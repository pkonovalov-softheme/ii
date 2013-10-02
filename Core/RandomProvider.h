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

	class RandomOperatorsProvider : RandomProviderBase
	{
	public:
		static mainDataType GetNextOperator();
	};

	class RandomConnectionsProvider : RandomProviderBase
	{
	public:
		RandomConnectionsProvider(mainDataType operatorsCount);
		~RandomConnectionsProvider(void);
		mainDataType GetNextConnectedOper();
	private:
		uniform_int_distribution<int> connections_dist;
	};
}

