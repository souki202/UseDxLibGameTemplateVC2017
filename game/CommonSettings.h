#pragma once
namespace CommonSettings {
	//�𑜓x
	constexpr float WINDOW_WIDTH = 1280;
	constexpr float WINDOW_HEIGHT = 720;

	//fps(60�ȏ�͐���������؂��Ă��������B)
	constexpr int FRAME_RATE = 60;

	constexpr char* GAME_TITLE = "Game"; //Unicode�����Z�b�g���p����wchar_t�ɁB
};

class Screen {
private:
	Screen() {};
	~Screen() {};
public:
	static const int getScreen() { return screen; };
	static void setScreen(int val) { DeleteGraph(screen); screen = val; };
private:
	static int screen;
	static int width;
	static int height;
};
