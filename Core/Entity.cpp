#include "stdafx.h"
#include "Entity.h"
#include "ChallengeManager.h"

namespace Brans 
{
	mainDataType EntetiesProcessed = 0;

	const mainDataType Entity::_operatorTypeContactCount[operatorsMaxCount] = {
		/* Operator-index		  Contacts count */
		/* Zero */						0,
		/* Division */					2,
		/* Equal */						1,
		/* If */						2,
		/* Minus */						2,
		/* Multiplication */			2,
		/* One */						0,
		/* Plus */						2,
		/* RandomNumber */				1,
		/* Time */						0,
		/* CreateChannel */				3,
		/* CreateOperator */			1,
		/* DeleteChannel */				2,
		/* GetTypeOfOperator */			1,
		/* IsChannelExists */			3,
		/* RemoveOperator */			1,
		/* GetInputOperatorId */		1,
		/* GetOperatorContactsCount */	1,
		/* ExternalInput */				0,
		/* ExternalOutput */			0,
		/* Nothing */					0,
	};

	Entity::Entity() : _operators(), _nextOperatorId(1), _correctAnswersCount(0), _effectiveness(0),
		_chmanager(ChallengeManager::GetChallangeManager())
	{
		InitializeInputsAndOutputs();
	}

	Entity::Entity(Entity &ent) : Entity::Entity()
	{
		//std::copy(&ent._operators[0][0], &ent._operators[0][0]+operatorsMaxCount*operatorsTableWidth,&this->_operators[0][0]);
		for (mainDataType curRow = FirstInternalOper; curRow < ent._nextOperatorId; curRow++) {
			for (mainDataType curColumn = 0; curColumn <= outputValueColumn; curColumn++){
				this->_operators[curRow][curColumn] = ent._operators[curRow][curColumn];
			}
		}

		this->_nextOperatorId = ent._nextOperatorId;
	}

	Entity::~Entity() { }

	void Entity::Reset()
	{
		for (mainDataType i = 0; i < _nextOperatorId; i++)  { _operators[i][outputValueColumn] = 0; }
		_correctAnswersCount = 0;
		_effectiveness = 0;
		_nextOperatorId = FirstInternalOper;
	}

	void Entity::InitializeInputsAndOutputs()
	{
		for (mainDataType i = 0; i < ExternalOutputsCount; i++)  {mCreateOperatorUnsafe(ExternalOutput);}
		for (mainDataType i = 0; i < ExternalInputsCount; i++)  {mCreateOperatorUnsafe(ExternalInput);}
	}

	bool Entity::IsOperIdCorrect(mainDataType operatorId)
	{
		return (operatorId >= 0) && (operatorId < _nextOperatorId);
	}

	bool Entity::IsOperTypeCorrect(mainDataType operatorType)
	{
		return (operatorType > Zero) && (operatorType < ExternalInput);
	}

	bool Entity::IsContactCorrect(mainDataType contactId)
	{
		return (contactId > 0) && (contactId < operatorsTableWidth);
	}

	//Maybe inline will faster?? Check also memory usage
	mainDataType Entity::mGetChannelvalue(mainDataType operatorId, mainDataType contactId)
	{
		if (!IsOperIdCorrect(operatorId)) return 0;
		if (!IsContactCorrect(contactId)) return 0;

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
		if (!IsOperIdCorrect(fromOperator))		    return;
		if (!IsOperIdCorrect(toOperator))		    return;
		if (!IsContactCorrect(toOperatorContactId))	return;

		mCreateChannelUnsafe(fromOperator, toOperator, toOperatorContactId);
	}

	void Entity::mCreateChannelUnsafe(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId)
	{
		_operators[toOperator][toOperatorContactId] = fromOperator;
	}

	mainDataType Entity::mIfChannelExists(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId)
	{
		if (IsOperIdCorrect(fromOperator) && IsOperIdCorrect(toOperator) && IsContactCorrect(toOperatorContactId)) {
			if (_operators[toOperator][toOperatorContactId] == fromOperator) return 1;
		}
			
		return 0;
	}

