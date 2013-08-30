#include "IsChannelExists.h"
#include "ChannelsImplimentation/ChannelsTable.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace AI::Core::ChannelsImplimentation;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{

				IsChannelExists::IsChannelExists(Entity *thisEntity) : ChannelOperator(thisEntity)
				{
				}

				void IsChannelExists::Action()
				{
					bool result = getThisEntity()->getChannelsTable()->ContainsKey(ChannelTableKey(getFromOperator(), getToOperator()));
					ExitContacts->SetValue(static_cast<unsigned long long>(result));
				}
			}
		}
	}
}
