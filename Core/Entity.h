#pragma once

namespace Brans 
{
	#define mainDataType unsigned int //main data type for all tables(arrays)

	enum OperatorsTypes
	{
		/*Zero is restricted system value. After the first zero operator _operators array processing will be stopped. 
		Value of the zero operator is assuming as zero-only.
		Basic operators:*/
		Zero, Division, Equal, If, Minus, Multiplication, One, Plus, RandomNumber, Time, 
		//Meta operators:
		CreateChannel, CreateOperator, DeleteChannel, GetTypeOfOperator, IsChannelExists, 
		RemoveOperator, GetInputOperatorId, GetOperatorContactsCount, Nothing 
	};

	const unsigned short const OperatorsCount = 19;

	class Entity
	{
	public:

		static const unsigned short operatorTypeColumn = 0;
		static const unsigned short outputValueColumn = 4;
		static const unsigned short operatorsMaxCount = 2000; // maximum acceptable count of operators for one entity
		static const unsigned short operatorsTypesCount = 18;
		static const unsigned short operatorsTableWidth = 5; // 0 column - operator type, 1 - 3 input values, 4 - output value

		Entity(void);

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

	private:

		mainDataType _operators[operatorsMaxCount][operatorsTableWidth];

		mainDataType _operatorTypeContactCount[operatorsMaxCount];

		//Add thread safe logic!
		unsigned int _nextOperatorId; //returns IDs of the last used operator

		void InitializeOpTypesCC();
	};
}
