#include "One.h"

using namespace AI::Core::ChannelsImplimentation;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace BasicOperators
			{

				One::One(Entity *thisEntity) : Operator(thisEntity)
				{
				}

				void One::Action()
				{
					ExitContacts->SetValue(1);
				}
			}
		}
	}
}
