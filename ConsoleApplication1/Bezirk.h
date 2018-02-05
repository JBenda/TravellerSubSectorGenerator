#pragma once

#include "System.h"
#include "SFML\Graphics.hpp"

#define PI 3.14159265

class Bezirk
{
public:
	Bezirk(int x = 8, int y = 10, int wmP = 0);
	std::string getName() { return name; }
	std::shared_ptr<System> getSystemAt(int x, int y);
	std::string getSystemCode(std::string systemName);
	std::string getSystemCode(int x, int y);
	bool isSystem(int x, int y) { return systems.count(y * dim[0] + x) != 0; }
	int getDis(int pos1[2], int pos2[]);
	int getId(int x, int y);
	int disShortestTravPath(int pos1[2], int pos2[]); // 0 = no path
	void printMapLine(int pos[2]);
private:
	void calculateRouts();
	void calculateTrades();
	void calculateTradePath();
	int dis(int pos1, int pos2);
	std::string generateSystemCode(std::shared_ptr<System> sys, int x, int y);
	std::map<int,std::shared_ptr<System>> systems;
	std::map<int, int> posToId;
	std::string name;
	int dim[2];
	uint8_t *map;
};