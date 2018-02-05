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
			systems[i] = std::make_shared<System>(numSystems);
			numSystems++;
		}
	}
	std::cout << "Anzal der System " << numSystems << std::endl;

	calculateRouts();
	calculateTrades();
	calculateTradePath();
	//calculate Traderouts
	//calculate Kommunikationsrouts
	//perhand
	//set Alianz
	//paer hand
	//set Bases
	//perhand
}

void Bezirk::printMapLine(int pos[2])
{
	int line = posToId.find(pos[0] + pos[1] * dim[0])->second;
	int sysNum = systems.size();
	for (int i = 0; i < sysNum; ++i)
		std::cout << i << ' ';
	std::cout << std::endl;
	for (int i = 0; i < sysNum; ++i)
		std::cout << (int)map[sysNum * line + i] << (i < 10 ? " " : "  ");
	std::cout << std::endl;
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

int Bezirk::getId(int x, int y)
{
	auto t = posToId.find(x + y * dim[0]);
	if (t != posToId.end())
		return t->second;
	else 
		return - 1;
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
	int row;
	int colum = 0;
	std::cout << "Size = " << numSystems << std::endl;
	for (row=0, itr[0] = systems.begin(); row < numSystems; ++row, ++itr[0])
	{
		posToId[itr[0]->first] = row;
		for(colum = row + 1, itr[1] = itr[0], ++itr[1]; colum < numSystems; ++colum, ++itr[1])
			if ((d = dis(itr[0]->first, itr[1]->first)) <= 2)
			{
				map[row * numSystems + colum] = d;
				map[colum * numSystems + row] = d;
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
						if (node < 0 || (buff[0] + buff[1]) < d)
						{
							node = k;
							d = buff[0] + buff[1];
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
	for (int i = 0; i < numSystems * numSystems; ++i)
		std::cout << (int)map[i] << ((i + 1) % numSystems == 0 ? '\n' : ' ');
}

void Bezirk::calculateTrades()
{
	int i, num = 0, ib;
	System::TRADE_TYPE tradeType, ttb;
	for (auto itr = systems.begin(); itr != systems.end(); ++num, ++itr)
	{
		tradeType = itr->second->getTradeType();
		if (tradeType == System::TRADE_TYPE::UNIN)
			continue;
		auto subI = itr;
		for (++subI, i = num + 1; subI != systems.end(); ++subI, ++i)
		{
			if ((ib = map[num * systems.size() + i]) > 4 || ib <= 0)
				continue;
			if ((ttb = subI->second->getTradeType()) != System::TRADE_TYPE::UNIN)
			{
				if (tradeType != ttb)
				{
					itr->second->addTradeSystem(subI->second);
					//andrsrum auch ??
				}
			}
		}
	}
}

void Bezirk::calculateTradePath()
{
	int num, sub, d, line;
	int goBack;
	std::shared_ptr<System> sys;
	System::TradeList tl;
	goBack = -1;
	do {
		num = 0;
		for (auto itr = systems.begin(); itr != systems.end(); ++itr, ++num)
		{
			if (goBack >= 0 || num < goBack)
				continue;
			tl = itr->second->getTradeSystems();
			std::sort(tl->begin(), tl->end());	//deletDuplicates
			tl->erase(std::unique(tl->begin(), tl->end()), tl->end());
			for (int i = 0; i < tl->size(); ++i)
			{
				line = systems.size() * num;
				d = map[line + tl->at(i)->getId()];
				if (d <= 0)
				{
					std::cerr << "ERROR Trade Partner" << std::endl;
					__debugbreak();
				}
				if (d <= 2)	//direct conection
					continue;
				sub = 0;
				d = -1;
				for (auto itr2 = systems.begin(); itr2 != systems.end(); ++itr2, ++sub)
					if (map[line + sub] <= 2 && map[line + sub] > 0)
						if(map[sub * systems.size() + tl->at(i)->getId()] > 0)
							if (d < 0 || map[sub * systems.size() + tl->at(i)->getId()] < d)
							{
								d = map[sub * systems.size() + tl->at(i)->getId()];
								sys = itr2->second;
							}
				sys->addTradeSystem(tl->at(i));
				(*tl)[i] = sys;
				if (sys->getId() < num)
					if (goBack < 0 || sys->getId() < goBack)
						goBack = sys->getId();
				std::sort(tl->begin(), tl->end());	//deletDuplicates
				tl->erase(std::unique(tl->begin(), tl->end()), tl->end());
			}
		}
	} while (goBack >= 0);
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
