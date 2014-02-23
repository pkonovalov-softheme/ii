#pragma once

enum OperatorsTypesTest
{
	/*Zero is restricted system value. After the first zero operator _operators array processing will be stopped.
	Value of the zero operator is assuming as zero-only.
	Basic operators:*/
	Zero, Division, Equal, If, Minus, Multiplication, One, Plus, RandomNumber, Time,
	//Meta operators:
	CreateChannel, CreateOperator, DeleteChannel, GetTypeOfOperator, IsChannelExists,
	RemoveOperator, GetInputOperatorId, GetOperatorContactsCount, ExternalInput, ExternalOutput, Nothing
};

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
		RemoveOperator, GetInputOperatorId, GetOperatorContactsCount, ExternalInput, ExternalOutput, Nothing
	};

	const unsigned short OperatorsCount = Nothing + 1;  //with zero and nothing
	static const unsigned short ExternalInputsCount = 2;//External inputs count of the entity
	static const unsigned short ExternalOutputsCount = 1;//External Outputs count of the entity
	const unsigned short EntityProcessCount = 1;
	const mainDataType EntityOperatorsCount = 30;
	const mainDataType operatorsMaxCount = EntityOperatorsCount * 2; // maximum acceptable count of operators for one entity
	const mainDataType EntitiesStartPopulation = 1000;
}