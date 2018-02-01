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

int Bezirk::disShortestTravPath(int pos1[2], int pos2[])
{
	std::map<int, int>::iterator itr[2];
	itr[0] = posToId.find(pos1[0] + pos1[1] * dim[0]);
	itr[1] = posToId.find(pos2[0] + pos2[1] * dim[0]);
	if (itr[0] == posToId.end() || itr[1] == posToId.end())
		return 0;
	return map[itr[0]->second * systems.size() + itr[1]->second];
}

int Bezirk::getDis(int pos1[2], int pos2[2])
{
	return dis(pos1[0] + pos1[1] * dim[0], pos2[0] + pos2[1] * dim[0]);
}

int Bezirk::dis(int pos1, int pos2)	//Manhatten distance
{
	sf::Vector2i p1, p2;
	p1 = { pos1 % dim[0], pos1 / dim[0] };
	p2 = { pos2 % dim[0], pos2 / dim[0] };
	int x[] = { p1.x, p2.x };
	int z[] = { p1.y - (int)(p1.x / 2), p2.y - (int)(p2.x / 2) };
	int y[] = { -x[0] - z[0], -x[1] - z[1] };
	return std::max(std::abs(x[0]-x[1]), std::max(std::abs(y[0]-y[1]), std::abs(z[0]-z[1])));
}

void Bezirk::calculateRouts()
{
	int numSystems = systems.size();
	std::cout << "NumSys= " << numSystems << std::endl;
	map = (uint8_t*)malloc(numSystems * numSystems* sizeof(uint8_t));
	memset(map, 0, numSystems * numSystems * sizeof(uint8_t));
	std::map<int, std::shared_ptr<System>>::iterator itr[2];
	int d;
	int row = 0;
	int colum = 0;
	std::cout << "Size = " << numSystems << std::endl;
	for (itr[0] = systems.begin(), row = 0; itr[0] != systems.end(); ++itr[0], ++row)
	{
		posToId[itr[0]->first] = row;
		for (itr[1] = itr[0], itr[1] ++, colum = row + 1; itr[1] != systems.end(); ++itr[1], ++colum)
		{
			if (itr[0]->first == itr[1]->first)
			{
				std::cout << "ERROR" << std::endl;
				continue;
			}
			if ((d = dis(itr[0]->first, itr[1]->first)) <= 2)
			{
				map[row * numSystems + colum] = d;
				map[colum * numSystems + row] = d;	//symetrie
			}
		}
	}
	char c;
	return;
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
	std::cout << "Calculation" << std::endl;
	std::cin >> c;
	for (int i = 0; i < numSystems * numSystems; ++i)
		std::cout << (int)map[i] << (i % numSystems == 0 ? '\n' : ' ');
	std::cin >> c;
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
