#pragma once

class Water
{
public:
	static int wmFromAtmoTemp(int atmo, int temp)
	{
		int wm = 0;
		if (atmo != 13)
		{
			if (temp >= 10)
				wm -= 4;
			if (temp >= 12)
				wm -= 2;
		}
		if (atmo <= 1 || (atmo >= 10 && atmo <= 12))
			wm -= 4;
		return wm;
	}
};