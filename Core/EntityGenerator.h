#pragma once
#include "Entity.h"

namespace Brans 
{
	class EntityGenerator
	{
	public:
		EntityGenerator(void);
		~EntityGenerator(void);
		Entity& GenerateEntity(mainDataType operatorsCount, mainDataType maxExternalInputOperators, 
										   mainDataType ExternalOutputsOperators);
	private:
		EntityGenerator::OperatorsTypes GenerateRandomOperType();
		mainDataType EntityGenerator::GetNextRandomOperId(mainDataType entityOpersCount);
	};
}

