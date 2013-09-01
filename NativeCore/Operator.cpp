#include "Operator.h"
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

			const AI::Core::Entity &Operator::getThisEntity() const
			{
				return privateThisEntity;
			}

			void Operator::setThisEntity(const Entity &value)
			{
				privateThisEntity = value;
			}

			const unsigned long long &Operator::getId() const
			{
				return privateId;
			}

			void Operator::setId(const unsigned long long &value)
			{
				privateId = value;
			}

			const unsigned long long &Operator::getOperatorType() const
			{
				return privateOperatorType;
			}

			void Operator::setOperatorType(const unsigned long long &value)
			{
				privateOperatorType = value;
			}

			const unsigned short &Operator::getEnterContactsCount() const
			{
				return _enterContactsCount;
			}

			void Operator::setEnterContactsCount(const unsigned short &value)
			{

				EnterContacts = new Channels(value);
				_enterContactsCount = value;
			}

			Operator::Operator(Entity *thisEntity)
			{
				InitializeInstanceFields();
				setThisEntity(thisEntity);
				setId(getThisEntity()->getOperators()->GetNewUniqueId());
				ExitContacts = new Channels(1);
			}

			void Operator::InitializeInstanceFields()
			{
				_enterContactsCount = 0;
			}
		}
	}
}
