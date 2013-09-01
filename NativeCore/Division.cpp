#include "Division.h"
#include "stdafx.h"

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{

				Division::Division(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(2);
				}

				void Division::Action()
				{
					auto value = EnterContacts[0]->Value / EnterContacts[1]->Value;
					ExitContacts->SetValue(value);
				}
			}
		}
	}
}
