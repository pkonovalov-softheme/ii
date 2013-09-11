#include "stdafx.h"
#include "Entity.h"
#include <time.h>

namespace Brans 
{
	Entity::Entity(void) : _operators()
	{
		_nextOperatorId = 1;
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
		_operatorTypeContactCount[OperatorsTypes::GetInputOperatorId] = 1;
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

	//Maybe inline will faster?? Chanek also memory usage
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

	void Entity::mCreateChannel(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId)
	{
		if (fromOperator > operatorsMaxCount)		    return;
		if (toOperator   > operatorsMaxCount)		    return;
		if (toOperatorContactId == 0)				    return;
		if (toOperatorContactId >= operatorsTableWidth) return;

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

	void Entity::mRemoveOperator(mainDataType operatorToRemove)
	{
		if (operatorToRemove < operatorsMaxCount)
			_operators[operatorToRemove][operatorTypeColumn] = OperatorsTypes::Nothing;
	}

	//To do: Add thread safe logic!!!
	void Entity::mCreateOperator(mainDataType operatorType)//To do: Add thread safe logic!!!
	{
		_operators[_nextOperatorId][0] = operatorType;
		_nextOperatorId++;
	}

	mainDataType Entity::mGetOperatorType(mainDataType operatorId)
	{
		if (operatorId < operatorsMaxCount)
			return _operators[operatorId][operatorTypeColumn];
		else
			return 0; //we should use operators IDs started from 1
	}

	bool Entity::mProcess(mainDataType operatorId)
	{
		#define fContValue GetInputValue(operatorId, 1) //value of first contact
		#define sContValue GetInputValue(operatorId, 2) //value of second contact
		#define tContValue GetInputValue(operatorId, 3) //value of third contact

		#define operType   _operators[operatorId][operatorTypeColumn] //type of the operator
		#define outValue   _operators[operatorId][outputValueColumn] //value of the operators output contact

		switch (operType)
		{
		case (CreateChannel):
			Entity::mCreateChannel(fContValue, sContValue, tContValue);
			break;
		case (CreateOperator):
			Entity::mCreateOperator(fContValue);
			break;
		case (DeleteChannel):
			Entity::mDeleteChannel(fContValue, sContValue);
			break;
		case (Division):
			if (sContValue > 0) {
				outValue = fContValue / sContValue;}
			break;
		case (Equal):
				outValue = fContValue;
			break;
		case (GetOperatorContactsCount):
				outValue = _operatorTypeContactCount[fContValue];
			break;
		case (GetInputOperatorId): //returns id of the operator witch have channel with the first contact of the GetOperatorId operator
				outValue = _operators[operatorId][1];
			break;
		case (GetTypeOfOperator):
				outValue = operType;
			break;
		case (If):
			if (fContValue > sContValue){
				outValue = 1;}
			else{
				outValue = 0;}
			break;
		case (IsChannelExists):
			outValue = mIfChannelExists(fContValue, sContValue, tContValue);
			break;
		case (Minus):
			outValue = fContValue - sContValue;
			break;
		case (Multiplication):
			outValue = fContValue * sContValue;
			break;
		case (Nothing):
			break;
		case (One):
			outValue = 1;
			break;
		case (Plus):
			outValue = fContValue + sContValue;
			break;
		case (RandomNumber):
			//Not implemented!!!!
			break;
		case (RemoveOperator):
			mRemoveOperator(fContValue);
			break;
		case (Time):
			outValue = time(NULL);
			break;
		case (Zero):
			return false;
		default:
			throw "Not implemented";
		}
		return true;
	}

	void Entity::mProcessLast()
	{
		mProcess(_nextOperatorId - 1);
	}

	mainDataType Entity::GetContactValue(mainDataType operatorId, mainDataType contactId) //Returns the value of the specific operator
	{
		return _operators[operatorId][contactId];
	}

	void Entity::SetContactValue(mainDataType operatorId, mainDataType contactId, mainDataType value) //Set up the value of the specific operator
	{
		_operators[operatorId][contactId] = value;
	}

	void Entity::SetInputValues(mainDataType operatorId, mainDataType fcontactValue, mainDataType scontactValue, mainDataType tcontactValue) //Set up the input values for the specific operator
	{
		SetInputValues (operatorId, fcontactValue, scontactValue);
		SetContactValue(operatorId, 3, tcontactValue);
	}

	void Entity::SetInputValues(mainDataType operatorId, mainDataType fcontactValue, mainDataType scontactValue) 
	{
		SetInputValues (operatorId, fcontactValue);
		SetContactValue(operatorId, 2, scontactValue);
	}

	void Entity::SetInputValues(mainDataType operatorId, mainDataType fcontactValue)
	{
		SetContactValue(operatorId, 1, fcontactValue);
	}

	mainDataType Entity::GetInputValue(mainDataType operatorId, mainDataType contactId)
	{
		mainDataType refOperId = GetContactValue(operatorId, contactId);
		if (refOperId == 0) 
			return 0;//test perf
		return _operators[refOperId][outputValueColumn];
	}

	mainDataType Entity::GetNextOperatorId()
	{
		return _nextOperatorId;
	}

	void Entity::mProcessAll()
	{
		for (mainDataType i = 0; i < operatorsMaxCount && mProcess(i); i++) {}
	}

}