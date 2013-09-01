#pragma once

#include "Operator.h"
#include "Entity.h"

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{
				class Division : public Operator
				{
				public:
					Division(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
