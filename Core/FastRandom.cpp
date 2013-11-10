#pragma once
#include "stdafx.h"
#include "FastRandom.h"
#include <time.h>
#include "emmintrin.h"

namespace Brans
{
	//extern void srand_sse();
	//extern void rand_sse(unsigned int*);
	//inline unsigned int randlim(unsigned int low, unsigned int high){
	//	unsigned int ret;
	//	rand_sse(&ret);
	//	return ret % (high - low + 1) + low;

	///////////////////////////////////////////////////////////////////////////

	// Random Number Generation for SSE / SSE2

	// Source File

	// Version 0.1

	// Author Kipp Owens, Rajiv Parikh

	////////////////////////////////////////////////////////////////////////





	/*void FastRandom::SetSeed()
	{
		unsigned int seed = (unsigned int)time(0);
		cur_seed = _mm_set_epi32(seed, seed + 1, seed, seed + 1);
	}

	void FastRandom::SetSeed(unsigned int seed)
	{
		cur_seed = _mm_set_epi32(seed, seed + 1, seed, seed + 1);
	}*/



	
}

