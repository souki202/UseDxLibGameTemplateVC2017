#pragma once
//----------------------------------------------------------
#define _USE_MATH_DEFINES
#include <array>
#include <map>
#include <cmath>
#include <algorithm>
#include "DxLib.h"
#include "Timer.h"
#include "CommonSettings.h"

#define USE_INPUTDEVICE_DEF

#ifdef USE_INPUTDEVICE_DEF
#define keyInput InputDevice::Keyboard::getInstance()
#define mouseInput InputDevice::Mouse::getInstance()
#define touchInput InputDevice::Touch::getInstance()
#endif

class Button;
class Panel;
//----------------------------------------------------------
namespace InputDevice {
	enum PressPhase {
		BEGAN, IN_THE_MIDDLE, ENDED, INVALID
	};

	class Keyboard {
	private:
		Keyboard();
		~Keyboard();
	public:
		static Keyboard& getInstance() { static Keyboard key; return key; };

		void update();				// �L�[�̓��͏�Ԃ��X�V����
		int getPressFrame(int keyCode) { return m_frame[keyCode]; }// �����̃L�[�R�[�h�̃L�[�̓��̓t���[������Ԃ�
		int getPressTime(int keyCode) { return m_time[keyCode]; }	// �����̃L�[�R�[�h�̃L�[�̓��͎���(���A���^�C��)��Ԃ�
		bool isRelease(int keyCode);	// �{�^�����オ�����Ƃ�
		void setInterval(int time) { m_interval = time; };	//�~���b
		bool getIsUpdate(int keyCode);	//�t���[����Ȃ�]�苁�߂Ăˁ�
	private:
		Timer timer;
		std::array<int, 256> m_frame;
		std::array<int, 256> m_time;
		std::array<int, 256> m_lastUpdateTime;
		std::array<bool, 256> m_isPress;
		char m_isPushKey[256];	//Update()�ŃL�[�̓��͏�Ԃ�ێ�

		int m_interval;
	};

	class Mouse {
	private:
		Mouse();
		~Mouse();

	public:
		static Mouse& getInstance() { static Mouse mouse; return mouse; };

		void update();
		int getLeftPressFrame() { return press[0].first; };
		int getLeftPressTime() { return press[0].second; };
		int getLeftPressPhase() { return phases[0]; };
		const std::pair<int, int>& getLeftClickInitPosition() { return m_leftClickInitPosition; };
		int getRightPressFrame() { return press[1].first; };
		int getRightPressTime() { return press[1].second; };
		int getRightPressPhase() { return phases[1]; };
		int getMiddlePressFrame() { return press[2].first; };
		int getMiddlePressTime() { return press[2].second; };
		int getMiddlePressPhase() { return phases[2]; };
		int getWheelRotateValue() { return GetMouseWheelRotVol(); };	//������, ��O����
		const std::pair<int, int>& getPosition() {
			return m_position;
		};
		std::pair<int, int> getDeltaPosition() {
			return std::make_pair(m_position.first - m_lastPosition.first, m_position.second - m_lastPosition.second);
		};
	private:
		Timer timer;
		std::array<std::pair<int, int>, 3> press;//�t���[��, ����
		std::pair<int, int> m_position;
		std::pair<int, int> m_leftClickInitPosition;
		std::pair<int, int> m_lastPosition;
		std::array<PressPhase, 3> phases;
		int buttons[3] = { MOUSE_INPUT_LEFT , MOUSE_INPUT_RIGHT , MOUSE_INPUT_MIDDLE };
	};

	class Touch {
	private:
		Touch() {};
		~Touch() {};

	public:
		struct Info {
			Info() { frame = 1; time = 0; };
			Info(int x, int y, int time) {
				initPos.first = x;
				initPos.second = y;
				nowPos.first = x;
				nowPos.second = y;
				deltaPos.first = 0;
				deltaPos.second = 0;
				frame = 1;
				this->time = time;
				phase = BEGAN;
			};
			std::pair<int, int> initPos;
			std::pair<int, int> nowPos;
			std::pair<int, int> deltaPos; //�O�t���[���Ƃ̍�
			int frame;
			int time;
			int flickDirection = 0; //1�� 2�E
			int flickedLine = 0;
			bool hasNeverFlickYet = true;
			int initLine;
			int nowLine;
			int lastLine;
			PressPhase phase;
		};

		static Touch& getInstance() { static Touch touch; return touch; };

		void update();
		std::map<int, Info>& getAllTouchInfo() { return touches; };
		const Info* getFirstTouch() {
			if (firstTouch == touches.end()) return nullptr;
			return &firstTouch->second;
		};
	private:
		Timer timer;
		std::map<int, Info> touches;
		std::map<int, std::pair<int, int>> keys; //ID, ���W
		int firstTouchId;
		decltype(touches.find(0)) firstTouch;
	};
}
