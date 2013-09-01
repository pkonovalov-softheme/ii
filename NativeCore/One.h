#pragma once

#include "Operator.h"
#include "Entity.h"

using namespace AI::Core::ChannelsImplimentation;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{
				class One : public Operator
				{
					/// <summary>
					/// Always 1
					/// </summary>
				public:
					One(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
