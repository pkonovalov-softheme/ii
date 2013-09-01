#include "RemoveOperator.h"
#include "stdafx.h"

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
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{

				const unsigned long long &RemoveOperator::getOperatorIdToRemove() const
				{
					return EnterContacts[0]->Value;
				}

				RemoveOperator::RemoveOperator(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(1);
				}

				void RemoveOperator::Action()
				{
					ExitContacts->SetValue(static_cast<unsigned long long>(getThisEntity()->getOperators()->erase(getOperatorIdToRemove())));
				}
			}
		}
	}
}
