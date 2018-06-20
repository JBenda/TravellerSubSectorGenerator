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
  TradeNet() : _change{false},  _vertex{}, _color{sf::Color::Red} {}
  TradeNet(const sf::Color& color) : _change{false}, _vertex{}, _color{color} {}
  void addRoute(const sf::Vector2f& start, const sf::Vector2f& end);
  void setTradeNet(Bezirk* const bez);
  void clear();
  void draw(sf::RenderWindow& window) const;
private:
  bool _change;
  std::vector<sf::Vertex> _vertex;
  const sf::Color _color;
};
