#pragma once
#include "Xorshift128.h"

class Dice 
{
private:
	static int last;
public:
	static int getLast() { return last; }
	static int role2W6() { return Xorshift128::instance()->getNextUInt % 6 + Xorshift128::instance()->getNextUInt() % 6; }
	static int roleW66() { return (Xorshift128::instance()->getNextUInt % 6) * 10 + Xorshift128::instance()->getNextUInt() % 6; }
};