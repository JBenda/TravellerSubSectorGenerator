// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	const uint32_t v[] = { 0x6563c1b9, 0x0d55caae, 0x41ce21b9 };
	Xorshift128::instance()->setValues(v[0], v[1], v[2]);
	Bezirk *bezirk;
	bezirk = new Bezirk(8, 10);
	char c;
	std::cin >> c;
    return 0;
}

