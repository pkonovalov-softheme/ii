#include "stdafx.h"
#include "EntityGenerator.h"
#include "Entity.h"

namespace Brans 
{
	EntityGenerator::EntityGenerator(void)
	{
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	OperatorsTypes EntityGenerator::GenerateRandomOperType()
	{
		OperatorsTypes result = (OperatorsTypes) RandomProvider::GetNextValue(OperatorsCount);
		return result;
	}

	mainDataType EntityGenerator::GetNextRandomOperId(mainDataType entityOpersCount)
	{
		return RandomProvider::GetNextValue(entityOpersCount);
	}

	Entity& EntityGenerator::GenerateEntity(mainDataType operatorsCount)
	{
		Entity* ent= new Entity();
	
		for (int curOper = 0; curOper < operatorsCount; curOper++)
		{
			//Creating oper
			ent->AddOperator(GenerateRandomOperType());

			//Creating connections
			for (int curContact = 0; curContact <= ent->contactsCount; curContact++)
			{
				ent->mCreateChannel(GetNextRandomOperId(operatorsCount), curOper, curContact);
			}
		}

		return *ent;
	}
}