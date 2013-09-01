#pragma once

#include "Entity.h"
#include "Channels.h"

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
				enum class OperatorsTypes
				{
					Division,
					Equal,
					If,
					Minus,
					Multiplication,
					One,
					Plus,
					Power,
					RandomNumber,
					Time,
					CreateChannel,
					CreateOperator,
					DeleteChannel,
					GetTypeOfOperator,
					IsChannelExists,
					RemoveOperator,
					GetOperatorId
				};

			/// <summary>
			/// Operator object. Base object that connects virtual & real world.
			/// </summary>
			class Operator
			{
			protected:
					private:
						Entity *privateThisEntity;
					protected:
						const Entity &getThisEntity() const;
						void setThisEntity(const Entity &value);
					private:
						unsigned long long privateId;
					public:
						const unsigned long long &getId() const;
						void setId(const unsigned long long &value);
					private:
						unsigned long long privateOperatorType;
					public:
						const unsigned long long &getOperatorType() const;
						void setOperatorType(const unsigned long long &value);
				Channels *ExitContacts; //To do: Add safe thread logic for external setter
				Channels *EnterContacts; //To do: Add safe thread logic for external setter
			private:
				unsigned short _enterContactsCount;

			public:
				const unsigned short &getEnterContactsCount() const;
				protected:
				void setEnterContactsCount(const unsigned short &value);

				virtual void Action() = 0;

				/// <summary>
				/// Initialize new Operator
				/// </summary>
				/// <param name="thisEntity">Operators collection of the Entity</param>
			protected:
				Operator(Entity *thisEntity);

			private:
				void InitializeInstanceFields();
			};
		}
	}
}
