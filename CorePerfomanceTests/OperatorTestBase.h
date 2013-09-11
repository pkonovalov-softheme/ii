#pragma once

#include "..\Core\Entity.h"
class OperatorTestBase
{
public:
	OperatorTestBase(mainDataType operatorType);
	void Process(unsigned long long numberOfCycles);
	mainDataType GetResult();

private:
	void CreateOper(mainDataType operatorType);
	mainDataType GetLastOper();
};

