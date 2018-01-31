#pragma once

#include "Justize.h"
#include "Tempreture.h"
#include "Water.h"
#include "SpacePort.h"
#include "TekkLvl.h"
class System
{
public:
	enum SYSTEM_INFO { SPACE_MARINE, SCOUT, SINCE, TAS, IMPERIUM, PIRATS, GAS_GIANT, END };
	enum TRADE_COES { Ag, Ar, As, Di, Due, Ei, Ga, Hi, In, Li, Lo, Na, Ni, Oed, Re, Va, Wa, Wue };
	enum ZONE { NEUTRAL, YELLOW, RED };
	System();
	std::string getName() { return name; }
	SpacePort::SPACE_PORT_TYPE getSpacePort() { return spacePort; }
	bool isBase(SYSTEM_INFO base) { return (systemInfo[base / 8] & (0x80 >> base % 8)); }
	bool isGaseGiant() { return (systemInfo[GAS_GIANT / 8] & (0x80 >> GAS_GIANT % 8)); }
	ZONE getZone() { return travellerZone; }
	std::string getSystemCode();
	void setName(std::string newName);
	void setSystemInfo(SYSTEM_INFO type, bool value);
	void addBase(SpacePort::SPACE_PORT_TYPE base);
	void removeBase(SpacePort::SPACE_PORT_TYPE base);
	void addTradeCode(TRADE_COES code);
	void removeTradeCode(TRADE_COES code);
	void setZone(ZONE zone);
private:
	SpacePort::SPACE_PORT_TYPE spacePort;
	uint8_t systemInfo[SYSTEM_INFO::END / 8 + (SYSTEM_INFO::END % 8 > 1 ? 1 : 0)];	//maske
	ZONE travellerZone;
	std::vector<std::shared_ptr<Confederation>> confederation;
	std::vector<std::shared_ptr<System>> communication;
	std::vector<std::shared_ptr<System>> trade;
	std::vector<TRADE_COES> tradeCode;
	uint8_t size;			//10
	uint8_t atmosphere;		//15
	int8_t temperatur;		//5
	int8_t water;			//10
	uint8_t population;		//10
	std::vector<std::shared_ptr<Fraction>> fraction;
	uint8_t culture[3];
	std::shared_ptr<Justize> justize;
	uint8_t tekkLvl;
	std::string name;
};