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
				class Equal : public Operator
				{
					/// <summary>
					/// Just repeats Enter on exit
					/// </summary>
				public:
					Equal(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
