#include "CreateChannel.h"
#include "Channel.h"
#include "Contact.h"
#include "ChannelsTable.h"
#include "stdafx.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
using namespace AI::Core::ChannelsImplimentation;
namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{

				CreateChannel::CreateChannel(Entity *thisEntity) : ChannelOperator(thisEntity)
				{
				}

				void CreateChannel::Action()
				{
					Channel *channel = nullptr;
					try
					{
						unsigned long long fromOpExitContactsCount = static_cast<unsigned long long>(getFromOperator()->ExitContacts->size());

						//We will ignore requests when one of Contacts is used by other channel to require old channel be deleted before create new.
						if (getToOperator()->EnterContacts[getToOperatorContactNumber()] != nullptr || getFromOperator()->ExitContacts[fromOpExitContactsCount] != nullptr)
						{
							return;
						}

						auto toContact = Contact(getToOperator(), getToOperatorContactNumber());
						auto fromContact = Contact(getFromOperator(), fromOpExitContactsCount);
						channel = new Channel(fromContact, toContact);
						getFromOperator()->ExitContacts->push_back(channel);
						getToOperator()->EnterContacts[getToOperatorContactNumber()] = channel;
						getThisEntity()->getChannelsTable()->Add(ChannelTableKey(getFromOperator(), getToOperator()), channel);
					}
					catch (ArgumentOutOfRangeException e1)
					{
						if (getFromOperator()->ExitContacts->Last() == channel)
						{
							getFromOperator()->ExitContacts->RemoveAt(getFromOperator()->ExitContacts->size());
						}
					}
				}
			}
		}
	}
}
