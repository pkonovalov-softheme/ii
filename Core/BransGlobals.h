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
		RemoveOperator, GetInputOperatorId, GetOperatorContactsCount, ExternalInput, ExternalOutput, Nothing
	};

	const unsigned short OperatorsCount = 19;
	static const unsigned short ExternalInputsCount = 10;
	static const unsigned short ExternalOutputsCount = 10;
	const unsigned short EntityProcessCount = 10;
	const mainDataType EntityOperatorsCount = 1000;
	const mainDataType TotalChallengesCount = 1000;
	const mainDataType EntitiesStartPopulation = 100000;
}