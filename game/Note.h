#pragma once
#include "Image.h"

class Note {
public:
	Note();
	~Note();
private:
	Image img;
	int type;
};