#pragma once

namespace Brans
{
#define mainDataType unsigned int //main data type for all tables(arrays)

	enum OperatorsTypes
	{
		/*Zero is restricted system value. After the first zero operator _operators array processing will be stopped.
		Value of the zero operator is assuming as zero-only.
		Basic operators:*/
		Zero, Division, If, Minus, Multiplication, One, Plus, RandomNumber,
		//Meta operators:
		CreateChannel, CreateOperator, DeleteChannel, GetTypeOfOperator, IsChannelExists,
		RemoveOperator, GetInputOperatorId, GetOperatorContactsCount, ExternalInput, ExternalOutput, Nothing
	};

	const unsigned short OperatorsTypesCount = Nothing + 1;  //with zero and nothing

	static const unsigned short ExternalInputsCount = 4; //External inputs count of the entity (for tests -4)
	static const unsigned short ExternalOutputsCount = 2; //External Outputs count of the entity (for tests -2)
	static const unsigned short FirstExternalValueInputs = 1; //Ofsset inside external inputs of first signable inputs, (current firs contact is challange type)

	static const unsigned short EntityInternalOperatorsCount = 2;
	static const unsigned short EntityOperatorsCount = ExternalInputsCount + ExternalOutputsCount + EntityInternalOperatorsCount + 1;


	static const unsigned short EntityProcessCount = 8;
	static const mainDataType operatorsMaxCount = EntityOperatorsCount * 2; // maximum acceptable count of operators for one entity
	static const mainDataType EntitiesStartPopulation = 1000;
}