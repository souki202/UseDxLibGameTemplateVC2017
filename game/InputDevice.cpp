#include "InputDevice.h"

InputDevice::Keyboard::Keyboard()
{
	for (auto &x : m_frame) {
		x = 0;
	}
	for (auto &x : m_time) {
		x = 0;
	}
	for (auto &x : m_lastUpdateTime) {
		x = 0;
	}
	m_interval = 100;
}

InputDevice::Keyboard::~Keyboard()
{
}

// キーの入力状態更新
void InputDevice::Keyboard::update()
{
	timer.update();

	GetHitKeyStateAll(m_isPushKey);  // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++) {
		if (m_isPushKey[i]) { // i番のキーコードに対応するキーが押されていたら
			m_frame[i]++;   // 加算
			m_time[i] += timer.getDeltaTime();
		}
		else {              // 押されていなければ
			m_frame[i] = 0; // 0にする
			m_time[i] = 0;
		}
	}
}

bool InputDevice::Keyboard::isRelease(int keyCode)
{
	if (getPressFrame(keyCode) > 0) {
		m_isPress[keyCode] = true;
		return false;
	}
	else if (getPressFrame(keyCode) == 0 &&
		m_isPress[keyCode] == true) {
		m_isPress[keyCode] = false;
		return true;
	}

	return false;
}

bool InputDevice::Keyboard::getIsUpdate(int keyCode)
{
	if (!m_time[keyCode]) {
		m_lastUpdateTime[keyCode] = 0;
		return false;
	}
	else if (m_time[keyCode] && m_lastUpdateTime[keyCode] == 0) { //初回フレーム
		m_lastUpdateTime[keyCode] += m_interval * 3;
		return true;
	}
	else if (m_time[keyCode] && //押していて、次にtrueが返るべき時間を超えている時
		m_time[keyCode] >= m_lastUpdateTime[keyCode] + m_interval) {
		m_lastUpdateTime[keyCode] += m_interval;
		return true;
	}

	return false;
}


//ここからマウス
InputDevice::Mouse::Mouse()
{
	for (auto& x : press) {
		x.first = 0;
		x.second = 0;
	}
	for (auto& x : phases) {
		x = INVALID;
	}
	m_position.first = 0;
	m_position.second = 0;
	m_lastPosition.first = 0;
	m_lastPosition.second = 0;
}

InputDevice::Mouse::~Mouse()
{
}

void InputDevice::Mouse::update()
{
	timer.update();

	m_lastPosition = m_position;
	GetMousePoint(&m_position.first, &m_position.second);
	for (int i = 0; i < 3; i++) {
		if ((GetMouseInput() & buttons[i]) != 0) {
			if (phases[i] == BEGAN) {
				phases[i] = IN_THE_MIDDLE;
				if (!i) m_leftClickInitPosition = m_position;
			}
			else {
				phases[i] = BEGAN;
			}
			press[i].first++;
			press[i].second += static_cast<int>(timer.getDeltaTime());
		}
		else {
			if (phases[i] == ENDED) {
				phases[i] = INVALID;
			}
			else phases[i] = ENDED;
			press[i].first = 0;
			press[i].second = 0;
		}
	}
}

void InputDevice::Touch::update()
{
	timer.update();
	int num = GetTouchInputNum();
	int id;
	int x, y;
	std::map<int, Info> newTouches;

	for (int i = 0; i < num; i++) {
		GetTouchInput(i, &x, &y, &id, NULL);
		//画面外は修正
		if (x < 0) x = 0;
		else if (x > CommonSettings::WINDOW_WIDTH) x = CommonSettings::WINDOW_WIDTH;
		if (y < 0) y = 0;
		else if (y > CommonSettings::WINDOW_HEIGHT) y = CommonSettings::WINDOW_HEIGHT;
		keys.insert(std::make_pair(id, std::make_pair(x, y)));
	}

	for (auto& touch : touches) {
		if (touch.second.phase == ENDED) {
			continue;
		}

		//既存のタッチか調べる
		auto it = keys.find(touch.first);
		//ある
		if (it != keys.end()) {
			int beforeX = touch.second.nowPos.first, beforeY = touch.second.nowPos.second;
			int lastDeltaPosX = touch.second.deltaPos.first;
			touch.second.deltaPos.first = it->second.first - beforeX;
			touch.second.deltaPos.second = it->second.second - beforeY;
			touch.second.nowPos.first = it->second.first;
			touch.second.nowPos.second = it->second.second;

			//方向転換(左右のみ)
			if ((lastDeltaPosX <= 0 && touch.second.deltaPos.first > 0)
				|| (lastDeltaPosX >= 0 && touch.second.deltaPos.first < 0)) {
				touch.second.turnPos = touch.second.nowPos;
			}

			touch.second.frame++;
			touch.second.time += timer.getDeltaTime();
			touch.second.phase = IN_THE_MIDDLE;
			newTouches.insert(std::make_pair(touch.first, std::move(touch.second)));
			keys.erase(it);
			continue;
		}
		else { //無い。タッチ終了
			touch.second.phase = ENDED;
			newTouches.insert(std::make_pair(touch.first, std::move(touch.second)));
		}
	}

	//タッチが無ければ最初のタッチを初期化
	if (!num && newTouches.empty()) firstTouchId = -1;

	//残ったkeyは新規
	for (auto& key : keys) {
		if (firstTouchId == -1) {
			firstTouchId = key.first;
		}
		newTouches.insert(std::make_pair(key.first, Info(key.second.first, key.second.second, timer.getDeltaTime())));
	}

	touches = std::move(newTouches);

	firstTouch = touches.find(firstTouchId);
}
