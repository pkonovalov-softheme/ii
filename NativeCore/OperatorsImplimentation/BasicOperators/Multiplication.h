#pragma once

#include "../OperatorsImplimentation/Operator.h"
#include "../Entity.h"

using namespace AI::Core::ChannelsImplimentation;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{
				class Multiplication : public Operator
				{
				public:
					Multiplication(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
