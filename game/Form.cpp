#include "Form.h"
Form::Form()
{
	SetMainWindowText(CommonSettings::GAME_TITLE);//ウィンドウのタイトル
}

Form::~Form()
{
}

bool Form::update()
{
	DrawFormatString(100, 100, 0xffffff, "ゲーム画面です。");
	
	return true;
}