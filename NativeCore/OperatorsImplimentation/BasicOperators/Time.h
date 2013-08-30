#pragma once

#include "../OperatorsImplimentation/Operator.h"
#include "../Entity.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{
				class Time : public Operator
				{
					/// <summary>
					/// Returns UTC ticks
					/// </summary>
				public:
					Time(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
