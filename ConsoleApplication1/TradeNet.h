#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/VertexBuffer.hpp>
#include "System.h"

/** \brief handle Netowork
 * functions: draw Trade routs
 */
class TradeNet
{
public:
  TradeNet() : _change{false}, _verBuffer{sf::PrimitiveType::Lines, sf::VertexBuffer::Usage::Static}, _vertex{}, _color{sf::Color::Red} {}
  TradeNet(const sf::Color& color) : _change{false}, _verBuffer{sf::PrimitiveType::Lines, sf::VertexBuffer::Usage::Static}, _vertex{}, _color{color} {}
  void addRoute(const sf::Vector2f& start, const sf::Vector2f& end);
  void clear();
  void draw(sf::RenderWindow& window);
private:
  bool _change;
  sf::VertexBuffer _verBuffer;
  std::vector<sf::Vertex> _vertex;
  const sf::Color _color;
};
