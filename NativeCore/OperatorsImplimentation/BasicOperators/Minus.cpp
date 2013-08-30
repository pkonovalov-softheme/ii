#include "Minus.h"

using namespace AI::Core::ChannelsImplimentation;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{

				Minus::Minus(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(2);
				}

				void Minus::Action()
				{
					auto value = EnterContacts[0]->Value - EnterContacts[1]->Value;
					ExitContacts->SetValue(value);
				}
			}
		}
	}
}
