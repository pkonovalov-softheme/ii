#pragma once

#include "../OperatorsImplimentation/Operator.h"
#include "../Entity.h"
#include <cmath>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace AI::Core::ChannelsImplimentation;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{
				class Power : public Operator
				{
				public:
					Power(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
