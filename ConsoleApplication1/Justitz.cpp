#include "Justize.h"

Justize::Justize(uint8_t mainFractionType)
{
	int jl = Dice::role2W6() - 7 + mainFractionType;
	if (jl > 9) jl = 9;
	if (jl < 0) jl = 0;
	for (int i = 0; i < (uint8_t)JUSTIZE_PARTS::END - 1; ++i)
	{
		justizeLvl[i] = jl;
	}
}