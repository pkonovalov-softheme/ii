#pragma once
#include "Entity.h"

namespace Brans
{
	struct EntityStats
	{
		Entity id;
		double effectiveness;
		bool results[TotalChallengesCount]; // 
		mainDataType curAnswerId;
	};
}