#pragma once
#include "DxLib.h"
#include <string>
#include <memory>
//#include <boost\any.hpp>
#include "InputDevice.h"
#include "Random.h"

class Panel;

class Button {
public:
	Button(int panelId);
	virtual ~Button();

	void setImage(const std::string& filePath, bool isSwitch = false, bool isDivHorizonal = false, bool isOn = false);
	void setImage(int fileHandle, bool isSwitch = false, bool isDivHorizonal = false, bool isOn = false);
	virtual void draw();
	void setPosition(float posX, float posY) { pos.first = posX; pos.second = posY; };
	void setPosition(int posX, int posY) { pos.first = static_cast<float>(posX); pos.second = static_cast<float>(posY); };
	virtual bool onMouse();
	virtual bool onClick();
	virtual bool onClinking();
	const std::pair<int, int>& getSize() { return size; };
	const std::pair<float, float>& getPosition() { return pos; };
	void setSwitchType(int type) { switchType = type; }; //0: クリック後にonoff 1:クリック中に変化
	void setIsOn(bool b) { isOn = b; };

	static void resetClick() {
		firstClick = 0; 
		clickingId = 0;
	};
	static int getClickingId() { return clickingId; };
	int getId() { return id; };

	void hoverAlpha(int notHover, int hover) { alpha[0] = notHover; alpha[1] = hover; };

	//virtual int executeClickEvent(const boost::any& v...) { return 0; };
	virtual int executeClickEvent() { return 0; };
protected:
	std::pair<int, int> size;
	std::pair<float, float> pos;
	int img[2];
	bool isOn, isSwitch;
	int switchType;

	std::array<int, 2> alpha;
	bool isHover;
private:
	int id;
	int panelId;
	bool isExternal;
	static int firstClick;
	static int clickingId;
};