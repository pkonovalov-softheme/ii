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
	void SetValue(mainDataType operatorId, mainDataType valueToSet);
	mainDataType GetLastOper();
};

