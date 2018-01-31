#pragma once

#include <stdint.h>

class Xorshift128
{
private:
	uint32_t _values[3];
	static Xorshift128 s_instance;
public:
	static Xorshift128 *instance()
	{
			return &s_instance;
	}
	void setValues(uint32_t v1, uint32_t v2, uint32_t v3);
	uint32_t getNextUInt();
	uint32_t getLastUInt();
};