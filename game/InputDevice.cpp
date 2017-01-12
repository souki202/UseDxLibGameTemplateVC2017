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

// �L�[�̓��͏�ԍX�V
void InputDevice::Keyboard::Update()
{
	timer.Update();

	GetHitKeyStateAll(m_isPushKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�

	for (int i = 0; i < 256; i++) {
		if (m_isPushKey[i]) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_frame[i]++;   // ���Z
			m_time[i] += timer.GetDeltaTime();
		}
		else {              // ������Ă��Ȃ����
			m_frame[i] = 0; // 0�ɂ���
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

	//�͋Z�����ǎd���Ȃ� MOUSE_INPUT_8�Ƃ�0x0080��ť��
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
