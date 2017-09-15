#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "DxLib.h" //C’¼‰º‚ÉDxLib_‚È‚ñ‚¿‚á‚ç‚ð“ü‚ê‚Ä‚Ë
#include "CommonSettings.h"
#include "InputDevice.h"

using namespace CommonSettings;

class Form
{
public:
	Form();
	~Form();

	bool update();
	bool draw();

private:
};
//---------------------------------------------------------------------------