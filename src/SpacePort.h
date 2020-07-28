#pragma once

class SpacePort
{
public:
	enum SPACE_PORT_TYPE { X, E, D, C, B, A };
	static SPACE_PORT_TYPE getSpacePort(int val)
	{
		val--;
		val /= 2;
		if (val > A)
			std::cerr << "ERROR SpapePort Caclulation" << std::endl;
		return (SPACE_PORT_TYPE)val;
	}
};