#include "TradeNet.h"

void TradeNet::setTradeNet(Bezirk* const bez)
{
  auto itr = bez->begin();
  while(itr != bez->end())
  {
    std::cout << "System: " << itr->second->getId() << "\n";  
    ++itr;
  }
}

void TradeNet::draw(sf::RenderWindow& window) const
{
  std::size_t size = _vertex.size();
  if( size > 0 && size % 2 == 0)
    window.draw(&_vertex[0], size, sf::Lines);  
}

void TradeNet::addRoute(const sf::Vector2f& start, const sf::Vector2f& end)
{
  _vertex.push_back(sf::Vertex(start, _color));
  _vertex.push_back(sf::Vertex(end, _color));
  _change = true;
}

void TradeNet::clear()
{
  _change = false;
  _vertex.clear();
}
