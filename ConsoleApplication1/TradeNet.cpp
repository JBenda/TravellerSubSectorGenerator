#include "TradeNet.h"

void TradeNet::setTradeNet(const Bezirk& bez)
{
  _width = bez.getWidth();
  auto itr = bez.begin();
  int pos;
  while(itr != bez.end())
  {
    pos = itr->first;
    for(auto sys : *(itr->second->getTradeSystems()))
    {
      addRoute(pos, sys->getPosition());
    } 
    ++itr;
  }
}

void TradeNet::draw(sf::RenderWindow& window) const
{
  std::size_t size = _vertex.size();
  if( size > 0 && size % 2 == 0)
    window.draw(&_vertex[0], size, sf::Lines);  
  else
    std::cout << "no routs: " << size <<"\n";
}

void TradeNet::addRoute(int start, int end)
{
  _positions.push_back(start);
  _positions.push_back(end);
  _change = true;
}

void TradeNet::calculatePos(const sf::Vector2f& topLeft, int dx, int h, int dy)
{
  auto itrP = _positions.begin();
  itrP += _vertex.size();
  int x, y;
  while( itrP != _positions.end() )
  {
    x = *itrP % _width;
    y = *itrP / _width;
    _vertex.push_back(sf::Vertex(topLeft + sf::Vector2f(x * dx, y * 2.f * h + (x % 2 == 0 ? 0.f : dy)), _color ));
    ++itrP;
  }

  _change = false;
}

void TradeNet::clear()
{
  _change = false;
  _vertex.clear();
}
