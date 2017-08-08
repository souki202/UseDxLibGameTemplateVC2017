#include <stdio.h>
#include "Form.h"

int Screen::screen = 0;

using namespace CommonSettings;
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);//ウィンドウモードで起動//FALSEだとフルスクリーン
	SetWindowSizeChangeEnableFlag(true);
	SetGraphMode(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT), 32);//ウィンドウサイズ
	SetDoubleStartValidFlag(true);
	if (DxLib_Init() == -1) {
		return -1;
	}

	Form Fmain;

	// 描画先を裏画面に変更
	SetCreateDrawValidGraphMultiSample(16, 3);
	Screen::setScreen(MakeScreen(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT), false));

	while (1) {
		if (ProcessMessage() != 0 || keyInput.getPressFrame(KEY_INPUT_ESCAPE)) {
			break;//ウィンドウの×ボタンまたはEscキー押されたらループを抜ける
		}

		SetDrawScreen(Screen::getScreen());
		ClearDrawScreen();

		//キーボード, マウスの状態を更新
		keyInput.update();
		mouseInput.update();
		touchInput.update();

		if (!Fmain.update()) {
			break;
		}
		Fmain.draw();

		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		DrawGraph(0, 0, Screen::getScreen(), false);
		ScreenFlip();//裏画面を反映
	}

	DxLib_End();
	return 0;
}
//---------------------------------------------------------------------------