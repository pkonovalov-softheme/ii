#include "If.h"
#include "stdafx.h"

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{

				If::If(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(3);
				}

				void If::Action()
				{
					auto currentValue = EnterContacts[0]->Value;
					auto downLimit = EnterContacts[1]->Value;
					auto upperLimit = EnterContacts[2]->Value;
					if (currentValue >= downLimit && currentValue < upperLimit)
					{
						ExitContacts->SetValue(1);
					}
					else
					{
						ExitContacts->SetValue(0);
					}
				}
			}
		}
	}
}
