#include "Bezirk.h"

Bezirk::Bezirk(int x, int y, int wmP) 
{
	name = "Test123";
	dim[0] = x;
	dim[1] = y;
	int numSystems = 0;
	for (int i = 0; i < x*y; ++i)
	{
		if (Dice::roleW6() > 3 - wmP)
		{
			systems[i] = std::make_shared<System>();
			numSystems++;
		}
	}
	std::cout << "Anzal der System " << numSystems << std::endl;

	calculateRouts();
	//calculate Traderouts
	// if(d <= 4) && path(<=2) && a e (In, Hi, Di, Re) && b e (As, Wue, Ei, Ni, Agr, Gar, Wa)
	//calculate Kommunikationsrouts
	//perhand
	//set Alianz
	//paer hand
	//set Bases
	//perhand
}
const float da = PI / 3.f;
#include "SFML\Graphics.hpp"
int Bezirk::dis(int pos1, int pos2)
{
	sf::Vector2i p1, d;
	p1 = { pos1 % dim[0], pos1 / dim[0]};
	d = { pos2 % dim[0], pos2 / dim[0] };
	d = p1 - d;
	//BIg Hexagon and boundary check //TODO
}

void Bezirk::calculateRouts()
{
	map = (uint8_t*)malloc(dim[0] * dim[1] * sizeof(uint8_t));
	memset(map, 0, dim[0] * dim[1] * sizeof(uint8_t));
	std::map<int, std::shared_ptr<System>>::iterator itr[2];
	int d;
	int row = 0;
	int colum = 0;
	int numSystems = systems.size();
	std::cout << "Size = " << numSystems << std::endl;
	for (itr[0] = systems.begin(), row = 0; itr[0] != systems.end(); ++itr[0], ++row)
	{
		for (itr[1] = itr[0], itr[1] ++, colum = 0; itr[1] != systems.end(); ++itr[1], ++colum)
		{
			if ((d = dis(itr[0]->first, itr[1]->first)) <= 2)
			{
				map[row * numSystems + colum] = d;
				map[colum * numSystems + row] = d;	//symetrie
			}
		}
	}
	bool updated;
	do {
		updated = false;
		for (int j = 0; j < numSystems; ++j)
		{
			for (int i = j + 1; i < numSystems; ++i)
			{
				if (map[j * numSystems + i] != 0)	//Systems allreday conected
					continue;
				d = -1;
				int node = -1;
				int buff[2];
				for (int k = 0; k < numSystems; ++k)
				{
					if ((buff[0] = map[j * numSystems + k]) != 0 && (buff[1] = map[i * numSystems + k]) != 0)
					{
						if (node < 0 || (buff[0] += buff[1]) < d)
						{
							node = k;
							d = buff[0];
						}
					}
				}
				if (node >= 0)
				{
					map[i * numSystems + j] = d;
					map[j * numSystems + i] = d;
					updated = true;
				}
			}
		}
	} while (updated);
	for (int i = 0; i < numSystems * numSystems; ++i)
		std::cout << map[i] << (i % numSystems == 0 ? '\n' : ' ');
}

std::shared_ptr<System> Bezirk::getSystemAt(int x, int y)
{
	int pos = x + dim[0] * y;
	std::map<int, std::shared_ptr<System>>::iterator itr;
	itr = systems.find(pos);
	if (itr != systems.end())
		return systems[pos];
	else
		return nullptr;
}
std::string Bezirk::generateSystemCode(std::shared_ptr<System> sys, int x, int y)
{
	std::stringstream str;
	str << sys->getName() << ' ';
	str << (x < 10 ? '0' << x : x) << (y < 10 ? '0' << y : y) << ' ';
	str << sys->getSystemCode();
	return str.str();
}
std::string Bezirk::getSystemCode(std::string systemName)
{
	std::map<int, std::shared_ptr<System>>::iterator itr;
	for (itr = systems.begin(); itr != systems.end(); ++itr)
	{
		if (itr->second->getName().compare(systemName) == 0)
			return generateSystemCode(itr->second, itr->first % dim[0], itr->first / dim[0]);
	}
	return "System not found";

}
std::string Bezirk::getSystemCode(int x, int y)
{
	return generateSystemCode(getSystemAt(x, y), x, y);
}
