// CorePerfomanceTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "OperatorTestBase.h"
#include "..\Core\Entity.h"
//#include "C:\Program Files\Microsoft Visual Studio 11.0\VC\include\iostream"
#include <iostream>

using namespace Brans;
using namespace std;

const unsigned long long numberOfCycles = 10000;

//We need manualy synchronize this with OperatorsTypes & OperatorsCount
const char const *OperatorsTypes_str[]=
{
	"Zero", "Division", "Equal", "If", "Minus", "Multiplication", "One", "Plus", "RandomNumber", "Time", 
	//Meta operators:
	"CreateChannel", "CreateOperator", "DeleteChannel", "GetTypeOfOperator", "IsChannelExists", 
	"RemoveOperator", "GetInputOperatorId", "GetOperatorContactsCount", "Nothing"
};

void TestPlus()
{
	OperatorTestBase* opbase = new OperatorTestBase(Plus, 1, 2, 0);
	opbase->Process(numberOfCycles);
	std::cout << "Plus result = " << opbase->GetResult() <<"/n"; 
}

void TestOperator(unsigned int OperatorId)
{
	//cout << "Testing operator " << OperatorsTypes_str[OperatorId];
	OperatorTestBase* opbase = new OperatorTestBase(OperatorId, 3, 2, 1);
	opbase->StartWatch();
	opbase->Process(numberOfCycles);
	opbase->StopWatch();
	cout << "Result = " << opbase->GetResult() <<"\n"
	<< "Elapsed: " << opbase->GetElapsedMiliseconds() << "ms\n"; 
}

void TestOperators()
{
	//OperatorsCount
	for (unsigned int i = 1; i < 11; i++)
	{
		TestOperator(i);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	TestOperator(Zero);
	return 0;
}
