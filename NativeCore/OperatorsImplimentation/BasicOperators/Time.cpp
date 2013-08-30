#include "Time.h"

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

				Time::Time(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(0);
				}

				void Time::Action()
				{
					ExitContacts->SetValue(static_cast<unsigned long long>(DateTime::UtcNow.Ticks));
				}
			}
		}
	}
}
