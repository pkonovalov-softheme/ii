#include "RandomNumber.h"
#include "stdafx.h"

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

				RandomNumber::RandomNumber(Entity *thisEntity) : Operator(thisEntity), _rnd(new Random())
				{
					setEnterContactsCount(1);
				}

				void RandomNumber::Action()
				{
					auto value = static_cast<unsigned long long>(_rnd->NextDouble() * EnterContacts[0]->Value);
					ExitContacts->SetValue(value);
				}
			}
		}
	}
}
