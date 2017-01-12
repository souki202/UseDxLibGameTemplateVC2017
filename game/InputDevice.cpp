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
void InputDevice::Keyboard::Update()
{
	timer.Update();

	GetHitKeyStateAll(m_isPushKey);  // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++) {
		if (m_isPushKey[i]) { // i番のキーコードに対応するキーが押されていたら
			m_frame[i]++;   // 加算
			m_time[i] += timer.GetDeltaTime();
		}
		else {              // 押されていなければ
			m_frame[i] = 0; // 0にする
			m_time[i] = 0;
		}
	}
}

bool InputDevice::Keyboard::IsRelease(int keyCode)
{
	if (GetPressFrame(keyCode) > 0) {
		m_isPress[keyCode] = true;
		return false;
	}
	else if (GetPressFrame(keyCode) == 0 &&
		m_isPress[keyCode] == true) {
		m_isPress[keyCode] = false;
		return true;
	}

	return false;
}

bool InputDevice::Keyboard::GetIsUpdate(int keyCode)
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
	m_leftPress.first = 0;
	m_leftPress.second = 0;
	m_rightPress.first = 0;
	m_rightPress.second = 0;
	m_middlePress.first = 0;
	m_middlePress.second = 0;
	m_position.first = 0;
	m_position.second = 0;
	m_lastPosition.first = 0;
	m_lastPosition.second = 0;
}

InputDevice::Mouse::~Mouse()
{
}

void InputDevice::Mouse::Update()
{
	timer.Update();

	//力技だけど仕方ない MOUSE_INPUT_8とか0x0080やで･･･
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		m_leftPress.first++;
		m_leftPress.second += static_cast<int>(timer.GetDeltaTime());
	}
	else {
		m_leftPress.first = 0;
		m_leftPress.second = 0;
	}

	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
		m_rightPress.first++;
		m_rightPress.second += static_cast<int>(timer.GetDeltaTime());
	}
	else {
		m_rightPress.first = 0;
		m_rightPress.second = 0;
	}


	if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0) {
		m_middlePress.first++;
		m_middlePress.second += static_cast<int>(timer.GetDeltaTime());
	}
	else {
		m_middlePress.first = 0;
		m_middlePress.second = 0;
	}

	m_lastPosition = m_position;
	GetMousePoint(&m_position.first, &m_position.second);
}
