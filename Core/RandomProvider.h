#pragma once
#include <random>
#include "BransGlobals.h"

namespace Brans
{
	class RandomProvider
	{
	private:
		static std::random_device rd;
		static std::mt19937 rnb;
	public:
		static mainDataType GetNextValue(mainDataType upperLimit);
	};
}

