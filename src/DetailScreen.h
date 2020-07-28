#pragma once
#include <memory>
#include "System.h"
#include "SystemParser.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class DetailScreen
{
public:
  /**
   * \param topLeft position topLeft corner
   * \param size size from description window
   * \param folderPath location wherre pre renderd Informations saved/should be save
   */
  DetailScreen(const sf::Font& font, sf::Vector2f&& topLeft, sf::Vector2f&& size, const std::string& folderPath) : _parser{folderPath}, _systemId{0}, _planetPic{sf::Vector2f(size.x/2, size.x/2)}, _topLeft{topLeft}, _size{size} 
  { 
    _font = font;
    _planetPic.setPosition(_topLeft); 
    _descriptoin.setPosition(sf::Vector2f(_topLeft.x, _topLeft.y + (_size.y / 2)));
    _descriptoin.setFont(_font);
    _descriptoin.setFillColor(sf::Color::Red);
  }
  void setSystem(const System& sys);
  void draw(sf::RenderWindow & window);
private:
  void resize(int numberLines);
  SystemParser::Description _des;
  SystemParser _parser;
  int _systemId, _fontSize;
  int _stateLins; /**< number of lines to display States */
  sf::Font _font;
  sf::Text _descriptoin;
  std::vector<sf::Text> _states;
  sf::RectangleShape _planetPic;
  sf::Vector2f _topLeft, _size;
};
