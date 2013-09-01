#include "Power.h"
#include "stdafx.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace AI::Core::ChannelsImplimentation;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{

				Power::Power(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(2);
				}

				void Power::Action()
				{
					auto value = static_cast<unsigned long long>(pow(EnterContacts[0]->Value, EnterContacts[1]->Value));
					ExitContacts->SetValue(value);
				}
			}
		}
	}
}
