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

		void Update();				// キーの入力状態を更新する
		int GetPressFrame(int keyCode)	{ return m_frame[keyCode]; }// 引数のキーコードのキーの入力フレーム数を返す
		int GetPressTime(int keyCode)	{ return m_time[keyCode]; }	// 引数のキーコードのキーの入力時間(リアルタイム)を返す
		bool IsRelease(int keyCode);	// ボタンが上がったとき
		void SetInterval(int time)	{ m_interval = time; };	//ミリ秒
		bool GetIsUpdate(int keyCode);	//フレーム基準なら余り求めてね★
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
		static Mouse& GetInstance() { static Mouse mouse; return mouse; };

		void Update();
		int GetLeftPressFrame()		{ return m_leftPress.first; };
		int GetLeftPressTime()		{ return m_leftPress.second; };
		int GetRightPressFrame()	{ return m_rightPress.first; };
		int GetRightPressTime()		{ return m_rightPress.second; };
		int GetMiddlePressFrame()	{ return m_middlePress.first; };
		int GetMiddlePressTime()	{ return m_middlePress.second; };
		int GetWheelRotateValue()	 { return GetMouseWheelRotVol(); };	//奥が正, 手前が負
		const std::pair<int, int>& GetPosition() { 
			return m_position;
		};
		std::pair<int, int> GetDeltaPosition() {
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
}
