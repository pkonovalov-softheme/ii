#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"
#include "assert.h"

namespace Brans 
{
	static const mainDataType reducedOpC = EntityOperatorsCount - 1;
	static const unsigned short ExternalOutputsCountAdd = ExternalOutputsCount + 1; // We didn't connect  from ExternalOutputs to opers

	EntityGenerator::EntityGenerator() : _entity(), _operatorsConProvider(reducedOpC, ExternalOutputsCountAdd), 
		_externalOutputsConProvider(reducedOpC, ExternalOutputsCountAdd + ExternalInputsCount)
	{
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	bool EntityGenerator::ValidateEntity()
	{

	}

	Entity& EntityGenerator::GenerateEntity()
	{
		_entity.Reset();

		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating opers
			_entity.mCreateOperatorUnsafe(RandomOperatorsProvider::GetNextOperator());
		}

		ValidateEntity();

		for (int curOper = Entity::FirstExtOutputPos; curOper <= ExternalOutputsCount; curOper++)
		{
			GenerateConnections(curOper);
		}

		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			GenerateConnections(curOper);
		}

		return _entity;
	}

	void EntityGenerator::GenerateConnections(mainDataType toOper)
	{
		OperatorsTypes operType = (OperatorsTypes)_entity.mGetOperatorTypeUnsafe(toOper);
		mainDataType operTypeCntsCount = Entity::mGetOperTypeContactsCountUnsafe(operType);

		for (int curContact = Entity::FirstContact; curContact <= operTypeCntsCount; curContact++)
		{
			mainDataType fromOper = _operatorsConProvider.GetNextValue();
			CreateChannelIfAppropriate(toOper, curContact, fromOper);
		}
	}

	void EntityGenerator::CreateChannelIfAppropriate(mainDataType toOper, mainDataType curOperContactId, mainDataType fromOper)
	{
		for (size_t i = 0; i < EntityOperatorsCount - ExternalOutputsCount; i++)
		{
			if ((toOper != fromOper) && _entity.HasOperExit(fromOper)) //ToDo: Add compatibility, at least with time check?
			{
				_entity.mCreateChannelUnsafe(fromOper, toOper, curOperContactId);
				break;
			}
			else
			{
				fromOper++;

				if (fromOper == Entity::FirstExtInputPos)
				{
					fromOper += ExternalInputsCount;
				}

				if (fromOper == EntityOperatorsCount)
				{
					fromOper = Entity::FirstExtOutputPos;
				}
			}
		}
	}
}