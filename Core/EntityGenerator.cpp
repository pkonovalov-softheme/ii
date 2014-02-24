#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"

namespace Brans 
{
	static const mainDataType reducedOpC = EntityOperatorsCount - 1;
	static const unsigned short ExternalOutputsCountAdd = ExternalOutputsCount + 1; // We didn't connect opers with ExternalOutputs

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

			OperatorsTypes lastOperType = (OperatorsTypes)_entity.mGetOperatorTypeUnsafe(curOper);
			mainDataType lastOperTypeCntsCount = Entity::mGetOperTypeContactsCountUnsafe(lastOperType);

			//Creating connections
			for (int curContact = Entity::FirstContact; curContact <= lastOperTypeCntsCount; curContact++)
			{
				mainDataType md = _conProvider.GetNextValue();
				_entity.mCreateChannelUnsafe(md, curOper, curContact);
			}
		}

		return _entity;
	}
}