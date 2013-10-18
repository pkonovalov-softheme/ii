#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"

namespace Brans 
{
	EntityGenerator::EntityGenerator()
	{
		_conProvider = new RandomValuesProvider(EntityOperatorsCount);
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	Entity& EntityGenerator::GenerateEntity()
	{
		Entity* ent= new Entity();
	
		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating oper
			ent->mCreateOperator(RandomOperatorsProvider::GetNextOperator());

			mainDataType lastOper = ent->mGetOperatorType(Entity::FirstInternalOper + curOper);
			//Creating connections
			for (int curContact = 0; curContact <= ent->; curContact++)
			{
				ent->mCreateChannel(_conProvider->GetNextValue(), curOper, curContact);
			}
		}

		return *ent;
	}
}