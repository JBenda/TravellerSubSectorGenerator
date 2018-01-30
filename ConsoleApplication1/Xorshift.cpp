#include "Xorshift128.h"

void Xorshift128::setValues(uint32_t v1, uint32_t v2, uint32_t v3)
{
	_values[0] = v1;
	_values[1] = v2;
	_values[3] = v3;
}
uint32_t Xorshift128::getNextUInt()
{
	uint32_t s, t = _values[3];
	t ^= t << 11;
	t ^= t >> 8;
	_values[3] = _values[2];
	_values[2] = _values[1];
	_values[1] = _values[0];
	s = _values[0];
	t ^= s;
	t ^= s >> 19;
	_values[0] = t;
	return t;
}

uint32_t Xorshift128::getLastUInt()
{
	return _values[0];
}
