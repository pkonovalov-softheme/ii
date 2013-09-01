#include "Equal.h"
#include "stdafx.h"

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{

				Equal::Equal(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(1);
				}

				void Equal::Action()
				{
					ExitContacts->SetValue(EnterContacts[0]->Value);
				}
			}
		}
	}
}
