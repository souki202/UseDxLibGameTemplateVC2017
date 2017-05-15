#include "Button.h"
#include "Panel.h"
int Button::firstClick = 0;
int Button::clickingId = 0;

Button::Button(int panelId)
{
	isExternal = false;
	img[0] = 0; img[1] = 0;
	isOn = false;
	isSwitch = false;
	id = rand.generate(1, INT_MAX);
	this->panelId = panelId;
	switchType = 0;
	isHover = false;
	for (auto& x : alpha) x = 255;
	resetClick();
}

Button::~Button()
{
	if (!isExternal) {
		if (img[0] > 0) DeleteGraph(img[0]);
		if (img[1] > 0) DeleteGraph(img[1]);
	}
	firstClick = 0;
	clickingId = 0;
}

void Button::setImage(const std::string & filePath, bool isSwitch, bool isDivHorizonal, bool isOn)
{
	if (!isSwitch) {
		img[0] = LoadGraph(filePath.c_str());
		img[1] = img[0];
		GetGraphSize(img[0], &size.first, &size.second);
	}
	else {
		GetImageSize_File(filePath.c_str(), &size.first, &size.second);
		if (isDivHorizonal) { //横に分割
			size.first /= 2;
			LoadDivGraph(filePath.c_str(), 2, 2, 1, size.first, size.second, img);
		}
		else { //縦に分割
			size.second /= 2;
			LoadDivGraph(filePath.c_str(), 2, 1, 2, size.first, size.second, img);
		}
		this->isOn = isOn;
		this->isSwitch = isSwitch;
	}
}

void Button::setImage(int fileHandle, bool isSwitch, bool isDivHorizonal, bool isOn)
{
	isExternal = true;
	if (!isSwitch) {
		img[0] = fileHandle;
		img[1] = img[0];
		GetGraphSize(img[0], &size.first, &size.second);
	}
	else {
		GetGraphSize(fileHandle, &size.first, &size.second);
		if (isDivHorizonal) {
			size.first /= 2;
			img[0] = DerivationGraph(0, 0, size.first, size.second, fileHandle);
			img[1] = DerivationGraph(size.first, 0, size.first, size.second, fileHandle);
		}
		else {
			size.second /= 2;
			img[0] = DerivationGraph(0, 0, size.first, size.second, fileHandle);
			img[1] = DerivationGraph(0, size.second, size.first, size.second, fileHandle);
		}

		this->isOn = isOn;
		this->isSwitch = isSwitch;
	}
}

void Button::draw()
{
	if (isHover) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha[1]);
	}
	else SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha[0]);
	DrawGraphF(pos.first - size.first / 2, pos.second - size.second / 2, img[isOn], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Button::onMouse()
{
	int x = INT_MIN;
	int y = INT_MIN;
	int pressPhase = mouseInput.getLeftPressPhase();
	//タッチ優先
	auto t = touchInput.getFirstTouch();
	if (t != nullptr) {
		x = t->nowPos.first;
		y = t->nowPos.second;
		pressPhase = t->phase;
	}
	else {
		x = mouseInput.getPosition().first;
		y = mouseInput.getPosition().second;
	}
	if ((!firstClick || firstClick == id) && (!panelId || panelId == Panel::getOnMousePanelId())
		&& pos.first - size.first / 2 <= x && x <= pos.first + size.first / 2
		&& pos.second - size.second / 2 <= y && y <= pos.second + size.second / 2) {
		isHover = true;
		return true;
	}
	isHover = false;
	return false;
}

bool Button::onClick()
{
	int pressPhase = mouseInput.getLeftPressPhase();
	//タッチ優先
	auto t = touchInput.getFirstTouch();
	if (t != nullptr) {
		pressPhase = t->phase;
	}
	bool b = onClinking();
	if (firstClick == id && b && pressPhase == InputDevice::ENDED) {
		if (!switchType) isOn = !isOn;
		resetClick();
		return true;
	}
	return false;
}

bool Button::onClinking()
{
	int pressPhase = mouseInput.getLeftPressPhase();
	//タッチ優先
	auto t = touchInput.getFirstTouch();
	if (t != nullptr) {
		pressPhase = t->phase;
	}
	bool b = onMouse();
	if (b && ((!firstClick && pressPhase == InputDevice::BEGAN) || firstClick)
		&& (pressPhase == InputDevice::BEGAN
			|| pressPhase == InputDevice::IN_THE_MIDDLE
			|| pressPhase == InputDevice::ENDED)) {
		if (!firstClick) firstClick = id;
		if (!clickingId) clickingId = id;
		if (switchType == 1) isOn = true;
		return true;
	}
	if (switchType == 1) isOn = false;
	return false;
}

