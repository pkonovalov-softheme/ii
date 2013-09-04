#pragma once

namespace AI
{
	#define mainDataType unsigned int //main data type for all tables(arrays)
	#define operType   _operators[operatorId][0] //type of the operator
	#define fContValue _operators[operatorId][1] //value of first contact
	#define sContValue _operators[operatorId][2] //value of second contact
	#define tContValue _operators[operatorId][3] //value of third contact
	#define outValue   _operators[operatorId][4] //value of the operators output contact

	namespace Core
	{
		/// <summary>
		/// 
		/// </summary>
		class Entity
		{
		private:

			const unsigned short operatorsTableWidth = 5; // 0 column - operator type, 1 - 3 input values, 4 - output value
			const unsigned short operatorTypeColumn = 1;
			const unsigned short outputValueColumn = 4;
			const unsigned short operatorsMaxCount = 300; // maximum acceptable count of operators for one entity
			const unsigned short operatorsTypesCount = 18;

			mainDataType _operators[operatorsMaxCount][operatorsTableWidth];

			mainDataType _operatorTypeContactCount[operatorsMaxCount];

			//Add thread safe logic!
			mainDataType _lastOperatorId; //returns IDs of the last used operator

			void mProcessInternal(mainDataType operatorId); //Process operator with the given Id calculating and setting up its output value

			void InitializeOpTypesCC();

		public:
			Entity();

			mainDataType mGetChannelvalue(mainDataType operatorId, mainDataType contactId); //returns input value of target contact

			void mSetOperatorOutValue(mainDataType operatorId, mainDataType value); // set value for operator output contact

			void mCreateChannel(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //create new channel between two operators

			mainDataType mIfChannelExists(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //returns true if channel exists there
			
			void mDeleteChannel(mainDataType toOperator, mainDataType toOperatorContactId); //delete existing channel between two operators

			mainDataType mGetOperatorType(mainDataType operatorId); //returns type of the target operator

			void mCreateOperator(mainDataType operatorType); //creates new operator

			enum OperatorsTypes
			{
				Division, Equal, If, Minus, Multiplication, One, Plus, RandomNumber, Time, CreateChannel, CreateOperator, DeleteChannel, GetTypeOfOperator,
				IsChannelExists, RemoveOperator, GetOperatorId, GetOperatorContactsCount, Nothing 
			};
		};
	}
}
