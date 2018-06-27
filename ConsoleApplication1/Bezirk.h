#pragma once

#include "System.h"
#include "SFML/Graphics.hpp"
#include <cstring>
#include <iterator>
// #include "TradeNet.h"

#define PI 3.14159265
class TradeNet;
class Bezirk
{
public:
	Bezirk(int x = 8, int y = 10, int wmP = 0);
        int getWidth() const { return dim[0]; }
	std::string getName() const { return name; }
	std::shared_ptr<System> getSystemAt(int x, int y);
        const std::shared_ptr<System> getSystemAt(int x, int y) const;
	std::string getSystemCode(std::string systemName) const;
	std::string getSystemCode(int x, int y) const;
	bool isSystem(int x, int y) const { return systems.count(y * dim[0] + x) != 0; }
	static int getDis(int pos1[2], int pos2[]);
        int getDis(int pos1, int po2) const;
	int getId(int x, int y) const;
	int disShortestTravPath(int pos1[2], int pos2[]) const; // 0 = no path
	void printMapLine(int pos[2]) const;
        int getNumSystems() const { return systems.size(); }
        std::map<int, std::shared_ptr<System>>::const_iterator begin() const { return systems.begin(); }
        std::map<int, std::shared_ptr<System>>::const_iterator end()const  { return systems.end(); }
        void draw(sf::RenderWindow & window, sf::Vector2f topLeft, int dx, int dy, int dw, int h, int a, sf::Font& font, int* selected, const int* dim) const;
private:
	void calculateRouts();
	void calculateTrades();
	void calculateTradePath();
	static int dis(int* const pos1, int* const pos2);
	std::string generateSystemCode(std::shared_ptr<System> sys, int x, int y) const;
	std::map<int,std::shared_ptr<System>> systems; // sorted is importend
	std::map<int, int> posToId;
	std::string name;
	int dim[2];
	uint8_t *map;
        std::unique_ptr<TradeNet> tradeNet;
};
