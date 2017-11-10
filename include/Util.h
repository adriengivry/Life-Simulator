#pragma once
#include <cstdint>
#include <random>

inline uint16_t random_between(const uint16_t p_min, const uint16_t p_max)
{
	return rand() % (p_max - p_min + 1) + p_min;
}
