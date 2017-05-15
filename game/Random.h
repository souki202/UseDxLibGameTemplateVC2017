#pragma once
#include <random>
#define rand Random::getInstance()

class Random {
private:
	Random();
	~Random();

public:
	static Random& getInstance() { static Random r; return r; };
	int generate(int min, int max);

private:
	static std::random_device rnd;
	static std::mt19937 mt;

	int offset;
};