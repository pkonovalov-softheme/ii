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

	RandomConnectionsProvider::RandomConnectionsProvider(mainDataType operatorsCount) : connections_dist(1, operatorsCount)
	{
	}

	mainDataType  RandomConnectionsProvider::GetNextConnectedOper()
	{
		return connections_dist(rnb);
	}
}