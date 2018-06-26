#pragma once
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/OpenGL.hpp"
#include "Bezirk.h"

/** \brief handle Netowork
 * functions: draw Trade routs
 */
class Bezirk;
class TradeNet
{
public:
  TradeNet() : _change{false},  _vertex{}, _color{sf::Color::Blue} {}
  TradeNet(const sf::Color& color) : _change{false}, _vertex{}, _color{color} {}
  void addRoute(int start, int end);
  void setTradeNet(const Bezirk& bez);
  void clear();
  void draw(sf::RenderWindow& window) const;
  bool hasChanged() const { return _change; }
  void calculatePos(const sf::Vector2f& topLeft, int dx, int h, int dy);
private:
  int _width;
  bool _change;
  std::vector<sf::Vertex> _vertex;
  std::vector<int> _positions;
  const sf::Color _color;
};
