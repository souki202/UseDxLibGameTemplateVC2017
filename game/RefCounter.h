#pragma once

class RefCounter {
public:
	RefCounter() { addRef(); };
	~RefCounter() {};

	void addRef() { cnt++; };
	void releaseRef() { cnt--; };
	int getCount() const { return cnt; };
private:
	int cnt = 0;
};