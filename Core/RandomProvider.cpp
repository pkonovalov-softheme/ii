#include "stdafx.h"
#include "RandomProvider.h"

namespace Brans
{
	random_device RandomOperatorsProvider::rd;
	mt19937 RandomOperatorsProvider::rnb(RandomOperatorsProvider::rd());
	const unsigned short LastInternalOperType = OperatorsCount - 4; //Excluding Zero, External input, Output and Nothing
	static uniform_int_distribution<int> operTypes_dist(1, LastInternalOperType);

	mainDataType RandomOperatorsProvider::GetNextOperator()
	{
		return operTypes_dist(rnb);
	}

	mainDataType  RandomValuesProvider::GetNextValue(mainDataType upperLimit)
	{
		uniform_int_distribution<int> values_dist(1, upperLimit);
		return values_dist(rnb);
	}

	mainDataType RandomValuesProvider::GetNextValue()
	{
		mainDataType ret = _values_dist(rnb);
		if (ret == 0)
		{
			ret = ret;
		}
		return ret;
	}

	RandomValuesProvider::RandomValuesProvider(mainDataType upperLimit) : _values_dist(1, upperLimit)
	{
		//_upperLimit = upperLimit;
	}
}