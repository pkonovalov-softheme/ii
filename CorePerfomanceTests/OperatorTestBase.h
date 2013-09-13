#pragma once

#include "..\Core\Entity.h"


class OperatorTestBase
{
public:
	OperatorTestBase(mainDataType operatorType, mainDataType firstValue, mainDataType secondValue, mainDataType thirdValue);
	void Process(unsigned long long numberOfCycles);
	mainDataType GetResult();
	void StartWatch();
	void StopWatch();
	unsigned long GetElapsedMiliseconds();

private:
	void CreateOper(mainDataType operatorType);
	void SetValue(mainDataType operatorId, mainDataType valueToSet);
	mainDataType GetLastOper();
};

