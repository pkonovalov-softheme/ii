#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"

namespace Brans 
{
	static const mainDataType reducedOpC = EntityOperatorsCount - 1;
	static const unsigned short ExternalOutputsCountAdd = ExternalOutputsCount + 1; // We didn't connect  from ExternalOutputs to opers

	EntityGenerator::EntityGenerator() : _entity(), _conProvider(reducedOpC, ExternalOutputsCountAdd)
	{
		static const mainDataType reducedOpC = EntityOperatorsCount - 1;
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	Entity& EntityGenerator::GenerateEntity()
	{
		_entity.Reset();

		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating oper
			_entity.mCreateOperatorUnsafe(RandomOperatorsProvider::GetNextOperator());
		}

		for (int curOper = Entity::FirstExtOutputPos; curOper <= ExternalOutputsCount; curOper++)
		{
			mainDataType fromOper = _conProvider.GetNextValue();
			_entity.mCreateChannelUnsafe(fromOper, curOper, Entity::FirstContact);
		}

		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating oper
			GenerateConnections(curOper);
		}

		return _entity;
	}

	void EntityGenerator::GenerateConnections(mainDataType curOper)
	{
		OperatorsTypes lastOperType = (OperatorsTypes)_entity.mGetOperatorTypeUnsafe(curOper);
		mainDataType lastOperTypeCntsCount = Entity::mGetOperTypeContactsCountUnsafe(lastOperType);

		for (int curContact = Entity::FirstContact; curContact <= lastOperTypeCntsCount; curContact++)
		{
			mainDataType fromOper = _conProvider.GetNextValue();
			CreateChannelIfAppropriate(curOper, curContact, fromOper);
		}
	}

	void EntityGenerator::CreateChannelIfAppropriate(mainDataType curOper, mainDataType curOperContactId, mainDataType fromOper)
	{
		for (size_t i = 0; i < EntityOperatorsCount; i++)
		{
			if ((curOper != fromOper) && _entity.HasOperExit(fromOper)) //ToDo: Add compatibility, at least with time check?
			{
				_entity.mCreateChannelUnsafe(fromOper, curOper, curOperContactId);
			}
			else
			{
				if (curOper == EntityOperatorsCount)
					curOper == Entity::FirstInternalOper;
				else
					curOper++;
			}
		}
	}
}