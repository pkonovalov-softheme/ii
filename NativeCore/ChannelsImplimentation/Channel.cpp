#include "Channel.h"

namespace AI
{
	namespace Core
	{
		namespace ChannelsImplimentation
		{

			Channel::Channel(Contact fromContact, Contact toContact) : _fromContact(fromContact), _toContact(toContact)
			{
				InitializeInstanceFields();
			}

			const AI::Core::Contact &Channel::getFromContact() const
			{
				return _fromContact;
			}

			const AI::Core::Contact &Channel::getToContact() const
			{
				return _toContact;
			}

			void Channel::InitializeInstanceFields()
			{
				Value = 0;
			}
		}
	}
}
