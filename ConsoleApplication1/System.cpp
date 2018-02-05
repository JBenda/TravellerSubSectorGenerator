#include "System.h"
bool isIn(int v, int min, int max)
{
	return (min <= v && max >= v);
}
System::System(int idNum)
{
	id = idNum;
	trade = std::make_shared<std::vector<std::shared_ptr<System>>>();
	memset(systemInfo, 0, SYSTEM_INFO::END / 8 + (SYSTEM_INFO::END % 8 > 1 ? 1 : 0));
	name = "test";
	if (Dice::role2W6() < 10)	//gas giant
		setSystemInfo(SYSTEM_INFO::GAS_GIANT, true);
	
	size = Dice::role2W6() - 2;
	
	atmosphere = Dice::role2W6() - 7 + size;
	if (atmosphere > 15)
		atmosphere = 0;

	if (atmosphere <= 1)
		temperatur = 0;
	else
	{
		temperatur = Dice::role2W6() + Tempreture::atmoToWm(atmosphere);
		if (temperatur < 2) temperatur = 2;
		if (temperatur > 12) temperatur = 12;
	}

	if (size <= 1)
		water = 0;
	else
	{
		water = Dice::role2W6() - 7 + Water::wmFromAtmoTemp(atmosphere, temperatur);
		if (water < 0) water = 0;
		if (water > 10) water = 10;
	}

	population = Dice::role2W6() - 2;
	if (population == 0)
	{
		tekkLvl = 0;
		justize = std::make_shared<Justize>(0);
		fraction = std::vector<std::shared_ptr<Fraction>> (0);
		return;
	}
	
	fraction.push_back(std::make_shared<Fraction>(population, true));
	int numFractions = Dice::roleW3();
	if (fraction[0]->getType() == 0 || fraction[0]->getType() == 7)
		numFractions += 1;
	else if (fraction[0]->getType() >= 10)
		numFractions -= 1;
	for (int i = 0; i < numFractions; ++i)
	{
		fraction.push_back(std::make_shared<Fraction>(population, false));
	}

	for (int i = 0; i < 3; ++i)
	{
		culture[i] = Dice::roleW66();
	}

	justize = std::make_shared<Justize>(fraction[0]->getType());

	spacePort = SpacePort::getSpacePort(Dice::role2W6());

	tekkLvl = TekkLvl::getTekkLvl(spacePort, size, atmosphere, water, population, fraction[0]->getType());
	int r;
	if (atmosphere >= 10 || (r = fraction[0]->getType(), r == 0) || r == 7 || r == 10
		|| (r = justize->getJustizLvl(Justize::JUSTIZE_PARTS::WAPON), r == 0) || r >= 9)
		travellerZone = ZONE::YELLOW;
	else
		travellerZone = ZONE::NEUTRAL;

	//TradeCodes
	tradeType = TRADE_TYPE::UNIN;
	if (isIn(atmosphere, 4, 9) && isIn(water, 4, 8) && isIn(population, 5, 7))
		addTradeCode(Ag);
	if (isIn(atmosphere, 2, 5) && isIn(water, 0, 3))
		addTradeCode(Ar);
	if (size == 0 && atmosphere == 0 && water == 0)
		addTradeCode(As);
	if (population >= 9)
		addTradeCode(Di);
	if (isIn(population, 1, 3))
		addTradeCode(Due);
	if (atmosphere <= 1 && water >= 1)
		addTradeCode(Ei);
	if(size >= 5 && isIn(atmosphere, 4, 9) && isIn(water, 4, 8))
		addTradeCode(Ga);
	if(tekkLvl >= 12)
		addTradeCode(Hi);
	int a;
	if((((a = atmosphere), a<=2) || a==4 || a==7 || a==9) && population >= 9)
		addTradeCode(In);
	if(atmosphere >= 10 && water >= 1)
		addTradeCode(Li);
	if(tekkLvl <= 5)
		addTradeCode(Lo);
	if(atmosphere <= 3 && water <= 3 && population >= 6)
		addTradeCode(Na);
	if(isIn(population, 4, 6))
		addTradeCode(Ni);
	if(population == 0 && fraction[0]->getType() == 0 && justize->getJustizLvl((Justize::JUSTIZE_PARTS) 0) == 0)
		addTradeCode(Oed);
	if ((atmosphere == 6 || atmosphere == 8) && isIn(population, 6, 8))
		addTradeCode(Re);
	if(atmosphere == 0)
		addTradeCode(Va);
	if(water >= 10)
		addTradeCode(Wa);
	if(atmosphere >= 2 && water == 0)
		addTradeCode(Wue);
}
void System::addTradeCode(TRADE_COES tr)
{
	tradeCode.push_back(tr);
	if (tradeType == OMNI)
		return;
	if (tr == In || tr == Hi || tr == Di || tr == Re)
	{
		if (tradeType == AGRA)
			tradeType = OMNI;
		else
			tradeType = IND;
	}
	if (tr == As || tr == Wue || tr == Ei || tr == Ni || tr == Ag || tr == Ga || tr == Wa)
	{
		if (tradeType == IND)
			tradeType = OMNI;
		else
			tradeType = AGRA;
	}
}
std::string System::getSystemCode()
{
	std::stringstream str;
	str << "Not worked yet";
	//space Base, size, atoms, hydro, pop, reg, just, -, techlvl, list base, zone
	return str.str();
}
void System::setSystemInfo(SYSTEM_INFO type, bool value)
{
	if (value)
		systemInfo[type / 8] |= (0x80 >> type % 8);
	else
		systemInfo[type / 8] &= ~(0x80 >> type % 8);
}
