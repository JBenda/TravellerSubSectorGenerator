#pragma once

class Tempreture
{
public:
	static int atmoToWm(int atmo)
	{
		switch (atmo)
		{
		case 2:  case 3:			return -2;
		case 4:  case 5: case 14:	return -1;
		case 6:  case 7:			return  0;
		case 8:  case 9:			return  1;
		case 10 :case 13: case 15:	return  2;
		case 11: case 12:			return  6;
		default: std::cerr << "atmo out of range" << std::endl;
			return 0;
		}
	}
};