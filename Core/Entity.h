#pragma once
#include "BransGlobals.h"
#include "RandomProvider.h"

namespace Brans 
{
	class Entity
	{
	public:
		static const unsigned short operatorTypeColumn = 0;
		static const unsigned short contactsCount = 3;
		static const unsigned short outputValueColumn = 4;
		static const unsigned int operatorsMaxCount = 200000; // maximum acceptable count of operators for one entity
		static const unsigned short operatorsTypesCount = 18;
		static const unsigned short operatorsTableWidth = 5; // 0 column - operator type, 1 - 3 input values, 4 - output value

		Entity(mainDataType ExternalInputsCount, mainDataType ExternalOutputsCount);

		~Entity(void);

		mainDataType mGetChannelvalue(mainDataType operatorId, mainDataType contactId); //returns input value of target contact

		void mCreateChannel(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //create new channel between two operators

		mainDataType mIfChannelExists(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //returns true if channel exists there

		void mDeleteChannel(mainDataType toOperator, mainDataType toOperatorContactId); //delete existing channel between two operators

		mainDataType mGetOperatorType(mainDataType operatorId); //returns type of the target operator

		void mCreateOperator(mainDataType operatorType); //creates new operator

		void mRemoveOperator(mainDataType operatorToRemove); //Virtually removes the operator setting up it type to Nothing

		void mProcess(mainDataType operatorId); //Process operator with the given Id calculating and setting up its output value

		void mProcessAll(); //Process all operators

		void mProcessLast(); //Processes last operator

		mainDataType GetContactValue(mainDataType operatorId, mainDataType contactId); //Returns the value of the specific operator

		void SetContactValue(mainDataType operatorId, mainDataType contactId, mainDataType value); //Set up the value of the specific operator

		mainDataType GetNextOperatorId();// returns last used operator ID = operators count if no one operator was deleted
		
		//Set up the input values for the specific operator
		void SetInputValues(mainDataType operatorId, mainDataType fcontactValue, mainDataType scontactValue, mainDataType tcontactValue); 
		void SetInputValues(mainDataType operatorId, mainDataType fcontactValue, mainDataType scontactValue); 
		void SetInputValues(mainDataType operatorId, mainDataType fcontactValue); 

		//Get the input values for the specific operator. Unsafe without any checks!
		mainDataType GetInputValue(mainDataType operatorId, mainDataType contactId);
		//Returns value from 1 to upperLimit(inclusive)
		mainDataType Entity::mGetNewRandomVal(mainDataType upperLimit);

		void SetExternalInputValue(mainDataType inputOperId);

		//Returns operator from witch is starting operators(after external enters and exists)
		mainDataType GetFirstOperator();

		//Returns operator from witch is starting operators(after external enters and exists)
		void AddOperator(mainDataType operatorType);
		mainDataType Entity::GetOperatorsCount();


	private:

		mainDataType _operators[operatorsMaxCount][operatorsTableWidth];

		mainDataType _operatorTypeContactCount[operatorsMaxCount];

		unsigned int _nextOperatorId; //returns IDs of the last used operator

		void InitializeOpTypesCC();
		void InitializeInputsAndOutputs();
		mainDataType _externalInputsCount;
		mainDataType _externalOutputsCount;
		mainDataType _firstOper; //from there external inputs and outputs ends
	};


}
