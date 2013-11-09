#pragma once
class FastRandom
{
public:
	static void srand_sse(unsigned int seed);
	static void srand_sse();
	static void rand_sse(unsigned int*);
	static inline unsigned int randlim(unsigned int low, unsigned int high);
};

