// ManagedPlusPlusWrapper.h

#pragma once
#include "..\Core\BransGlobals.h"
#include "..\Core\Entity.h"

using namespace System;
using namespace Brans;

namespace ManagedPlusPlusWrapper {

	public ref class BransGlobals abstract sealed
	{
	public:
		literal UInt32 EntitiesStartPopulation = EntitiesStartPopulation;
		literal UInt32 operatorsMaxCount = operatorsMaxCount;
		literal UInt32 EntityOperatorsCount = EntityOperatorsCount;
		literal UInt32 EntityProcessCount = EntityProcessCount;
		literal UInt32 ExternalOutputsCount = ExternalOutputsCount;
		literal UInt32 ExternalInputsCount = ExternalInputsCount;
		literal UInt32 OperatorsCount = OperatorsCount;
	};

	public ref class EntityConsts abstract sealed
	{
		public:
		static const unsigned short operatorTypeColumn = Entity::operatorTypeColumn;
		static const unsigned short contactsCount = Entity::contactsCount;
		static const unsigned short outputValueColumn = Entity::outputValueColumn;
		static const unsigned short operatorsTypesCount = Entity::operatorsTypesCount;
		static const unsigned short operatorsTableWidth = Entity::operatorsTableWidth; // 0 column - operator type, 1 - 3 input values, 4 - output value
		static const mainDataType FirstInternalOper = Entity::FirstInternalOper;
		static const unsigned short FirstExtInputPos = FirstExtInputPos;
		static const unsigned short FirstContact = Entity::FirstContact;
		static const unsigned short SecondContact = Entity::SecondContact;;
		static const unsigned short ThirdContact = Entity::ThirdContact;;
    };
}
