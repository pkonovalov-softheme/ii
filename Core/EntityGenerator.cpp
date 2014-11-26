#pragma once
#include "stdafx.h"
#include "EntityGenerator.h"
#include "assert.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort

namespace Brans 
{
	static const unsigned short ExternalOutputsCountAdd = ExternalOutputsCount + 1; // We didn't connect  from ExternalOutputs to opers

	EntityGenerator::EntityGenerator() : _entity(), _operatorsConProvider(EntityOperatorsCount, ExternalOutputsCountAdd),
		_externalOutputsConProvider(EntityOperatorsCount, ExternalOutputsCountAdd + ExternalInputsCount)
	{
		static const int firtsOperType = OperatorsTypes::Zero + 1;
		for (size_t curOper = Entity::FirstInternalOper + 1; curOper < EntityOperatorsCount; curOper++)
		{
			_entity.SetContactValue(curOper, Entity::operatorTypeColumn, firtsOperType);
		}

		for (size_t curOper = Entity::FirstExtOutputPos; curOper < EntityOperatorsCount; curOper++)
		{
			if (_entity.HasOperExit(curOper))
			{
				operators_with_exit.push_back(curOper);
			}
		}

		std::sort(operators_with_exit.begin(), operators_with_exit.end());
	}

	EntityGenerator::~EntityGenerator(void)
	{
	}

	bool EntityGenerator::NextEntityCore()
	{
		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++) {
			_entity.IncrimentContactValueUnsafe(curOper, Entity::operatorTypeColumn);
			
			if (_entity.GetContactValue(curOper, Entity::operatorTypeColumn) < OperatorsTypes::ExternalInput) {
				for (int nextOper = Entity::FirstInternalOper; nextOper < curOper; nextOper++) {
					int curVal = _entity.GetContactValue(curOper, Entity::operatorTypeColumn);
					_entity.SetContactValue(nextOper, Entity::operatorTypeColumn, curVal);
				}
				return true;
			}
		}

		// no more legal values
		return false;
	}

	bool EntityGenerator::GenerateStartLayout()
	{
		return std::next_permutation(operators_with_exit.begin(), operators_with_exit.end());
	}

	Entity* EntityGenerator::GetEntity()
	{
		return &_entity;
	}

	Entity& EntityGenerator::GenerateEntity()
	{
		static ULONGLONG stat[OperatorsTypesCount] = {};

		_entity.Reset();

		for (int curOper = Entity::FirstInternalOper; curOper < EntityOperatorsCount; curOper++)
		{
			//Creating opers
			int operType = RandomOperatorsProvider::GetNextOperator();
			stat[operType]++;
			_entity.mCreateOperatorUnsafe(operType);
		}

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
		OperatorsTypes operType = static_cast<OperatorsTypes>(_entity.mGetOperatorTypeUnsafe(toOper));
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

				if (fromOper == Entity::FirstExtOutputPos)
				{
					fromOper += ExternalOutputsCount;
				}

				if (fromOper == EntityOperatorsCount)
				{
					fromOper = Entity::FirstExtInputPos;
				}
			}
		}
	}
}