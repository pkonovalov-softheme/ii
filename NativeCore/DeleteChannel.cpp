#include "DeleteChannel.h"
#include "Channel.h"
#include "ChannelsTable.h"
#include "stdafx.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace AI::Core::ChannelsImplimentation;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{

				DeleteChannel::DeleteChannel(Entity *thisEntity) : ChannelOperator(thisEntity)
				{
				}

				void DeleteChannel::Action()
				{
					try
					{
						Channel *channel;
						auto chktey = ChannelTableKey(getFromOperator(), getToOperator());
						try
						{
							channel = getThisEntity()->getChannelsTable()[chktey];
						}
						catch (KeyNotFoundException e1)
						{
							return;
						}

//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete getFromOperator()->ExitContacts[channel->getFromContact().getContactNumber()];
//C# TO C++ CONVERTER WARNING: C# to C++ Converter converted the original 'null' assignment to a call to 'delete', but you should review memory allocation of all pointer variables in the converted code:
						delete getToOperator()->EnterContacts[channel->getToContact().getContactNumber()];
						getThisEntity()->getChannelsTable()[chktey] = nullptr;
					}
					catch (ArgumentOutOfRangeException e2)
					{
					}
				}
			}
		}
	}
}
