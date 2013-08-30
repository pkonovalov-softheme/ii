#pragma once

#include "../OperatorsImplimentation/Operator.h"
#include "../Entity.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading::Tasks;
using namespace AI::Core::OperatorsImplimentation::BasicOperators;

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{
				class CreateOperator : public Operator
				{
					/// <summary>
					/// Create new operator of specified type and returns ID of new created operator. 
					/// </summary>
					/// <param name="thisEntity"></param>
				public:
					CreateOperator(Entity *thisEntity);

					virtual void Action() override;

				private:
					const unsigned long long &getOperatorTypeToAdd() const;

					//We don't using Activator because of it's bad performance. http://rogeralsing.com/2008/02/28/linq-expressions-creating-objects is better but still 2x slower than 'new'.
					private *operator CreateOperatorInternal();
				};
			}
		}
	}
}
