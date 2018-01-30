#include "System.h"

System::System()
{
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
		justize = Justize(0);
		fraction = std::vector<Fraction>(0);
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
private:
	std::vector<std::shared_ptr<Confederation>> confederation;
	std::vector<std::shared_ptr<System>> communication;
	std::vector<std::shared_ptr<System>> trade;
	std::vector<Fraction> fraction;
	uint8_t culture[3];
	Justize justize;