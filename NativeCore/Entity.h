#pragma once

namespace AI
{
	#define mainDataType unsigned int //main data type for all tables(arrays)
	#define operatorsTableWidth 5// 0 column - operator type, 1 - 3 imput values, 4 - output value
	#define operatorTypeColumn 1
	#define outputValueColumn 4
	#define operatorsMaxCount 300 // maximum acceptable count of operators for one entity

	namespace Core
	{
		/// <summary>
		/// 
		/// </summary>
		class Entity
		{
		private:
			mainDataType _operators[operatorsMaxCount][operatorsTableWidth];

			mainDataType _lastOperatorId; //returns IDs of the last used operator

		public:
			Entity();

			mainDataType GetChannelvalue(mainDataType operatorId, mainDataType contactId); //returns input value of target contact

			void SetOperatorOutValue(mainDataType operatorId, mainDataType value); // set value for operator output contact

			void CreateChannel(mainDataType fromOperator, mainDataType toOperator, mainDataType toOperatorContactId); //create new channel between two operators

			void DeleteChannel(mainDataType toOperator, mainDataType toOperatorContactId); //delete existing channel between two operators

			mainDataType GetOperatorType(mainDataType operatorId); //returns type of the target operator
		};
	}
}
