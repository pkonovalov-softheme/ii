#pragma once
#include "BransGlobals.h"
#include "RandomProvider.h"
#include <time.h>

namespace Brans 
{
	class ChallengeManager;

	#if defined(PERFOMANCE_TESTING)
		extern mainDataType EntetiesProcessed;
	#endif

	class Entity
	{
	public:
		static const unsigned short operatorTypeColumn = 0;
		static const unsigned short contactsCount = 3;
		static const unsigned short outputValueColumn = 4;
		static const unsigned short operatorsTableWidth = 5; // 0 column - operator type, 1 - 3 input values, 4 - output value
		static const mainDataType FirstInternalOper = ExternalInputsCount + ExternalOutputsCount + 1;
		static const unsigned short FirstExtInputPos = ExternalOutputsCount + 1;
		static const unsigned short FirstExtOutputPos = 1;
		static const mainDataType _operatorTypeContactCount[OperatorsTypesCount];
		static const unsigned short FirstContact = 1;
		static const unsigned short SecondContact = 2;
		static const unsigned short ThirdContact = 3;

		static const bool _operatorTypeExit[OperatorsTypesCount];

		Entity();

		~Entity(void);

		Entity::Entity(Entity &ent);

		mainDataType mGetChannelvalue(mainDataType operatorId, mainDataType contactId); //returns input value of target contact

		void mCreateChannel(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //create new channel between two operators

		void mCreateChannelUnsafe(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //create new channel between two operators

		mainDataType mIsChannelExists(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //returns true if channel exists there

		void mDeleteChannel(mainDataType toOperator, mainDataType toOperatorContactId); //delete existing channel between two operators

		mainDataType mGetOperatorType(mainDataType operatorId); //returns type of the target operator

		mainDataType mGetOperatorTypeUnsafe(mainDataType operatorId); //returns type of the target operator without check


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
		mainDataType mGetNewRandomVal(mainDataType upperLimit);

		void SetExternalInputValue(mainDataType inputOperId);

		mainDataType GetOperatorsCount();

		void CalculateEffectiveness(mainDataType totalAnswersCount);

		double GetEffectiveness();

		//Now used only for tests
		void SetCorrectAnswers(mainDataType count);

		void Entity::mCreateOperatorUnsafe(mainDataType operatorType);

		//Returns true if all operators type are the same
		bool IsEqual(Entity* ent); 

		void Reset();

		mainDataType* GetOperatorsPtr();

		//Returns true if the target operator have exit
		bool HasOperExit(mainDataType operId);

		mainDataType GetCorrectAnswersCount();

		static mainDataType Entity::mGetOperTypeContactsCount(mainDataType operatorType);

		static mainDataType Entity::mGetOperTypeContactsCountUnsafe(mainDataType operatorType);

	private:

		double _effectiveness;

		mainDataType _incorrectAnswersCount;

		mainDataType _correctAnswersCount;

		mainDataType _nextOperatorId; //returns IDs of the last used operator

		ChallengeManager* _chmanager;

		mainDataType _operators[operatorsMaxCount][operatorsTableWidth];

		bool IsOperIdCorrect(mainDataType operatorId);

		bool IsOperTypeCorrect(mainDataType operatorType);

		bool IsContactCorrect(mainDataType contactId, mainDataType operId);

		void InitializeInputsAndOutputs();
	};


}
