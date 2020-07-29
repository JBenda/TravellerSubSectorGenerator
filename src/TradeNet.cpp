#include "TradeNet.h"
#include "Bezirk.h"

#include <algorithm>
#include <cassert>

void TradeNet::setTradeNet(const Bezirk* bez)
{
  _pBezirk = bez;
  auto itr = bez->begin();
  int pos, id;
  while(itr != bez->end())
  {
    pos = itr->first;
    id = itr->second->getId();
    auto node = _adjList.find(id);
    if(node == _adjList.end())
      node = _adjList.insert(std::pair<int, std::vector<Edge>>(id, std::vector<Edge>())).first;
    auto sys = itr->second->getTradeSystems()->begin();
    auto listEnd = itr->second->getTradeSystems()->end();
    while(sys != listEnd)
    {
      int subPos = (*sys)->getPosition();
      int subId = (*sys)->getId();
      node->second.push_back(Edge(
        pos, subPos, 
        bez->getDis(pos, (*sys)->getPosition()), 
        id, subId
      ));

      // trade partner also trade partner
      auto subNode = _adjList.find(subId);
      if(subNode == _adjList.end())
        subNode = _adjList.insert(std::pair<int, std::vector<Edge>>(subId, std::vector<Edge>())).first;
      auto subItr = itr->second->getTradeSystems()->begin();
      while(subItr != itr->second->getTradeSystems()->end())
      {
        if(subItr != sys)
        {
          subNode->second.push_back(Edge(
            subPos, (*subItr)->getPosition(),
            bez->getDis(subPos, (*subItr)->getPosition()),
            subId, (*subItr)->getId()
          ));
        }
        ++subItr;
      }
      ++sys;
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

void TradeNet::stashNet()
{
  std::vector<char> bitset(_pBezirk->getNumSystems(), 0);
  std::vector<Edge> prioQueue{};
  std::map<int, std::vector<Edge>>::iterator node;
  
  
  do{
    if(prioQueue.empty())
    {
      node = _adjList.begin();  
    }
    else
    {
      int idStart = prioQueue.front().idStart;
      int idEnd = prioQueue.front().idEnd;
      // insert Edge in Both directions
      auto sys = _tradeRouts.find(idStart);
      if(sys == _tradeRouts.end())
        sys = _tradeRouts.insert(std::pair<int, std::vector<Edge>>(idStart, std::vector<Edge>())).first;
      sys->second.push_back(prioQueue.front());
      sys = _tradeRouts.find(idEnd);
      if(sys == _tradeRouts.end())
        sys = _tradeRouts.insert(std::pair<int, std::vector<Edge>>(idEnd, std::vector<Edge>())).first;
      sys->second.push_back(prioQueue.front().reverse());

      node = _adjList.find(prioQueue.front().idEnd);
    }
    bitset[node->first] = 0x0F;
    for(const Edge& e : node->second)
    {
      if(bitset[e.idEnd] == 0)
      {
        prioQueue.push_back(e);
        std::push_heap(prioQueue.begin(), prioQueue.end());
      }
    }
    _adjList.erase(node);
    while(!prioQueue.empty() && bitset[prioQueue.front().idEnd] != 0)
    {
      std::pop_heap(prioQueue.begin(), prioQueue.end());
      prioQueue.pop_back();
    }
  }while(!prioQueue.empty() || !_adjList.empty());
  assert(_adjList.empty());
  _change = true;
}

void TradeNet::calculatePos(const sf::Vector2f& topLeft, int dx, int h, int dy)
{
  std::cout << "VertexLength: " << _vertex.size() << "\n";
  assert(_vertex.empty());
  int x, y;
  int width = _pBezirk->getWidth();
  for( auto node : _tradeRouts )
  {
    x = node.second.front().start % width;
    y = node.second.front().start / width;
    sf::Vertex startV(topLeft + sf::Vector2f(x * dx, y * 2.f * h + (x % 2 == 0 ? 0.f : dy)), _color );
    for(auto e : node.second)
    {
      if(e.idStart >= e.idEnd) // only draw one direction
        continue;
      _vertex.push_back(startV);
      x = e.end % width;
      y = e.end / width;
      _vertex.push_back(sf::Vertex(topLeft + sf::Vector2f(x * dx, y * 2.f * h + (x % 2 == 0 ? 0.f : dy)), _color ));
    }
  }

  _change = false;
}

void TradeNet::clear()
{
  _change = false;
  _vertex.clear();
  _adjList.clear();
  _tradeRouts.clear();
}
