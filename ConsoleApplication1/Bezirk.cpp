#include "Bezirk.h"

Bezirk::Bezirk(int x, int y, int wmP) 
{
	name = "Test123";
	dim[0] = x;
	dim[1] = y;
	for (int i = 0; i < x*y; ++i)
	{
		if (Xorshift128::instance()->getNextUInt() % 6 > 3 - wmP)
			systems[i] = std::make_shared<System>();
	}
}

std::shared_ptr<System> Bezirk::getSystemAt(int x, int y)
{
	int pos = x + dim[0] * y;
	std::map<int, std::shared_ptr<System>>::iterator itr;
	itr = systems.find(pos);
	if (pos == systems.end)
		return nullptr;
	else
		return itr->second;
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
	for (itr = systems.begin; itr != systems.end; ++itr)
		if (itr->second->getName().compare(systemName) == 0)
			return generateSystemCode(itr->second, itr->first % dim[0], itr->first / dim[0]);
}
std::string Bezirk::getSystemCode(int x, int y)
{
	return generateSystemCode(getSystemAt(x, y), x, y);
}
