#include "InputDevice.h"
#include "Button.h"

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

// �L�[�̓��͏�ԍX�V
void InputDevice::Keyboard::update()
{
	timer.update();

	GetHitKeyStateAll(m_isPushKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++) {
		if (m_isPushKey[i]) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_frame[i]++;   // ���Z
			m_time[i] += timer.getDeltaTime();
		}
		else {              // ������Ă��Ȃ����
			m_frame[i] = 0; // 0�ɂ���
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
	else if (m_time[keyCode] && m_lastUpdateTime[keyCode] == 0) { //����t���[��
		m_lastUpdateTime[keyCode] += m_interval * 3;
		return true;
	}
	else if (m_time[keyCode] && //�����Ă��āA����true���Ԃ�ׂ����Ԃ𒴂��Ă��鎞
		m_time[keyCode] >= m_lastUpdateTime[keyCode] + m_interval) {
		m_lastUpdateTime[keyCode] += m_interval;
		return true;
	}

	return false;
}


//��������}�E�X
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
			else if (phases[i] != IN_THE_MIDDLE) {
				phases[i] = BEGAN;
			}
			press[i].first++;
			press[i].second += static_cast<int>(timer.getDeltaTime());
		}
		else {
			if (phases[i] == ENDED) {
				phases[i] = INVALID;
				if (!i) {
					Button::resetClick();
				}
			}
			else if (phases[i] != INVALID) phases[i] = ENDED;
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
		//��ʊO�͏C��
		if (x < 0) x = 0;
		else if (x > CommonSettings::WINDOW_WIDTH) x = static_cast<int>(CommonSettings::WINDOW_WIDTH);
		if (y < 0) y = 0;
		else if (y > CommonSettings::WINDOW_HEIGHT) y = static_cast<int>(CommonSettings::WINDOW_HEIGHT);
		keys.insert(std::make_pair(id, std::make_pair(x, y)));
	}

	for (auto& touch : touches) {
		if (touch.second.phase == ENDED) {
			continue;
		}

		//�����̃^�b�`�����ׂ�
		auto it = keys.find(touch.first);
		//����
		if (it != keys.end()) {
			int beforeX = touch.second.nowPos.first, beforeY = touch.second.nowPos.second;
			int lastDeltaPosX = touch.second.deltaPos.first;
			touch.second.deltaPos.first = it->second.first - beforeX;
			touch.second.deltaPos.second = it->second.second - beforeY;
			touch.second.nowPos.first = it->second.first;
			touch.second.nowPos.second = it->second.second;

			touch.second.frame++;
			touch.second.time += timer.getDeltaTime();
			touch.second.phase = IN_THE_MIDDLE;
			newTouches.insert(std::make_pair(touch.first, std::move(touch.second)));
			keys.erase(it);
			continue;
		}
		else { //�����B�^�b�`�I��
			touch.second.phase = ENDED;
			newTouches.insert(std::make_pair(touch.first, std::move(touch.second)));
		}
	}

	//�c����key�͐V�K
	if (!num && keys.empty() && touches.empty()) firstTouchId = -1;
	for (auto& key : keys) {
		if (firstTouchId == -1) {
			firstTouchId = key.first;
		}
		newTouches.insert(std::make_pair(key.first, Info(key.second.first, key.second.second, timer.getDeltaTime())));
	}

	touches = std::move(newTouches);

	firstTouch = touches.find(firstTouchId);
	if (firstTouchId == -1) {
	}
}
