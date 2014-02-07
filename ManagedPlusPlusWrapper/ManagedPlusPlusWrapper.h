// ManagedPlusPlusWrapper.h

#pragma once
#include "..\Core\BransGlobals.h"

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
		literal UInt32 EntitiesStartPopulation = EntitiesStartPopulation;
		
		static const unsigned short operatorTypeColumn = operatorTypeColumn;
		static const unsigned short contactsCount = contactsCount;
		static const unsigned short outputValueColumn = outputValueColumn;
		static const unsigned short operatorsTypesCount = operatorsTypesCount;
		static const unsigned short operatorsTableWidth = operatorsTableWidth; // 0 column - operator type, 1 - 3 input values, 4 - output value
		static const mainDataType FirstInternalOper = FirstInternalOper;

		static const unsigned short FirstExtInputPos = FirstExtInputPos;
    };
}
