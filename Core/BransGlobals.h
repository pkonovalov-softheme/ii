#pragma once

namespace Brans
{
#define mainDataType unsigned int //main data type for all tables(arrays)

	enum OperatorsTypes
	{
		/*Zero is restricted system value. After the first zero operator _operators array processing will be stopped.
		Value of the zero operator is assuming as zero-only.
		Basic operators:*/
		Zero, If, Multiplication, One, Plus, ExternalInput, ExternalOutput, Nothing
	};

	const unsigned short OperatorsTypesCount = Nothing + 1;  //with zero and nothing

	static const unsigned short ExternalInputsCount = 3; //External inputs count of the entity (for tests -4)
	static const unsigned short ExternalOutputsCount = 1; //External Outputs count of the entity (for tests -2)

	static const unsigned short EntityInternalOperatorsCount = 6;
	static const unsigned short EntityOperatorsCount = ExternalInputsCount + ExternalOutputsCount + EntityInternalOperatorsCount + 1;
	static const unsigned short EntityOperatorsWithExitCount = ExternalOutputsCount + EntityInternalOperatorsCount;

	static const unsigned short EntityProcessCount = 2;
	static const mainDataType operatorsMaxCount = EntityOperatorsCount * 2; // maximum acceptable count of operators for one entity
	static const mainDataType EntitiesStartPopulation = 1000;
}