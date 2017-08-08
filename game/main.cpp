#include <stdio.h>
#include "Form.h"

int Screen::screen = 0;

using namespace CommonSettings;
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);//�E�B���h�E���[�h�ŋN��//FALSE���ƃt���X�N���[��
	SetWindowSizeChangeEnableFlag(true);
	SetGraphMode(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT), 32);//�E�B���h�E�T�C�Y
	SetDoubleStartValidFlag(true);
	if (DxLib_Init() == -1) {
		return -1;
	}

	Form Fmain;

	// �`���𗠉�ʂɕύX
	SetCreateDrawValidGraphMultiSample(16, 3);
	Screen::setScreen(MakeScreen(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT), false));

	while (1) {
		if (ProcessMessage() != 0 || keyInput.getPressFrame(KEY_INPUT_ESCAPE)) {
			break;//�E�B���h�E�́~�{�^���܂���Esc�L�[�����ꂽ�烋�[�v�𔲂���
		}

		SetDrawScreen(Screen::getScreen());
		ClearDrawScreen();

		//�L�[�{�[�h, �}�E�X�̏�Ԃ��X�V
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
		ScreenFlip();//����ʂ𔽉f
	}

	DxLib_End();
	return 0;
}
//---------------------------------------------------------------------------