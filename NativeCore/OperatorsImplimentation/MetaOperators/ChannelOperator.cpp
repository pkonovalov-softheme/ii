#include "ChannelOperator.h"

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{

				const unsigned long long &ChannelOperator::getFromOperatorId() const
				{
					return EnterContacts[0]->Value;
				}

				void ChannelOperator::setFromOperatorId(const unsigned long long &value)
				{
					EnterContacts[0]->Value = value;
				}

				const AI::Core::OperatorsImplimentation::Operator &ChannelOperator::getFromOperator() const
				{
					return getThisEntity()->getOperators()[getFromOperatorId()];
				}

				void ChannelOperator::setFromOperator(const Operator &value)
				{
					setFromOperatorId(value->Id);
				}

				const unsigned long long &ChannelOperator::getToOperatorId() const
				{
					return EnterContacts[1]->Value;
				}

				void ChannelOperator::setToOperatorId(const unsigned long long &value)
				{
					EnterContacts[1]->Value = value;
				}

				const AI::Core::OperatorsImplimentation::Operator &ChannelOperator::getToOperator() const
				{
					return getThisEntity()->getOperators()[getToOperatorId()];
				}

				void ChannelOperator::setToOperator(const Operator &value)
				{
					setToOperatorId(value->Id);
				}

				const unsigned long long &ChannelOperator::getToOperatorContactNumber() const
				{
					return EnterContacts[2]->Value;
				}

				void ChannelOperator::setToOperatorContactNumber(const unsigned long long &value)
				{
					EnterContacts[2]->Value = value;
				}

				ChannelOperator::ChannelOperator(Entity *thisEntity) : Operator(thisEntity)
				{
					setEnterContactsCount(3);
				}
			}
		}
	}
}
