#include "DetailScreen.h"


void DetailScreen::loadShader() {
  _planetShader.loadFromMemory(PLANET_FRAGMENT_SHADER, sf::Shader::Type::Fragment);
}

void DetailScreen::setSystem(const System& sys)
{
  if(sys.getId() == _systemId)
    return;
  _des = _parser.parse(sys);
  _planetPic.setTexture(&_des.texPlanet);
  std::size_t i = 0;
  bool res = _des.states.size() != _states.size();
  for(const std::string& s : _des.states)
  {
    ++i;
    if(i > _states.size())
      _states.push_back(sf::Text(s, _font, _fontSize));
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

void DetailScreen::animationUpdate(float dt) {
  _planetAngle += ROT_SPEED * dt;
  while(_planetAngle > 2.f * PI<float>) {
    _planetAngle -= 2.f * PI<float>;
  }
}

void DetailScreen::draw(sf::RenderWindow & window)
{
  _planetShader.setUniform("texture", *_planetPic.getTexture());
  _planetShader.setUniform("rotation",
      (_planetRotation * Quat(_planetRotationAxis, _planetAngle)).mat());
  for(sf::Text& text : _states)
    window.draw(text);
  window.draw(_description);
  window.draw(_planetPic, &_planetShader);
}

void DetailScreen::resize(int numberLines)
{
  _stateLins = numberLines;
  _fontSize =  (_size.x / numberLines) - 2;
  if(_fontSize > 20)
    _fontSize = 20;

  sf::Vector2f pos(_topLeft.x + _size.x/2, _topLeft.y);
  for(sf::Text& text : _states)
  {
    text.setCharacterSize(_fontSize);
    text.setPosition(pos);
    pos.y += 2 + _fontSize;
  }
}
