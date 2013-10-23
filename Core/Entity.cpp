#include "stdafx.h"
#include "Entity.h"


namespace Brans 
{
	//Todo: remove _operator initialization with 0 to improve perfomance
	Entity::Entity() : _operators()
	{
		//_chmanager = nullptr;
		_nextOperatorId = 1;
		InitializeOpTypesCC();
		InitializeInputsAndOutputs();
	}

	Entity::~Entity() 
	{

	}

	void Entity::InitializeInputsAndOutputs()
	{
		for (mainDataType i = 0; i < ExternalOutputsCount; i++)  {mCreateOperator(ExternalOutput);}
		for (mainDataType i = 0; i < ExternalInputsCount; i++)  {mCreateOperator(ExternalInput);}
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

	//Maybe inline will faster?? Check also memory usage
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
		if (fromOperator >= operatorsMaxCount)		    return;
		if (toOperator   >= operatorsMaxCount)		    return;
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
		if (_nextOperatorId < operatorsMaxCount)
		{
			_operators[_nextOperatorId][0] = operatorType;
			_nextOperatorId++;
		}
	}

	mainDataType Entity::mGetOperatorType(mainDataType operatorId)
	{
		if (operatorId < operatorsMaxCount)
			return _operators[operatorId][operatorTypeColumn];
		else
			return 0; //we should use operators IDs started from 1
	}

	mainDataType Entity::mGetNewRandomVal(mainDataType upperLimit)
	{
		return RandomValuesProvider::GetNextValue(upperLimit);
	}

	void Entity::mProcess(mainDataType operatorId)
	{
		#define fContValue GetInputValue(operatorId, 1) //value of first contact
		#define sContValue GetInputValue(operatorId, 2) //value of second contact
		#define tContValue GetInputValue(operatorId, 3) //value of third contact

		#define operType   _operators[operatorId][operatorTypeColumn] //type of the operator
		#define outValue   _operators[operatorId][outputValueColumn] //value of the operators output contact
		
		mainDataType targetOp, targetOpType;

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
		case (GetOperatorContactsCount) :
			targetOp = _operators[operatorId][1];
			targetOpType = _operators[targetOp][0];
			outValue = _operatorTypeContactCount[targetOpType];
			break;
		case (GetInputOperatorId): //returns id of the operator witch have channel with the first contact of the GetOperatorId operator
				outValue = _operators[operatorId][1];
			break;
		case (GetTypeOfOperator): //returns the operator type witch have channel with the first contact of this oper
				outValue = mGetOperatorType(_operators[operatorId][1]);
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
			outValue = mGetNewRandomVal(fContValue);
			break;
		case (RemoveOperator):
			mRemoveOperator(fContValue);
			break;
		case (Time):
			outValue = time(NULL);
			break;
		case (Zero):
			throw "Zero operator!";
			break;
		case (ExternalInput):
				//outValue = _chmanager->GetEntityExternalInput(operatorId - 1);
			break;
		default:
			throw "Not implemented";
		}
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
			return 0;//test performance
		return _operators[refOperId][outputValueColumn];
	}

	mainDataType Entity::GetNextOperatorId()
	{
		return _nextOperatorId;
	}

	void Entity::mProcessAll()
	{
		const mainDataType firstInput = ExternalOutputsCount + 1;

		//Processing external inputs and all internal operators
		for (mainDataType i = firstInput; i < _nextOperatorId; i++) 
		{
			mProcess(i);
		}

		bool wasError = false;

		////Processing external outputs
		//for (mainDataType i = 1; i <= ExternalOutputsCount; i++) 
		//{
		//	if (_chmanager->GetCorrectAnswer(i) != GetContactValue(i, outputValueColumn))
		//	{
		//		wasError = true;
		//		break;
		//	}
		//}

		//if (wasError)
		//	_chmanager->ReportFailure();
		//else
		//	_chmanager->ReportSuccess();
	}

	void Entity::SetExternalInputValue(mainDataType inputOperId)
	{
		_operators[_nextOperatorId][operatorTypeColumn] = inputOperId;
	}

	mainDataType Entity::GetOperatorsCount()
	{
		return _nextOperatorId;
	}

	//void Entity::StartChallengeLine(ChallengeManager* chline)
	//{
	//	_chmanager = chline;
	//}

}