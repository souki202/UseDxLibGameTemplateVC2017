#include <stdio.h>
#include "Form.h"

using namespace CommonSettings;
//---------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);//�E�B���h�E���[�h�ŋN��//FALSE���ƃt���X�N���[��
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);//�E�B���h�E�T�C�Y
	SetDoubleStartValidFlag(true);
	if (DxLib_Init() == -1) {
		return -1;
	}

	Form Fmain;

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);
	while (1) {
		if (ProcessMessage() != 0 || keyInput.GetPressFrame(KEY_INPUT_ESCAPE)) {
			break;//�E�B���h�E�́~�{�^���܂���Esc�L�[�����ꂽ�烋�[�v�𔲂���
		}
		ClearDrawScreen();

		//�L�[�{�[�h, �}�E�X�̏�Ԃ��X�V
		keyInput.Update();
		mouseInput.Update();

		if (!Fmain.Update()) {
			break;
		}
		ScreenFlip();//����ʂ𔽉f
	}

	DxLib_End();
	return 0;
}
//---------------------------------------------------------------------------