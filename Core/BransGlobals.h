#pragma once

namespace Brans
{
	#define mainDataType unsigned int //main data type for all tables(arrays)

	//enum OperatorsTypes
	//{
	//	/*Zero is restricted system value. After the first zero operator _operators array processing will be stopped.
	//	Value of the zero operator is assuming as zero-only.
	//	Basic operators:*/
	//	Zero = 0, Division = 12, Equal = 21, If = 32, Minus = 42, Multiplication = 52, One = 60, Plus = 72, RandomNumber = 81, Time = 90,
	//	//Meta operators:
	//	CreateChannel = 103, CreateOperator = 111, DeleteChannel = 122, GetTypeOfOperator = , IsChannelExists,
	//	RemoveOperator, GetInputOperatorId, GetOperatorContactsCount, ExternalInput, ExternalOutput, Nothing
	//};
	enum OperatorsTypes
	{
		/*Zero is restricted system value. After the first zero operator _operators array processing will be stopped.
		Value of the zero operator is assuming as zero-only.
		Basic operators:*/
		Zero, Division, Equal, If, Minus, Multiplication, One, Plus, RandomNumber, Time,
		//Meta operators:
		CreateChannel, CreateOperator, DeleteChannel, GetTypeOfOperator, IsChannelExists,
		RemoveOperator, GetInputOperatorId, GetOperatorContactsCount, ExternalInput, ExternalOutput, Nothing
	};

	const unsigned short OperatorsCount = Nothing + 1;  //with zero and nothing
	static const unsigned short ExternalInputsCount = 10;
	static const unsigned short ExternalOutputsCount = 10;
	const unsigned short EntityProcessCount = 10;
	const mainDataType EntityOperatorsCount = 1000;
	const mainDataType operatorsMaxCount = EntityOperatorsCount * 2; // maximum acceptable count of operators for one entity
	const mainDataType EntitiesStartPopulation = 10000;
}