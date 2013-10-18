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
	
		for (int curOper = 0; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating oper
			ent->AddOperator(RandomOperatorsProvider::GetNextOperator());

			//Creating connections
			for (int curContact = 0; curContact <= ent->contactsCount; curContact++)
			{
				ent->mCreateChannel(_conProvider->GetNextValue(), curOper, curContact);
			}
		}

		return *ent;
	}
}