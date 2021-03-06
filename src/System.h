#pragma once

#include "Justize.h"
#include "Tempreture.h"
#include "Water.h"
#include "SpacePort.h"
#include "TekkLvl.h"

#include <cstring>
#include <vector>
#include <memory>

class System
{
public:
	typedef std::vector<System*> TradeList;
	enum SYSTEM_INFO { SPACE_MARINE, SCOUT, SINCE, TAS, IMPERIUM, PIRATES, GAS_GIANT, END };
	enum TRADE_CODES { Ag, Ar, As, Di, Due, Ei, Ga, Hi, In, Li, Lo, Na, Ni, Oed, Re, Va, Wa, Wue};
	enum ZONE { NEUTRAL, YELLOW, RED };
	enum TRADE_TYPE { UNIN, AGRA, IND, OMNI };
	System(int idNum, int position);
	TRADE_TYPE getTradeType() const { return tradeType; }
    const std::string& getName() const { return name; }
	SpacePort::SPACE_PORT_TYPE getSpacePort() { return spacePort; }
    bool isInfo(SYSTEM_INFO info) const {
      return (systemInfo[info / 8] & (0x80) >> info % 8);}
	bool isBase(SYSTEM_INFO base) const {
      return (systemInfo[base / 8] & (0x80 >> base % 8)); }
	bool isGaseGiant() const {
      return (systemInfo[GAS_GIANT / 8] & (0x80 >> GAS_GIANT % 8)); }
	ZONE getZone() const { return travellerZone; }
	std::string getSystemCode() const;
	void setName(std::string newName);
	void setSystemInfo(SYSTEM_INFO type, bool value);
	void addBase(SpacePort::SPACE_PORT_TYPE base);
	void removeBase(SpacePort::SPACE_PORT_TYPE base);
	void addTradeCode(TRADE_CODES tr);
	void removeTradeCode(TRADE_CODES code);
	void setZone(ZONE zone);
	int getId() const { return id; }
	void addTradeSystem(System* tradeSys) { trade.push_back(tradeSys); }
	const System::TradeList* const  getTradeSystems() const { return &trade; }
    int getPosition() const { return pos; } // only can use when you know the map size
private:
	int id;
    int pos;
	SpacePort::SPACE_PORT_TYPE spacePort;
	uint8_t systemInfo[SYSTEM_INFO::END / 8 + (SYSTEM_INFO::END % 8 > 1 ? 1 : 0)];	//maske
	ZONE travellerZone;
	std::vector<std::shared_ptr<Confederation>> confederation;
	std::vector<std::shared_ptr<System>> communication;
	TradeList  trade;
	TRADE_TYPE tradeType;
	std::vector<TRADE_CODES> tradeCode;
	uint8_t size;			// max 10
	uint8_t atmosphere;		// max 15
	int8_t temperatur;		// max 5
	int8_t water;			// max 10
	uint8_t population;		// max 10
	std::vector<std::shared_ptr<Fraction>> fraction;
	uint8_t culture[3];
	std::shared_ptr<Justize> justize;
	uint8_t tekkLvl;
	std::string name;
};
