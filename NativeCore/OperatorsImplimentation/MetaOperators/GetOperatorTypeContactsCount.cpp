#include "GetOperatorTypeContactsCount.h"

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

				GetOperatorContactsCount::GetOperatorContactsCount(Entity *thisEntity) : ChannelOperator(thisEntity)
				{
					setEnterContactsCount(1);
				}

				void GetOperatorContactsCount::Action()
				{
					ExitContacts->SetValue(getThisEntity()->getOperators()[getTargetOperatorId()]->OperatorType);
				}

				const unsigned long long &GetOperatorContactsCount::getTargetOperatorId() const
				{
					return EnterContacts[0]->Value;
				}
			}
		}
	}
}
