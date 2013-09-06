#include "stdafx.h"
#include "Entity.h"
#include <time.h>

namespace Brans 
{

	Entity::Entity(void)
	{
		InitializeOpTypesCC();
	}

	void Entity::InitializeOpTypesCC()
	{
		_operatorTypeContactCount[OperatorsTypes::CreateChannel] = 3;
		_operatorTypeContactCount[OperatorsTypes::CreateOperator] = 1;
		_operatorTypeContactCount[OperatorsTypes::DeleteChannel] = 2;
		_operatorTypeContactCount[OperatorsTypes::Division] = 2;
		_operatorTypeContactCount[OperatorsTypes::Equal] = 1;
		_operatorTypeContactCount[OperatorsTypes::GetOperatorContactsCount] = 1;
		_operatorTypeContactCount[OperatorsTypes::GetOperatorId] = 1;
		_operatorTypeContactCount[OperatorsTypes::GetTypeOfOperator] = 1;
		_operatorTypeContactCount[OperatorsTypes::If] = 2;
		_operatorTypeContactCount[OperatorsTypes::IsChannelExists] = 3;
		_operatorTypeContactCount[OperatorsTypes::Minus] = 2;
		_operatorTypeContactCount[OperatorsTypes::Multiplication] = 2;
		_operatorTypeContactCount[OperatorsTypes::One] = 0;
		_operatorTypeContactCount[OperatorsTypes::Plus] = 2;
		_operatorTypeContactCount[OperatorsTypes::RandomNumber] = 1;
		_operatorTypeContactCount[OperatorsTypes::RemoveOperator] = 1;
		_operatorTypeContactCount[OperatorsTypes::Time] = 0;
		_operatorTypeContactCount[OperatorsTypes::Nothing] = 0;
	}

	mainDataType Entity::mGetChannelvalue(mainDataType operatorId, mainDataType contactId)
	{
		return _operators[operatorId][contactId]; 

		//mainDataType* val = (mainDataType*)&_operators[operatorId][contactId]; 
		//return *val;//need to test
		//if (val == nullptr)
		//	return 0;
		//else
		//	return *val;
	}

	void Entity::mSetOperatorOutValue(mainDataType operatorId, mainDataType value)
	{
		if (operatorId < operatorsMaxCount)
		_operators[operatorId][outputValueColumn] = value;
	}

	void Entity::mCreateChannel(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId)
	{
		if (fromOperator < operatorsMaxCount && toOperator < operatorsMaxCount && toOperatorContactId < operatorsTableWidth)
		_operators[toOperator][toOperatorContactId] = fromOperator;
	}

	mainDataType Entity::mIfChannelExists(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId)
	{
		if (!(fromOperator < operatorsMaxCount && toOperator < operatorsMaxCount && toOperatorContactId < operatorsTableWidth)) return 0;
			
		if (_operators[toOperator][toOperatorContactId] == fromOperator) return 1;
			
		return 0;
	}

	void Entity::mDeleteChannel(mainDataType toOperator, mainDataType toOperatorContactId)
	{
		if (toOperator < operatorsMaxCount && toOperatorContactId < operatorsTableWidth)
		_operators[toOperator][toOperatorContactId] = 0;
	}

	//To do: Add thread safe logic!!!
	void Entity::mCreateOperator(mainDataType operatorType)
	{
		_lastOperatorId++;
		_operators[_lastOperatorId][0] = operatorType;
	}

	mainDataType Entity::mGetOperatorType(mainDataType operatorId)
	{
		if (operatorId < operatorsMaxCount)
			return operType;
		else
			return 0; //we should use operators IDs started from 1
	}

	void Entity::mProcessInternal(mainDataType operatorId)
	{
		switch (operType)
		{
		case (OperatorsTypes::CreateChannel):
			Entity::mCreateChannel(fContValue, sContValue, tContValue);
			break;
		case (OperatorsTypes::CreateOperator):
			Entity::mCreateOperator(fContValue);
			break;
		case (OperatorsTypes::DeleteChannel):
			Entity::mDeleteChannel(fContValue, sContValue);
			break;
		case (OperatorsTypes::Division):
			if (sContValue > 0) {
				outValue = fContValue / sContValue;}
			break;
		case (OperatorsTypes::Equal):
				outValue = fContValue;
			break;
		case (OperatorsTypes::GetOperatorContactsCount):
				outValue = _operatorTypeContactCount[operType];
			break;
		case (OperatorsTypes::GetOperatorId):
				outValue = _operatorTypeContactCount[operType];
			break;
		case (OperatorsTypes::GetTypeOfOperator):
				outValue = operType;
			break;
		case (OperatorsTypes::If):
			if (fContValue > sContValue){
				outValue = 1;}
			else{
				outValue = 0;}
			break;
		case (OperatorsTypes::IsChannelExists):
			outValue = mIfChannelExists(fContValue, sContValue, tContValue);
			break;
		case (OperatorsTypes::Minus):
			outValue = fContValue - sContValue;
			break;
		case (OperatorsTypes::Multiplication):
			outValue = fContValue * sContValue;
			break;
		case (OperatorsTypes::Nothing):
			break;
		case (OperatorsTypes::One):
			outValue = 1;
			break;
		case (OperatorsTypes::Plus):
			outValue = fContValue + sContValue;
			break;
		case (OperatorsTypes::RandomNumber):
			//Not implemented!!!!
			break;
		case (OperatorsTypes::RemoveOperator):
			_operators[_lastOperatorId][0] = OperatorsTypes::Nothing;
			break;
		case (OperatorsTypes::Time):
			outValue = time(NULL);
			break;
		}
	}

}