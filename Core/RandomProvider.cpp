#include "stdafx.h"
#include "RandomProvider.h"

namespace Brans
{
	//static const unsigned short LastValidOperType = ExternalInput - 1;
	//static uniform_int_distribution<int> operTypes_dist(1, LastValidOperType);
	//static  FastRandom _fastrandom();

	mainDataType RandomOperatorsProvider::GetNextOperator()
	{
		return GetRandom(1, ExternalInput);
	}

	mainDataType  RandomValuesProvider::GetNextValue(mainDataType upperLimit)
	{
		return GetRandom(1, upperLimit);
	}

	mainDataType RandomValuesProvider::GetNextValue()
	{
		return GetRandom(_downLimit, _upperLimit);
	}

	RandomValuesProvider::RandomValuesProvider(mainDataType upperLimit) : _upperLimit(upperLimit), _downLimit(1) {}
	RandomValuesProvider::RandomValuesProvider(mainDataType upperLimit, mainDataType downLimit) : 
		_upperLimit(upperLimit), _downLimit(downLimit) 	{}
}