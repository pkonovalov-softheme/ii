#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"

namespace Brans 
{
	static const mainDataType reducedOpC = EntityOperatorsCount - 1;
	EntityGenerator::EntityGenerator() : _entity(), _conProvider(reducedOpC)
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

			OperatorsTypes lastOperType = (OperatorsTypes)_entity.mGetOperatorType(curOper);
			mainDataType lastOperTypeCntsCount = Entity::mGetOperTypeContactsCount(lastOperType);

			//Creating connections
			for (int curContact = 1; curContact <= lastOperTypeCntsCount; curContact++)
			{
				mainDataType md = _conProvider.GetNextValue();
				_entity.mCreateChannelUnsafe(md, curOper, curContact);
			}
		}

		return _entity;
	}
}