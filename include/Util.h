#pragma once
#include <cstdint>
#include <random>

static bool __FIRST_RANDOM = true;

inline uint16_t random_between(const uint16_t p_min, const uint16_t p_max)
{
	if (__FIRST_RANDOM)
	{
		srand(time(nullptr));
		__FIRST_RANDOM = false;
	}

	return p_min + rand() % (p_max + 1 - p_min);
}
