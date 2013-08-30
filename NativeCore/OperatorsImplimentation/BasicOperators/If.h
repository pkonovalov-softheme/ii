#pragma once

#include "../OperatorsImplimentation/Operator.h"
#include "../Entity.h"

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{
				class If : public Operator
				{
				public:
					If(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
