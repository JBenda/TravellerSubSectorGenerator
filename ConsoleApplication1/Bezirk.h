#pragma once

#include "System.h"

class Bezirk
{
public:
	Bezirk(int x = 8, int y = 10, int wmP = 0);
	std::string getName() { return name; }
	std::shared_ptr<System> getSystemAt(int x, int y);
	std::string getSystemCode(std::string systemName);
	std::string getSystemCode(int x, int y);
private:
	std::string generateSystemCode(std::shared_ptr<System> sys, int x, int y);
	std::map<int,std::shared_ptr<System>> systems;
	std::string name;
	int dim[2];
};