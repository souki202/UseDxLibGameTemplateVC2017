#include <stdio.h>
#include "Form.h"

using namespace CommonSettings;
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);//ウィンドウモードで起動//FALSEだとフルスクリーン
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//ウィンドウサイズ
	SetDoubleStartValidFlag(true);
	if (DxLib_Init() == -1) {
		return -1;
	}

	Form Fmain;

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);
	while (1) {
		if (ProcessMessage() != 0 || keyInput.GetPressFrame(KEY_INPUT_ESCAPE)) {
			break;//ウィンドウの×ボタンまたはEscキー押されたらループを抜ける
		}
		ClearDrawScreen();

		//キーボード, マウスの状態を更新
		keyInput.Update();
		mouseInput.Update();

		if (!Fmain.Update()) {
			break;
		}
		ScreenFlip();//裏画面を反映
	}

	DxLib_End();
	return 0;
}
//---------------------------------------------------------------------------