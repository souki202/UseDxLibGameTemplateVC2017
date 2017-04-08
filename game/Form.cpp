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

	/*
	キー入力サンプル
	*/
	int pressFrame = keyInput.getPressFrame(KEY_INPUT_SPACE);
	DrawFormatString(100, 200, 0xffffff, "スペースキーを%dだけ押した。", pressFrame);
	
	/*
	マウスサンプル
	*/
	int mouseX = mouseInput.getPosition().first;
	int mouseY = mouseInput.getPosition().second;
	int leftClickFrame = mouseInput.getLeftPressFrame();
	DrawFormatString(mouseX, mouseY - 20, 0xffffff, "%dの間、左クリックした。", leftClickFrame);

	/*
	タッチサンプル
	*/
	decltype(auto) touches = touchInput.getAllTouchInfo();
	for (auto& touch : touches) {
		DrawFormatString(
			touch.second.nowPos.first, touch.second.nowPos.second - 20,
			0xffffff, "タッチ!! time:%d, frame:%d, ID:%d",
			touch.second.time, touch.second.frame, touch.first);
	}

	return true;
}