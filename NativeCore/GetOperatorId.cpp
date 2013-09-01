#include "GetOperatorId.h"
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
using namespace AI::Core::ChannelsImplimentation;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{

				GetOperatorId::GetOperatorId(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(1);
				}

				void GetOperatorId::Action()
				{
					ExitContacts->SetValue(getEnterChannel()->getFromContact().getOper()->Id);
				}

				const AI::Core::ChannelsImplimentation::Channel &GetOperatorId::getEnterChannel() const
				{
					return EnterContacts[0];
				}
			}
		}
	}
}
