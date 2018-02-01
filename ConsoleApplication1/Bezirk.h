#pragma once

#include "System.h"

#define PI 3.14159265

class Bezirk
{
public:
	Bezirk(int x = 8, int y = 10, int wmP = 0);
	std::string getName() { return name; }
	std::shared_ptr<System> getSystemAt(int x, int y);
	std::string getSystemCode(std::string systemName);
	std::string getSystemCode(int x, int y);
	bool isSystem(int x, int y) { return systems.count(y * dim[1] + x) != 0; }
private:
	void calculateRouts();
	int dis(int pos1, int pos2);
	std::string generateSystemCode(std::shared_ptr<System> sys, int x, int y);
	std::map<int,std::shared_ptr<System>> systems;
	std::string name;
	int dim[2];
	uint8_t *map;
};