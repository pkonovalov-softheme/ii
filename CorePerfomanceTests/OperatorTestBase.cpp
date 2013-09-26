#include "stdafx.h"
#include "OperatorTestBase.h"
#include "..\Core\Entity.h"

#include <iostream>
#include <chrono>
#include <ctime>

using namespace Brans;

Entity* entity;
clock_t c_start; 
unsigned long _elapsed;

OperatorTestBase::OperatorTestBase(mainDataType operatorType, mainDataType firstValue, mainDataType secondValue, mainDataType thirdValue)
{
	entity = new Entity(0, 0);
	CreateOper(Nothing);
	SetValue(1, firstValue);
	CreateOper(Nothing);
	SetValue(2, secondValue);
	CreateOper(Nothing);
	SetValue(3, thirdValue);

	for (int i = 0; i < OperatorsCout; i++)
	{
		CreateOper(operatorType);
		entity->mCreateChannel(1, GetLastOper(), 1);
		entity->mCreateChannel(2, GetLastOper(), 2);
		entity->mCreateChannel(3, GetLastOper(), 3);
	}
}

void OperatorTestBase::CreateOper(mainDataType operatorType)
{
	entity->mCreateOperator(operatorType);
}

void OperatorTestBase::SetValue(mainDataType operatorId, mainDataType valueToSet)
{
	entity->SetContactValue(operatorId, entity->outputValueColumn, valueToSet);
}

mainDataType OperatorTestBase::GetLastOper()
{
	return (entity->GetNextOperatorId() - 1);
}

void OperatorTestBase::Process(unsigned long long numberOfCycles)
{
	for (int i = 0; i < numberOfCycles; i++)
	{
		entity->mProcessAll();
	}
}

mainDataType OperatorTestBase::GetResult()
{
	return (entity->mGetChannelvalue(GetLastOper(), entity->outputValueColumn));
}


void OperatorTestBase::StartWatch()
{
	c_start = std::clock();
}

void OperatorTestBase::StopWatch()
{
	clock_t c_end = std::clock();
	_elapsed = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
}

unsigned long OperatorTestBase::GetElapsedMiliseconds()
{
	return _elapsed;
}