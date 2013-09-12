#include "stdafx.h"
#include "OperatorTestBase.h"
#include "..\Core\Entity.h"
using namespace Brans;

Entity* entity;

OperatorTestBase::OperatorTestBase(mainDataType operatorType)
{
	const unsigned int OperatorsCout = 1000;
	entity = new Entity();
	CreateOper(Nothing);
	SetValue(1, 1);
	CreateOper(Nothing);
	SetValue(2, 1);
	for (int i = 0; i < OperatorsCout; i++)
	{
		CreateOper(operatorType);
		entity->mCreateChannel(1, GetLastOper(), 1);
		entity->mCreateChannel(GetLastOper() - 1, GetLastOper(), 2);
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