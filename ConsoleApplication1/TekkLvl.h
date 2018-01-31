#pragma once
#include "SpacePort.h"
#include "Dice.h"

class TekkLvl {
public:
	static int getTekkLvl(SpacePort::SPACE_PORT_TYPE port,int size,int atmos, int water, int pop, int fracTyp)
	{
		int tekkLvl = Dice::roleW6();
		switch (port)
		{
		case SpacePort::A: tekkLvl += 6;
			break;
		case SpacePort::B: tekkLvl += 4;
			break;
		case SpacePort::C: tekkLvl += 2;
			break;
		case SpacePort::X: tekkLvl -= 4;
			break;
		}

		if (size <= 1)
			tekkLvl += 2;
		else if (size <= 4)
			tekkLvl += 1;

		if (atmos <= 3)
			tekkLvl += 1;
		else if (atmos >= 10)
			tekkLvl += 1;

		if (water == 9)
			tekkLvl += 1;
		if (water == 10)
			tekkLvl += 2;

		if (pop >= 1 && pop <= 5)
			tekkLvl += 1;
		else if (pop >= 9 && pop <= 12)
			tekkLvl += pop - 8;

		switch (fracTyp)
		{
		case 0:
		case 5: tekkLvl += 1;
			break;
		case 7: tekkLvl += 2;
			break;
		case 13:
		case 14: tekkLvl -= 2;
			break;
		}

		if (atmos <= 1 && tekkLvl < 8)
			tekkLvl = 8;
		if (atmos <= 3 && tekkLvl < 5)
			tekkLvl = 5;
		switch (tekkLvl)
		{
		case 4: case 7: case 9: if (tekkLvl < 3) tekkLvl = 3;
			break;
		case 10: case 15: if (tekkLvl < 8) tekkLvl = 8;
			break;
		case 11: if (tekkLvl < 9) tekkLvl = 9;
			break;
		case 12: if (tekkLvl < 10) tekkLvl = 10;
			break;
		case 13: case 14: if (tekkLvl < 5) tekkLvl = 5;
			break;
		}
		return tekkLvl;
	}
};