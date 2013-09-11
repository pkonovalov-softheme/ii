#pragma once
#include "..\Core\Entity.h"

ref class OperatorTestBase
{
public:
	OperatorTestBase(mainDataType operatorType);
	void Process(unsigned long long numberOfCycles);
	mainDataType GetResult();

private:

	Entity* entity;
	void CreateOper(mainDataType operatorType);
	mainDataType GetLastOper();

};

