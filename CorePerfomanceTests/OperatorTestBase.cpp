#include "stdafx.h"
#include "OperatorTestBase.h"
#include "..\Core\Entity.h"
using namespace Brans;

Entity* entity;

OperatorTestBase::OperatorTestBase(mainDataType operatorType)
{
	const unsigned int OperatorsCout = 100;
	entity = new Entity();
	CreateOper(Nothing);
	CreateOper(Nothing);
	CreateOper(Nothing);
	for (int i = 0; i < OperatorsCout; i++)
	{
		CreateOper(operatorType);
		entity->mCreateChannel(0, GetLastOper(), 1);
		entity->mCreateChannel(1, GetLastOper(), 2);
		entity->mCreateChannel(GetLastOper() - 1, GetLastOper(), 3);
	}
}

void OperatorTestBase::CreateOper(mainDataType operatorType)
{
	entity->mCreateOperator(operatorType);
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