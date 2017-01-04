#pragma once
//----------------------------------------------------------
#include <array>
#include "DxLib.h"
#include "Timer.h"

#define USE_INPUTDEVICE_DEF

#ifdef USE_INPUTDEVICE_DEF
#define keyInput InputDevice::Keyboard::GetInstance()
#define mouseInput InputDevice::Mouse::GetInstance()
#endif
//----------------------------------------------------------
namespace InputDevice {
	class Keyboard {
	private:
		Keyboard();
		~Keyboard();
	public:
		static Keyboard& GetInstance() { static Keyboard key; return key; };

		void Update();				// �L�[�̓��͏�Ԃ��X�V����
		int GetPressFrame(int keyCode)	{ return m_frame[keyCode]; }// �����̃L�[�R�[�h�̃L�[�̓��̓t���[������Ԃ�
		int GetPressTime(int keyCode)	{ return m_time[keyCode]; }	// �����̃L�[�R�[�h�̃L�[�̓��͎���(���A���^�C��)��Ԃ�
		bool IsRelease(int keyCode);	// �{�^�����オ�����Ƃ�
		void SetInterval(int time)	{ m_interval = time; };	//�~���b
		bool GetIsUpdate(int keyCode);	//�t���[����Ȃ�]�苁�߂Ăˁ�
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
		static Mouse& GetInstance() { static Mouse mouse; return mouse; };

		void Update();
		int GetLeftPressFrame()		{ return m_leftPress.first; };
		int GetLeftPressTime()		{ return m_leftPress.second; };
		int GetRightPressFrame()	{ return m_rightPress.first; };
		int GetRightPressTime()		{ return m_rightPress.second; };
		int GetMiddlePressFrame()	{ return m_middlePress.first; };
		int GetMiddlePressTime()	{ return m_middlePress.second; };
		int GetWheelRotateValue()	 { return GetMouseWheelRotVol(); };	//������, ��O����
		const std::pair<int, int>& GetPosition() { 
			return m_position;
		};
		std::pair<int, int> GetDeltaPosition() {
			return std::make_pair(m_position.first - m_lastPosition.first, m_position.second - m_lastPosition.second);
		};
	private:
		Timer timer;
		std::pair<int, int> m_leftPress; //�t���[��, ����
		std::pair<int, int> m_rightPress;
		std::pair<int, int> m_middlePress;
		std::pair<int, int> m_position;
		std::pair<int, int> m_lastPosition;
	};

	//���ꂾ���w�ǑO�̃e���v���̂܂ܕ��u
	class JoyPad {
	private:
		JoyPad();
		~JoyPad();

	public:
		static JoyPad& GetInstance() { static JoyPad joyPad; return joyPad; };
		void Update();
		bool Release(int KeyCode);
		int GetPressFrame(int KeyCode);

	private:
		int m_JoyKey[68];
		bool upon;

	public:
		//Keyboard.h
		static constexpr int JOYPAD1 = 1;
		static constexpr int JOYPAD2 = 34 + 1;
		//JOYPAD�ݒ�
		static constexpr int BUTTON_LEFT = 0;
		static constexpr int BUTTON_UP = 1;
		static constexpr int BUTTON_RIGHT = 2;
		static constexpr int BUTTON_DOWN = 3;

		static constexpr int BUTTON_1 = 4; //z  PS�R�� �~
		static constexpr int BUTTON_2 = 5; //x  PS�R�� ��
		static constexpr int BUTTON_3 = 6; //c  PS�R�� ��
		static constexpr int BUTTON_4 = 7; //a  PS�R�� ��

		static constexpr int BUTTON_5 = 8; //s  PS�R�� L1
		static constexpr int BUTTON_6 = 9; //d  PS�R�� L2
		static constexpr int BUTTON_7 = 10; //q  PS�R�� R1
		static constexpr int BUTTON_8 = 11; //w  PS�R�� R2

		static constexpr int BUTTON_9 = 12; //esc PS�R���@SELECT
		static constexpr int BUTTON_10 = 13; //space PS�R���@START
		static constexpr int BUTTON_11 = 14; //
		static constexpr int BUTTON_12 = 15; //
		static constexpr int BUTTON_13 = 16; //
		static constexpr int BUTTON_14 = 17; //
		static constexpr int BUTTON_15 = 18; //
		static constexpr int BUTTON_16 = 19; //
		static constexpr int BUTTON_17 = 20; //
		static constexpr int BUTTON_18 = 21; //
		static constexpr int BUTTON_19 = 22; //
		static constexpr int BUTTON_20 = 23; //
		static constexpr int BUTTON_21 = 24; //
		static constexpr int BUTTON_22 = 25; //
		static constexpr int BUTTON_23 = 26; //
		static constexpr int BUTTON_24 = 27; //
		static constexpr int BUTTON_25 = 28; //
		static constexpr int BUTTON_26 = 29; //
		static constexpr int BUTTON_27 = 30; //
		static constexpr int BUTTON_28 = 31; //
		static constexpr int BUTTON_29 = 32; //
		static constexpr int BUTTON_30 = 33; //
	};
}
