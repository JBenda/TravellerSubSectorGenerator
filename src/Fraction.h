#pragma once

#include "Confederation.h"

class Fraction {
public:
	enum INFLUENZ {MAIN, OBSKURE, BORDER, SMALL, REKONIZE, IMPORTEND, OP};
	void setName(std::string newName) { name = newName; }
	void setDescription(std::string des) { description = des; }
	void setInfluenz(INFLUENZ inf) { influenz = inf; }
	void setType(int8_t typ) { type = typ; }
	INFLUENZ getInfluenz() { return influenz; }
	int8_t getType() { return type; }
	Fraction(uint8_t population, bool isMain)
	{
		name = "New";
		description = "--empty--";
		type = Dice::role2W6() - 7 + population;
		if (type < 0) type = 0;
		if (type > 13) type = 13;
		if (isMain)
		{
			influenz = MAIN;
		}
		else
		{
			int power = Dice::role2W6();
			if (power <= 3)
				influenz = OBSKURE;
			else if (power <= 5)
				influenz = BORDER;
			else if (power <= 7)
				influenz = SMALL;
			else if (power <= 9)
				influenz = REKONIZE;
			else if (power <= 11)
				influenz = IMPORTEND;
			else if (power >= 12)
				influenz = OP;
		}
	}
private:
	INFLUENZ influenz;
	int8_t type;		//13
	std::string description;
	std::string name;
};
