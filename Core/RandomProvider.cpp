#include "stdafx.h"
#include "RandomProvider.h"

namespace Brans
{
	random_device RandomOperatorsProvider::rd;
	mt19937 RandomOperatorsProvider::rnb(RandomOperatorsProvider::rd());
	static uniform_int_distribution<int> operTypes_dist(1, OperatorsCount);

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
		return _values_dist(rnb);
	}

	RandomValuesProvider::RandomValuesProvider(mainDataType upperLimit) : _values_dist(1, upperLimit)
	{
		_upperLimit = upperLimit;
	}
}