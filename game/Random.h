#pragma once
#include <random>
#define rnd Random::getInstance()

class Random {
private:
	Random();
	~Random();

public:
	static Random& getInstance() { static Random r; return r; };
	int generate(int min, int max);

private:
	static std::random_device rd;
	static std::mt19937 mt;

	int offset;
};