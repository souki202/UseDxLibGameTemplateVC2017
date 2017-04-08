#pragma once
//----------------------------------------------------------
#include <array>
#include <map>
#include "DxLib.h"
#include "Timer.h"

#define USE_INPUTDEVICE_DEF

#ifdef USE_INPUTDEVICE_DEF
#define keyInput InputDevice::Keyboard::getInstance()
#define mouseInput InputDevice::Mouse::getInstance()
#define touchInput InputDevice::Touch::getInstance()
#endif
//----------------------------------------------------------
namespace InputDevice {
	class Keyboard {
	private:
		Keyboard();
		~Keyboard();
	public:
		static Keyboard& getInstance() { static Keyboard key; return key; };

		void update();				// キーの入力状態を更新する
		int getPressFrame(int keyCode) { return m_frame[keyCode]; }// 引数のキーコードのキーの入力フレーム数を返す
		int getPressTime(int keyCode) { return m_time[keyCode]; }	// 引数のキーコードのキーの入力時間(リアルタイム)を返す
		bool isRelease(int keyCode);	// ボタンが上がったとき
		void setInterval(int time) { m_interval = time; };	//ミリ秒
		bool getIsUpdate(int keyCode);	//フレーム基準なら余り求めてね★
	private:
		Timer timer;
		std::array<int, 256> m_frame;
		std::array<int, 256> m_time;
		std::array<int, 256> m_lastUpdateTime;
		std::array<bool, 256> m_isPress;
		char m_isPushKey[256];	//Update()でキーの入力状態を保持

		int m_interval;
	};

	class Mouse {
	private:
		Mouse();
		~Mouse();

	public:
		static Mouse& getInstance() { static Mouse mouse; return mouse; };

		void update();
		int getLeftPressFrame() { return m_leftPress.first; };
		int getLeftPressTime() { return m_leftPress.second; };
		int getRightPressFrame() { return m_rightPress.first; };
		int getRightPressTime() { return m_rightPress.second; };
		int getMiddlePressFrame() { return m_middlePress.first; };
		int getMiddlePressTime() { return m_middlePress.second; };
		int getWheelRotateValue() { return GetMouseWheelRotVol(); };	//奥が正, 手前が負
		const std::pair<int, int>& getPosition() {
			return m_position;
		};
		std::pair<int, int> getDeltaPosition() {
			return std::make_pair(m_position.first - m_lastPosition.first, m_position.second - m_lastPosition.second);
		};
	private:
		Timer timer;
		std::pair<int, int> m_leftPress; //フレーム, 時間
		std::pair<int, int> m_rightPress;
		std::pair<int, int> m_middlePress;
		std::pair<int, int> m_position;
		std::pair<int, int> m_lastPosition;
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
				frame = 1;
				this->time = time;
			};
			std::pair<int, int> initPos;
			std::pair<int, int> nowPos;
			std::pair<int, int> deltaPos; //前フレームとの差
			int frame;
			int time;
		};

		static Touch& getInstance() { static Touch touch; return touch; };

		void update();
		const std::map<int, Info>& getAllTouchInfo() { return touches; };
	private:
		Timer timer;
		std::map<int, Info> touches;
	};
}
