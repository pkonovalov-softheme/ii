#include "stdafx.h"
#include "EntityGenerator.h"
#include "Entity.h"

namespace Brans 
{
	EntityGenerator::EntityGenerator(mainDataType operatorsCount)
	{
		_operatorsCount = operatorsCount;
		_conProvider = new RandomValuesProvider(operatorsCount);
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	Entity& EntityGenerator::GenerateEntity()
	{
		Entity* ent= new Entity();
	
		for (int curOper = 0; curOper < _operatorsCount; curOper++)
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