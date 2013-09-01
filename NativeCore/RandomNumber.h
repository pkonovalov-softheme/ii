#pragma once

#include "Operator.h"
#include "Entity.h"

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
				class RandomNumber : public Operator
				{
				private:
					Random *const _rnd;

				public:
					RandomNumber(Entity *thisEntity);

					virtual void Action() override;
				};
			}
		}
	}
}
