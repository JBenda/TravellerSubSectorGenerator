#include "DetailScreen.h"

#include <SFML/Graphics/Rect.hpp>


void DetailScreen::loadShader() {
  if (!_planetShader) {
    _planetShader = std::make_unique<sf::Shader>();
    _planetShader->loadFromMemory(PLANET_FRAGMENT_SHADER, sf::Shader::Type::Fragment);
  }
}

void DetailScreen::setSystem(const System& sys)
{
  if(sys.getId() == _systemId)
    return;
  _systemId = sys.getId();
  _parser.parse(sys, _des);
  _planetPic.setTexture(_des.texPlanet.get());
  std::size_t i = 0;
  bool res = _des.states.size() != _states.size();
  for(const std::string& s : _des.states)
  {
    ++i;
    if(i > _states.size())
      _states.push_back(Text(s, _font, _fontSize));
    else
      _states[i-1].setString(s);
  }
  if(res)
    resize(_des.states.size());
 _description.setString(_des.description);
 constexpr struct {float x = 0, y = 0, z = 1;} UP;
 _planetRotation = Quat(normalize(cross(_planetRotationAxis, UP)),
     -acos(dot(UP,_planetRotationAxis)));
 loadShader();
}

void reorderText() {}

void DetailScreen::animationUpdate(float dt) {
  _planetAngle += ROT_SPEED * dt;
  while(_planetAngle > 2.f * PI<float>) {
    _planetAngle -= 2.f * PI<float>;
  }
}

void DetailScreen::draw(sf::RenderWindow & window)
{
  if(_systemId < 0)  { return; }
  _planetShader->setUniform("texture", *_planetPic.getTexture());
  _planetShader->setUniform("rotation",
      (_planetRotation * Quat(_planetRotationAxis, _planetAngle)).mat());
  for(Text& text : _states)
    window.draw(text);
  window.draw(_description);
  window.draw(_planetPic, _planetShader.get());
}

void DetailScreen::resize(int numberLines)
{
  _stateLins = numberLines;

  sf::Vector2f pos(_topLeft.x + _size.x/2, _topLeft.y);
  for(Text& text : _states)
  {
    text.setFontSize(_fontSize);
    text.setPosition(pos);
    pos.y += 2 + _fontSize;
  }
}
