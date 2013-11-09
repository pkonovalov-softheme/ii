#ifdef FAST_RANDOM

#pragma once
#include <random>
#include "BransGlobals.h"

namespace Brans
{
	using namespace std;

	class RandomProviderBase
	{
	protected:
		static random_device rd;
		static mt19937 rnb;
	};

	class RandomValuesProvider : public RandomProviderBase
	{
	public:
		RandomValuesProvider(mainDataType upperLimit);
		mainDataType GetNextValue();
		static mainDataType GetNextValue(mainDataType upperLimit);
	private:
		//mainDataType _upperLimit;
		uniform_int_distribution<int> _values_dist;
	};

	class RandomOperatorsProvider : public RandomProviderBase
	{
	public:
		static mainDataType GetNextOperator();
	};
}

#endif