#pragma once

#include "Operator.h"
#include "Entity.h"

namespace AI
{
	namespace Core
	{
		namespace OperatorsImplimentation
		{
			namespace MetaOperators
			{
				/// <summary>
				/// Base for the "meta-operators" that are managing Channels and Operators. 
				/// </summary>
				class ChannelOperator : public Operator
				{
				protected:
					const unsigned long long &getFromOperatorId() const;
					void setFromOperatorId(const unsigned long long &value);

					const Operator &getFromOperator() const;
					void setFromOperator(const Operator &value);

					const unsigned long long &getToOperatorId() const;
					void setToOperatorId(const unsigned long long &value);

					const Operator &getToOperator() const;
					void setToOperator(const Operator &value);

					const unsigned long long &getToOperatorContactNumber() const;
					void setToOperatorContactNumber(const unsigned long long &value);

					ChannelOperator(Entity *thisEntity);
				};
			}
		}
	}
}
