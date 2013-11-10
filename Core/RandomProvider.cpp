#include "stdafx.h"
#include "RandomProvider.h"

namespace Brans
{
	static const unsigned short LastInternalOperType = OperatorsCount - 4; //Excluding Zero, External input, Output and Nothing
	static const unsigned short LastValidOperType = ExternalInput - 1;
	//static uniform_int_distribution<int> operTypes_dist(1, LastValidOperType);
	//static  FastRandom _fastrandom();

	mainDataType RandomOperatorsProvider::GetNextOperator()
	{
		//return FastRandom::randlim(1, LastValidOperType);
		return 1;
	}

	mainDataType  RandomValuesProvider::GetNextValue(mainDataType upperLimit)
	{
		return 1;
		//return FastRandom::randlim(1, upperLimit);
	}

	mainDataType RandomValuesProvider::GetNextValue()
	{
		return _fastrandom.GetRandom(1, _upperLimit);
	}

	RandomValuesProvider::RandomValuesProvider(mainDataType upperLimit) : _upperLimit(upperLimit)
	{}
}