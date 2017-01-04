#include "MyRand.h"
std::random_device MyRandom::rnd;
std::mt19937 MyRandom::mt(rnd());
MyRandom::MyRandom()
{
	offset = 0;
}

MyRandom::~MyRandom()
{
}

int MyRandom::Generate(int min, int max)
{
	if (min < 0) {
		offset = min;
		std::uniform_int_distribution<> rn(0, max - offset);
		return rn(mt) + offset;
	}
	else {
		std::uniform_int_distribution<> rn(min, max);
		return rn(mt) + min;
	}
}