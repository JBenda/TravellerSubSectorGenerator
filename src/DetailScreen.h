#pragma once
#include <memory>
#include "System.h"
#include "SystemParser.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>

#include <vector>
#include <memory>
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
  static constexpr char PLANET_FRAGMENT_SHADER[] = R"V0G0N(
uniform sampler2D texture;

#define PI 3.1415926538
void main() {
  vec2 p = 2. * gl_TexCoord[0].xy - 1.;
  float r = length(p);
  if (r > 1.) {
    discard;
  }
  vec2 uv;
  uv.x = asin(r) / PI + 0.5;
  uv.y = acos(p.x/r) / PI; // acos p*[1,0] / r
  if (uv.x > 1. || uv.y > 1. || uv.x < 0. || uv.y < 0.) {
    gl_FragColor = vec4(0., 0., 1., 1.);
  } else {
    gl_FragColor = texture2D(texture, uv);
  }
 }
  )V0G0N";
  void loadShader();
  sf::Shader _planetShader;
};
