#pragma once

#include "..\Core\Entity.h"

const unsigned long long numberOfCycles = 10000;
const unsigned int OperatorsCout = 1000;

class OperatorTestBase
{
public:
	OperatorTestBase::OperatorTestBase();
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

