#include "Entity.h"
#include "stdafx.h"

namespace AI
{
	namespace Core
	{
		mainDataType Entity::GetChannelvalue(mainDataType operatorId, mainDataType contactId)
		{
			mainDataType* val = (mainDataType*)&_operators[operatorId][contactId]; 
			return *val;//need to test
			//if (val == nullptr)
			//	return 0;
			//else
			//	return *val;
		}

		void Entity::SetOperatorOutValue(mainDataType operatorId, mainDataType value)
		{
			if (operatorId < operatorsMaxCount)
			_operators[operatorId][outputValueColumn] = value;
		}

		void Entity::CreateChannel(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId)
		{
			if (fromOperator < operatorsMaxCount && toOperator < operatorsMaxCount && toOperatorContactId < operatorsTableWidth)
			_operators[toOperator][toOperatorContactId] = (mainDataType)&_operators[fromOperator][outputValueColumn];
		}

		void Entity::DeleteChannel(mainDataType toOperator, mainDataType toOperatorContactId)
		{
			if (toOperator < operatorsMaxCount && toOperatorContactId < operatorsTableWidth)
			_operators[toOperator][toOperatorContactId] = 0;
		}

		mainDataType Entity::GetOperatorType(mainDataType operatorId)
		{
			if (operatorId < operatorsMaxCount)
				return _operators[operatorId][0];
			else
				return 0; //we should use operators IDs started from 1
		}
	}
}
