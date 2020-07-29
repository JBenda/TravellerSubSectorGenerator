#include "SpacePort.h"

#include <iostream>

SpacePort::SPACE_PORT_TYPE SpacePort::getSpacePort(int val)
{
    val--;
    val /= 2;
    if (val > A)
        std::cerr << "ERROR Spaceport Calculation" << std::endl;
    return SPACE_PORT_TYPE(val);
}
std::ostream& operator<<(std::ostream& os, SpacePort::SPACE_PORT_TYPE type) {
  using SP = SpacePort::SPACE_PORT_TYPE;
  static constexpr char NAMES[] = {
    [SP::X] = 'X',
    [SP::E] = 'E',
    [SP::D] = 'D',
    [SP::C] = 'C',
    [SP::B] = 'B',
    [SP::A] = 'A'
  };
  os << NAMES[type];
  return os;
}
