#pragma once
#include "Xorshift128.h"

class Dice 
{
private:
	static int last;
public:
	static int getLast() { return last; }
	static int roleW6() { return Xorshift128::instance()->getNextUInt() % 6 + 1; }
	static int role2W6() { return Xorshift128::instance()->getNextUInt() % 6 + Xorshift128::instance()->getNextUInt() % 6 + 2; }
	static int roleW66() { return (Xorshift128::instance()->getNextUInt() % 6 + 1) * 10 + Xorshift128::instance()->getNextUInt() % 6 + 1; }
	static int roleW3() { return Xorshift128::instance()->getNextUInt() % 3 + 1; }
};