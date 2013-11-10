#pragma once

namespace Brans
{
	class FastRandom
	{
	public:
		FastRandom();
		unsigned int GetRandom(unsigned int low, unsigned int high);
	private:
		void rand_sse(unsigned int* result);
	};
//#ifndef SSERand_GUARD_130848549
//#define SSERand_GUARD_130848549
//	extern void srand_sse();
//	extern void rand_sse(unsigned int*);
//
//	inline unsigned int randlim(unsigned int low, unsigned int high)
//	{
//		unsigned int ret;
//		rand_sse(&ret);
//		return ret % (high - low + 1) + low;
//	}
//
//#endif

}

