#pragma once

#include "Math.hpp"
#include "System.h"
#include "SystemParser.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Vector3.hpp>

#include <vector>
#include <memory>
#include <string>

#include <iostream>

class DetailScreen
{
public:
  /**
   * \param topLeft position topLeft corner
   * \param size size from description window
   * \param folderPath location wherre pre renderd Informations saved/should be save
   */
  DetailScreen(const sf::Font& font, sf::Vector2f&& topLeft, sf::Vector2f&& size, const std::string& folderPath) : _parser{folderPath}, _systemId{-1}, _planetPic{sf::Vector2f(size.x/2, size.x/2)}, _topLeft{topLeft}, _size{size}, _states(0), _planetRotationAxis(0,-1,0.5)
  {
    normalize(_planetRotationAxis);
    _font = font;
    _planetPic.setPosition(_topLeft);
    _description.setPosition(sf::Vector2f(_topLeft.x, _topLeft.y + (_size.y / 2)));
    _description.setFont(_font);
    _description.setFillColor(sf::Color::Red);
  }
  void setSystem(const System& sys);
  void draw(sf::RenderWindow & window);

  void animationUpdate(float dt);
private:
  static constexpr float ROT_SPEED = PI<float> / 3.f;
  void resize(int numberLines);
  SystemParser::Description _des;
  SystemParser _parser;
  int _systemId, _fontSize;
  int _stateLins; /**< number of lines to display States */
  sf::Font _font;
  sf::Text _description;
  std::vector<sf::Text> _states;
  sf::RectangleShape _planetPic;
  sf::Vector2f _topLeft, _size;
  Quat _planetRotation;
  sf::Vector3f _planetRotationAxis;
  float _planetAngle = 0;
  static constexpr char PLANET_FRAGMENT_SHADER[] = R"V0G0N(
uniform sampler2D texture;
uniform mat3 rotation;

#define PI 3.1415926538
void main() {
  vec2 p = 2. * gl_TexCoord[0].xy - 1.;
  float r = length(p);
  if (r > 1.) {
    discard;
  }
  vec3 sp;
  sp.xy = p;
  sp.z = sqrt(1. - dot(p,p));
  sp = rotation * sp;
  vec2 uv;
  uv.x = atan(sp.x, sp.y)/(2.*PI);
  uv.x += 0.5;
  uv.y = acos(sp.z)/PI;
  if (abs(length(sp)-1.) > .0001) {
    gl_FragColor = vec4(0., 0., 1., 1.);
  } else {
    gl_FragColor = texture2D(texture, uv);
  }
 }
  )V0G0N";
  void loadShader();
  std::unique_ptr<sf::Shader> _planetShader{nullptr};
};
