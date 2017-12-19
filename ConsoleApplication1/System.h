#pragma once

#include "Justize.h"
class System
{
public:
	enum SPACE_PORT_TYPE {X, E, D, C, B, A};
	enum SYSTEM_INFO {SPACE_MARINE, SCOUT, SINCE, TAS, IMPERIUM, PIRATS, GAS_GIANT, END};
	enum TRADE_COES {Ag, Ar, As, Di, Due, Ei, Ga, Hi, In, Li, Lo, Na, Ni, Oed, Re, Va, Wa, Wue};
	enum ZONE {NEUTRAL, YELLOW, RED};
	System();
	std::string getName();
	SPACE_PORT_TYPE getSpacePort(){return spacePort;}
	bool isBase(int i);
	bool isGaseGiant();
	uint8_t getNumGasGiants();
	ZONE getZone() { return travellerZone; }
	std::string getSystemCode();
private:
	SPACE_PORT_TYPE spacePort;
	uint8_t systemInfo[SYSTEM_INFO::END / 8 + (SYSTEM_INFO::END % 8 > 1 ? 1 : 0)];	//maske
	ZONE travellerZone;
	std::vector<std::shared_ptr<Confederation>> confederation;
	std::vector<std::shared_ptr<System>> communication;
	std::vector<std::shared_ptr<System>> trade;
	uint8_t size;			//10
	uint8_t atmosphere;		//15
	uint8_t temperatur;		//5
	uint8_t water;			//10
	uint8_t population;		//10
	std::vector<Fraction> fraction;
	uint8_t culture[3];
	Justize justize;
	uint8_t tekkLvl;
};