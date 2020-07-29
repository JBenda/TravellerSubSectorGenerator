#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "System.h"

class SystemParser
{
public:
  struct Description
  {
    std::vector<std::string> states;
    std::string description;
    std::unique_ptr<sf::Texture> texPlanet{nullptr};
  };
  SystemParser(const std::string& folderPath) : _fPath(folderPath) {}
  SystemParser(std::string&& folderPath) : _fPath{folderPath} {}

  void parse(const System& sys, Description& des) const
  {
    des.states = generateStateText(sys);
    des.description = generateText(sys);
    sf::Image img = generatePicture(sys);
    if (!des.texPlanet) {
      des.texPlanet = std::make_unique<sf::Texture>();
      des.texPlanet->loadFromImage(img);
      des.texPlanet->setRepeated(true);
    } else {
      des.texPlanet->update(img);
    }
  }
private:
  void states(Description& des) const{}
  std::vector<std::string> generateStateText(const System& sys) const
  {
    std::vector<std::string> stat;
    for(int i = 0; i < 12; ++i)
      stat.push_back("Hiy: asasasasasa");
    return stat;
  }
  void text(Description& des) const{}
  std::string generateText(const System& sys) const{ return sys.getSystemCode(); }
  /** load Image from file if exist, else generate new
   * \param des Description refrenc
   */
  void image(Description& des) const{}
  /** generate Planet picture from System informations
   * \param sys System referrenz for generate picture
   */
  sf::Image generatePicture(const System& sys) const;
  const std::string& _fPath;
};
