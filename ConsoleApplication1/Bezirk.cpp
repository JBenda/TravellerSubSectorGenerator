#include "Bezirk.h"
#include <math.h>

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
			systems[i] = std::make_shared<System>(numSystems, i);
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
        tradeNet = std::make_unique<TradeNet>(TradeNet());
        tradeNet->setTradeNet(*this);
}

void Bezirk::printMapLine(int pos[2]) const
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

int Bezirk::disShortestTravPath(int pos1[2], int pos2[]) const
{
	std::map<int, int>::const_iterator itr[2];
	itr[0] = posToId.find(pos1[0] + pos1[1] * dim[0]);
	itr[1] = posToId.find(pos2[0] + pos2[1] * dim[0]);
	if (itr[0] == posToId.end() || itr[1] == posToId.end())
		return 0;
	return map[itr[0]->second * systems.size() + itr[1]->second];
}

int Bezirk::getId(int x, int y) const
{
	auto t = posToId.find(x + y * dim[0]);
	if (t != posToId.end())
		return t->second;
	else 
		return - 1;
}

int Bezirk::getDis(int pos1[2], int pos2[2]) const
{
	return dis(pos1[0] + pos1[1] * dim[0], pos2[0] + pos2[1] * dim[0]);
}

int Bezirk::dis(int pos1, int pos2) const	//Manhatten distance
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
		std::cout << (int)map[i] << ((i + 1) % numSystems == 0 ? "\n" : (map[i] > 9 ? " " : "  "));
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
			if ((ib = map[num * systems.size() + i]) > 4 || ib <= 0) //if systems not connected or to far away
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
const std::shared_ptr<System> Bezirk::getSystemAt(int x, int y) const
{
	int pos = x + dim[0] * y;
	std::map<int, std::shared_ptr<System>>::const_iterator itr;
	itr = systems.find(pos);
	if (itr != systems.end())
		return itr->second;
	else
		return nullptr;
}

std::string Bezirk::generateSystemCode(std::shared_ptr<System> sys, int x, int y) const
{
	std::stringstream str;
	str << sys->getName() << ' ';
	str << (x < 10 ? '0' << x : x) << (y < 10 ? '0' << y : y) << ' ';
	str << sys->getSystemCode();
	return str.str();
}
std::string Bezirk::getSystemCode(std::string systemName) const
{
	std::map<int, std::shared_ptr<System>>::const_iterator itr;
	for (itr = systems.begin(); itr != systems.end(); ++itr)
	{
		if (itr->second->getName().compare(systemName) == 0)
			return generateSystemCode(itr->second, itr->first % dim[0], itr->first / dim[0]);
	}
	return "System not found";

}
std::string Bezirk::getSystemCode(int x, int y) const
{
	return generateSystemCode(getSystemAt(x, y), x, y);
}

// values from 0, dw, 2dw, 3dw, 4dw, 5dw
const float cosVal[] = {1.f, 0.5f, -0.5f, -1.f, -0.5f, 0.5f};
const float sinVal[] = {0.f, 0.866025404f, 0.866025404f, 0.f, -0.866025404f, -0.866025404f};

void Bezirk::draw(sf::RenderWindow & window,  sf::Vector2f topLeft,int dx, int dy, int dw, int h, int a, sf::Font& font, int* selected, const int* dim) const
{

	sf::ConvexShape hex(6);
	sf::Text num;
	num.setCharacterSize(18);
	num.setColor(sf::Color::Blue);
	num.setFont(font);
	for(int i = 0; i < 6; ++i)
	  hex.setPoint(i, sf::Vector2f(cosVal[i] * a, sinVal[i] * a));
	hex.setOutlineColor(sf::Color::Black);
	hex.setOutlineThickness(1);
	hex.setFillColor(sf::Color::Green);
        hex.setPosition(100, 100);
        window.draw(hex);
	int pij[2];
	// int sysNum = 0;
	char cBuff[20];
	hex.setOutlineThickness(2);
	hex.setOutlineColor(sf::Color::Black);
	bool isSys;
	int buff;
        const System::TradeList* const tl = selected[0] >= 0 ? getSystemAt(selected[0], selected[1])->getTradeSystems() : nullptr;
        if(tradeNet->hasChanged())
          tradeNet->calculatePos(topLeft, dx, h, dy);
	for (int j = 0; j < dim[1]; ++j)
	{
		for (int i = 0; i < dim[0]; ++i)
		{
			isSys = false;
                        sf::Vector2f position = topLeft + sf::Vector2f(i * dx, j * 2.f * h + (i % 2 == 0 ? 0.f : dy));
			hex.setPosition(position);
			if (isSystem(i, j))
			{
				isSys = true;
                                sprintf(cBuff, "%i", getId(i, j));
				num.setString(cBuff);
				num.setPosition(hex.getPosition().x - num.getGlobalBounds().width * 0.5f,
								hex.getPosition().y - num.getGlobalBounds().height * 0.5f);
				pij[0] = i;
				pij[1] = j;
				if (i == selected[0] && j == selected[1])
				{
					hex.setFillColor(sf::Color::Blue);
				}
				else if ((buff = disShortestTravPath(selected, pij)) <= 4 && buff > 0)
				{
					hex.setFillColor(sf::Color::Magenta);
					int id = getSystemAt(i, j)->getId();
					if (tl != nullptr)
					{
						for (std::size_t k = 0; k < tl->size(); ++k)
							if (tl->at(k)->getId() == id)
							{
								hex.setFillColor(sf::Color::Red);
								break;
							}
					}
				}
				else
				{
                                                // std::cout << "fill color"<< getSystemAt(i, j)->getTradeType() <<  "setted at";
						switch (getSystemAt(i, j)->getTradeType())
						{
						case System::TRADE_TYPE::UNIN :hex.setFillColor(sf::Color::Cyan);
                                                  // std::cout << "Cyan\n";
							break;
						case System::TRADE_TYPE::AGRA: hex.setFillColor(sf::Color::Green);
                                                  // std::cout << "Green\n";
							break;
						case System::TRADE_TYPE::IND: hex.setFillColor(sf::Color(100, 100, 100));
                                                  // std::cout << "Gray\n";
							break;
						case System::TRADE_TYPE::OMNI: hex.setFillColor(sf::Color::Black);
                                                  // std::cout << "Black\n";
							break;
                                                default: hex.setFillColor(sf::Color::Yellow);
                                                  // std::cout << "Yello valkue\n";
						}
				}
					
			}
			else
				hex.setFillColor(sf::Color::White);
			window.draw(hex);
			if(isSys)
			  window.draw(num);
		}
	}
        window.draw(hex);
        tradeNet->draw(window);
}