	void Entity::mDeleteChannel(mainDataType toOperator, mainDataType toOperatorContactId)
	{
		if (!IsOperIdCorrect(toOperator))		    return;
		if (!IsContactCorrect(toOperatorContactId))	return;

		_operators[toOperator][toOperatorContactId] = 0;
	}

	void Entity::mRemoveOperator(mainDataType operatorToRemove)
	{
		if (!IsOperIdCorrect(operatorToRemove))		return;

		_operators[operatorToRemove][operatorTypeColumn] = OperatorsTypes::Nothing;
	}

	//To do: Add thread safe logic!!!
	void Entity::mCreateOperator(mainDataType operatorType)//To do: Add thread safe logic!!!
	{
		if (!IsOperTypeCorrect(operatorType))	return;

		mCreateOperatorUnsafe(operatorType);
	}

	//To do: Add thread safe logic!!!
	void Entity::mCreateOperatorUnsafe(mainDataType operatorType)
	{
		_operators[_nextOperatorId][0] = operatorType;
		_nextOperatorId++;
	}

	mainDataType Entity::mGetOperatorType(mainDataType operatorId)
	{
		if (!IsOperIdCorrect(operatorId))	return 0;

		return _operators[operatorId][operatorTypeColumn];
	}

	mainDataType Entity::mGetNewRandomVal(mainDataType upperLimit)
	{
		if (upperLimit == 0) return 0;

		return RandomValuesProvider::GetNextValue(upperLimit);
	}

	void Entity::mProcess(mainDataType operatorId)
	{

		#if defined(PERFOMANCE_TESTING)
		 EntetiesProcessed++;
		#endif

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
			if (sContValue != 0) {
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
			outValue = fContValue > sContValue;
			break;
		case (IsChannelExists):
			outValue = mIfChannelExists(fContValue, sContValue, tContValue);
			break;
		case (Minus):
			if (fContValue > sContValue){
				outValue = fContValue - sContValue;
			}
			else
				outValue = 0;
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
			outValue = _chmanager->GetEntityExternalInput(operatorId - FirstExtInputPos);
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
		{
			return 0;//test performance
		}

		return _operators[refOperId][outputValueColumn];
	}

	mainDataType Entity::GetNextOperatorId()
	{
		return _nextOperatorId;
	}

	void Entity::mProcessAll()
	{
		//Processing external inputs and all internal operators
		for (mainDataType i = FirstExtInputPos; i < _nextOperatorId; i++)
		{
			mProcess(i);
		}

		//Processing external outputs
		static const unsigned short rex = ExternalOutputsCount - 1;
		for (mainDataType i = 0; i < rex;)
		{
			mainDataType nextI = i + 1;
			if (_chmanager->GetCorrectAnswer(i) != GetInputValue(nextI, outputValueColumn))
			{
				//_chmanager->ReportFailure();
				return;
			}

			i = nextI;
		}

		//_chmanager->ReportSuccess();
		_correctAnswersCount++;
	}

	void Entity::SetExternalInputValue(mainDataType inputOperId)
	{
		_operators[_nextOperatorId][operatorTypeColumn] = inputOperId;
	}

	mainDataType Entity::GetOperatorsCount()
	{
		return _nextOperatorId - 1;
	}

	void Entity::CalculateEffectiveness(mainDataType totalAnswersCount)
	{
		_effectiveness = _correctAnswersCount / (double) totalAnswersCount;
	}

	double Entity::GetEffectiveness()
	{
		return _effectiveness;
	}

	void Entity::SetCorrectAnswers(mainDataType count)
	{
		_correctAnswersCount = count;
	}

	bool Entity::IsEqual(Entity* ent)
	{
		if (this->GetOperatorsCount() != ent->GetOperatorsCount()) return false;

		for (size_t i = FirstInternalOper; i < GetOperatorsCount(); i++) {
			if (this->GetContactValue(i, 0) != ent->GetContactValue(i, 0))  return false;
		}

		return true;
	}
}