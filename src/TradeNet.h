#pragma once
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"

/** \brief handle Netowork
 * functions: draw Trade routs
 */
class Bezirk;
class TradeNet
{
public:
  struct Edge{
    Edge(int s, int e, int d, int idS, int idE) 
    {
      dis = d;
      start = s;
      idStart = idS;
      idEnd = idE;
      end = e;
    }
    Edge(Edge&& e) : start{e.start}, end{e.end}, idStart{e.idStart}, idEnd{e.idEnd}, dis{e.dis}{}
    Edge(const Edge& e)
    {
      dis = e.dis;
      start = e.start;
      idStart = e.idStart;
      idEnd = e.idEnd;
      end = e.end;
    }
    Edge& operator=(const Edge& e)
    {
      dis = e.dis;
      start = e.start;
      idStart = e.idStart;
      idEnd = e.idEnd;
      end = e.end;
      return *this;
    }
    Edge reverse()
    {
      return Edge(end, start, dis, idEnd, idStart);
    }
    bool operator==(const Edge& e )
    { return idStart == e.idStart && idEnd == e.idEnd; }
    bool operator<(const Edge& e) /**< schortest Edge dirst */
    { return dis > e.dis; }
    int start;
    int end;
    int idStart;
    int idEnd;
    int dis;
  };
  TradeNet() : _change{false},  _vertex{}, _color{sf::Color::Blue} {}
  TradeNet(const sf::Color& color) : _change{false}, _vertex{}, _color{color} {}
  void setTradeNet(const Bezirk* bez);
  void clear();
  void draw(sf::RenderWindow& window) const;
  bool hasChanged() const { return _change; }
  void calculatePos(const sf::Vector2f& topLeft, int dx, int h, int dy);
  void stashNet();
  bool isInNet(int id) const { return _tradeRouts.find(id) != _tradeRouts.end(); };
private:
  const Bezirk* _pBezirk;
  bool _change;
  std::vector<sf::Vertex> _vertex;
  std::map<int, std::vector<Edge>> _tradeRouts; /**< trade routs saved in an adjzentz List */
  std::map<int, std::vector<Edge>> _adjList;
  const sf::Color _color;
};
