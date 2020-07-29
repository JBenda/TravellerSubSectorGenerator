#pragma once

#include "Fraction.h"

class Justize
{
public:
	enum struct JUSTIZE_PARTS { WAPON, DRUG, INFORMATION, TEKK, TRAVELLER, PSIONIK, END};
	enum struct REAKTION {NOT, CONTROL, INSPECTION, FIGHT};
	enum struct CONFLIKT_TYPE {FIRST_CONTACT, DAYLY_VISIT, CREEPY_PERSON, BAR_FIGHT, GUN_FIER, RAID, HAVY_GUN_FIGHT, SLAYING};
	enum struct JUDGEMENT{NOTHING, MONEY_1x1, MONEY_2x5, MONEY_2x10, PRISION_MONTH, PRISION_YEAR, PRISION_YEARx2, PRISION_FOREVER, DEATH};
	enum struct ACT {FIGHT, DESTROY, WRING_ID, DETAH, SLAYING};
	Justize(uint8_t mainFractionType);
	void setJustizeLvl(JUSTIZE_PARTS kind, int8_t value) { justizeLvl[(uint8_t)kind] = value; }
	int8_t getJustizLvl(JUSTIZE_PARTS kind) { return justizeLvl[(uint8_t)kind]; }
    int8_t getJustizLvl() { return justizeLvlAvrg; }
private:
	int8_t justizeLvl[(uint8_t)JUSTIZE_PARTS::END - 1];
    int8_t justizeLvlAvrg;
};
