#include "stdafx.h"
#include "RandomProvider.h"

namespace Brans
{
	std::random_device RandomProvider::rd;
	std::mt19937 RandomProvider::rnb(RandomProvider::rd());

	mainDataType RandomProvider::GetNextValue(mainDataType upperLimit)
	{
		std::uniform_int_distribution<int> uniform_dist(1, upperLimit);
		return uniform_dist(rnb);
	}
}