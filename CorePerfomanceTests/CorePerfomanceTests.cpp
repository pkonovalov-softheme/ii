// CorePerfomanceTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "OperatorTestBase.h"
#include "..\Core\Entity.h"
//#include "C:\Program Files\Microsoft Visual Studio 11.0\VC\include\iostream"
#include <iostream>
#include <random>

using namespace Brans;
using namespace std;

unsigned long perfomanceSum;
unsigned long result;
unsigned short perfomanceCount;

//We need manualy synchronize this with OperatorsTypes & OperatorsCount
const char const *OperatorsTypes_str[]=
{
	"Zero", "Division", "Equal", "If", "Minus", "Multiplication", "One", "Plus", "RandomNumber", "Time", 
	//Meta operators:
	"CreateChannel", "CreateOperator", "DeleteChannel", "GetTypeOfOperator", "IsChannelExists", 
	"RemoveOperator", "GetInputOperatorId", "GetOperatorContactsCount", "Nothing"
};

void TestOperator(unsigned int OperatorId, mainDataType firstValue, mainDataType sValue, mainDataType tValue)
{
	cout << "Testing operator " << OperatorsTypes_str[OperatorId];
	OperatorTestBase* opbase = new OperatorTestBase(OperatorId, firstValue, sValue, tValue);
	opbase->StartWatch();
	opbase->Process(numberOfCycles);
	opbase->StopWatch();
	unsigned long curPerf = (numberOfCycles * OperatorsCout * 1000)/opbase->GetElapsedMiliseconds();
	perfomanceSum += curPerf;
	perfomanceCount++;
	result+=opbase->GetResult();
	cout << "\nElapsed: " << opbase->GetElapsedMiliseconds() << "ms\n"
	<< "Performance: " << curPerf << " operations/sec.\n"; 
}

void TestOperators()
{
	//OperatorsCount
	//for (unsigned int i = 1; i < 11; i++)
	//{
	//	TestOperator(i);
	//}
	Entity *entl = new Entity();
	TestOperator(Division, 8, 2, 0);
	TestOperator(Equal, 2, 0, 0);
	TestOperator(If, 2, 1, 0);
	TestOperator(Minus, 3, 1, 0);
	TestOperator(Multiplication, 2, 3, 0);
	TestOperator(One, 0, 0, 0);
	TestOperator(Plus, 2, 3, 0);
	TestOperator(RandomNumber, 10, 0, 0);
	TestOperator(Time, 0, 0, 0);

	TestOperator(CreateChannel, 1, 4, 1);
	TestOperator(CreateOperator, Nothing, 0, 0);
	TestOperator(DeleteChannel, 4, 1, 0);
	TestOperator(GetTypeOfOperator, 1, 0, 0);
	TestOperator(IsChannelExists, 1, 4, 1);
	TestOperator(RemoveOperator, 7, 0, 0);
	TestOperator(GetInputOperatorId, 0, 0, 0);
	TestOperator(GetOperatorContactsCount, Plus, 0, 0);
	TestOperator(Nothing, 0, 0, 0);

	cout << "Average performance: " << perfomanceSum/perfomanceCount << " operations/sec.\n"; 
	cout << "Result: " << result << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//std::random_device rd;
	//std::mt19937 e1(rd());
	//std::uniform_int_distribution<int> uniform_dist(1, 3);
	//int val = uniform_dist(e1);


	//unsigned int one=0, two =0, three = 0;

	//OperatorTestBase* opbase = new OperatorTestBase(0, 0, 0, 0);
	//opbase->StartWatch();
	//for (int i =0; i < 100000000; i++)
	//{
	//	int val = uniform_dist(e1);
	//	if (val == 1) one++;
	//	if (val == 2) two++;
	//	if (val == 3) three++;
	//}
	//opbase->StopWatch();
	//cout << "\nElapsed: " << opbase->GetElapsedMiliseconds() << "ms\n" << std::endl << "one=" << one << std::endl;

	TestOperators();
	return 0;
}
