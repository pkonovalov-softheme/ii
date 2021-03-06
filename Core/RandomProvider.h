#pragma once
#include <random>
#include "BransGlobals.h"
#include "FastRandom.h"

namespace Brans
{
	using namespace std;

	class RandomProviderBase
	{
	protected:
		static void SetSeed();
		static void SetSeed(unsigned int seed);
		//FastRandmon _fastrandom;
		//FastRandom _fastrandom;
	};

	class RandomValuesProvider : public RandomProviderBase
	{
	public:
		RandomValuesProvider(mainDataType upperLimit);
		RandomValuesProvider(mainDataType upperLimit, mainDataType downLimit);
		mainDataType GetNextValue();
		static mainDataType GetNextValue(mainDataType upperLimit);
	private:
		mainDataType _upperLimit;
		mainDataType _downLimit;
	};

	class RandomOperatorsProvider : public RandomProviderBase
	{
	public:
		static mainDataType GetNextOperator();
	};
}