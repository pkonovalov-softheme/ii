#include "stdafx.h"
#include "RandomProvider.h"

#ifndef FAST_RANDOM

namespace Brans
{
	random_device RandomOperatorsProvider::rd;
	mt19937 RandomOperatorsProvider::rnb(RandomOperatorsProvider::rd());
	static const unsigned short LastInternalOperType = OperatorsCount - 4; //Excluding Zero, External input, Output and Nothing
	static const unsigned short LastValidOperType = ExternalInput - 1;
	static uniform_int_distribution<int> operTypes_dist(1, LastValidOperType);

	mainDataType RandomOperatorsProvider::GetNextOperator()
	{
		return operTypes_dist(rnb);
	}

	mainDataType  RandomValuesProvider::GetNextValue(mainDataType upperLimit)
	{
		uniform_int_distribution<mainDataType> values_dist(1, upperLimit);
		return values_dist(rnb);
	}

	mainDataType RandomValuesProvider::GetNextValue()
	{
		mainDataType ret = _values_dist(rnb);
		return ret;
	}

	RandomValuesProvider::RandomValuesProvider(mainDataType upperLimit) : _values_dist(1, upperLimit)
	{}
}

#endif

#ifdef FAST_RANDOM

namespace Brans
{
	static const unsigned short LastInternalOperType = OperatorsCount - 4; //Excluding Zero, External input, Output and Nothing
	static const unsigned short LastValidOperType = ExternalInput - 1;
	static uniform_int_distribution<int> operTypes_dist(1, LastValidOperType);

	mainDataType RandomOperatorsProvider::GetNextOperator()
	{
		return FastRandom::randlim(1, LastValidOperType);
	}

	mainDataType  RandomValuesProvider::GetNextValue(mainDataType upperLimit)
	{
		return FastRandom::randlim(1, upperLimit);
	}

	mainDataType RandomValuesProvider::GetNextValue()
	{
		return FastRandom::randlim(1, _upperLimit);
	}

	RandomValuesProvider::RandomValuesProvider(mainDataType upperLimit) : _upperLimit(upperLimit)
	{}
}

#endif