#include "TradeNet.h"


void TradeNet::draw(sf::RenderWindow& window)
{
  std::size_t size = _vertex.size();
  if(_change)
  {
    _verBuffer.update(_vertex, size, 0);
    _change = false;
  }
  if( size > 0 && size % 2 == 0)
    window.draw(_verBuffer);  
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
  _verBuffer = sf::VertexBuffer();
  _vertex.clear();
}
