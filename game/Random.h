#pragma once
#include <random>

class MyRandom {
public:
	MyRandom();
	~MyRandom();
	int Generate(int min, int max);	//[min, max]	�����Ή� max < min�͑z�肵�Ă��Ȃ��̂Œ���
private:
	static std::random_device rnd;
	static std::mt19937 mt;

	int offset;
};