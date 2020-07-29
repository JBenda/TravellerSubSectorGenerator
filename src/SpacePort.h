#pragma once

#include <iosfwd>

class SpacePort
{
public:
	enum SPACE_PORT_TYPE { X, E, D, C, B, A };
	static SPACE_PORT_TYPE getSpacePort(int val);
};

std::ostream& operator<<(std::ostream& os, SpacePort::SPACE_PORT_TYPE type);
