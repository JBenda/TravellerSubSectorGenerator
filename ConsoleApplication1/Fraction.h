#pragma once

#include "Confederation.h"

class Fraction {
public:
	enum INFLUENZ {MAIN, OBSKURE, BORDER, SMAL, REKONIZE, IMPORTEND, OP};
	INFLUENZ getInfluenz() { return influenz; }
	uint8_t getType() { return type; }
	Fraction(uint8_t population);
private:
	INFLUENZ influenz;
	uint8_t type;		//13
};