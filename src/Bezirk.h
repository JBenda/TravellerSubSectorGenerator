#pragma once


#include "System.h"
#include "Math.hpp"
#include "TradeNet.h"

#include "SFML/Graphics.hpp"

#include <cstring>
#include <iterator>

class Bezirk
{
  using map_t = std::map<int, std::unique_ptr<System>>;
public:
    enum ICONS {PIRATE_BASE, RFA, SCOUT_BASE, MARINE_BASE};
	Bezirk(int x = 8, int y = 10, int wmP = 0);
    int getWidth() const { return dim[0]; }
	std::string getName() const { return name; }
	System* getSystemAt(int x, int y);
    const System* getSystemAt(int x, int y) const;
	std::string getSystemCode(std::string systemName) const;
	std::string getSystemCode(int x, int y) const;
	bool isSystem(int x, int y) const { return systems.count(y * dim[0] + x) != 0; }
	static int getDis(int pos1[2], int pos2[]);
        int getDis(int pos1, int po2) const;
	int getId(int x, int y) const;
	int disShortestTravPath(int pos1[2], int pos2[]) const; // 0 = no path
	void printMapLine(int pos[2]) const;
    int getNumSystems() const { return systems.size(); }
    typename map_t::const_iterator begin() const { return systems.cbegin(); }
    typename map_t::const_iterator end()const  { return systems.cend(); }
    typename map_t::iterator begin() { return systems.begin(); }
    typename map_t::iterator end() { return systems.end(); }
    void draw(sf::RenderWindow & window, sf::Vector2f topLeft, int dx, int dy, int dw, int h, int a, sf::Font& font, int* selected, const int* dim) const;
    ~Bezirk() { free(map); }
private:
	void calculateRouts();
	void calculateTrades();
	void calculateTradePath();
	static int dis(int* const pos1, int* const pos2);
	std::string generateSystemCode(const System& sys, int x, int y) const;
	map_t systems; // sorted is importend
	std::map<int, int> posToId;
	std::string name;
	int dim[2];
	uint8_t *map;
    std::unique_ptr<TradeNet> tradeNet;
    std::vector<sf::Image> _icons;
};
