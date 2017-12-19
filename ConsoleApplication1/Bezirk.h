#pragma once

#include "System.h"

class Bezirk
{
public:
	Bezirk();
	Bezirk(int x, int y);
	std::string getName() { return name; }
	std::shared_ptr<System> getSystemAt(int x, int y);
	std::string getSystemCode(std::string systemName);
	std::string getSystemCode(int x, int y);
private:
	std::vector<std::shared_ptr<System>> systems;
	std::string name;
};