// CorePerfomanceTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "OperatorTestBase.h"
#include "..\Core\ChallengeManager.h"
//#include "C:\Program Files\Microsoft Visual Studio 11.0\VC\include\iostream"
#include <iostream>
#include <random>
#include <vector>

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
	OperatorTestBase opbase(OperatorId, firstValue, sValue, tValue);
	opbase.StartWatch();
	opbase.Process(numberOfCycles);
	opbase.StopWatch();
	unsigned long curPerf = (numberOfCycles * OperatorsCout * 1000)/opbase.GetElapsedMiliseconds();
	perfomanceSum += curPerf;
	perfomanceCount++;
	result+=opbase.GetResult();
	cout << "\nElapsed: " << opbase.GetElapsedMiliseconds() << "ms\n"
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

void TestEntityGenerationAndClear()
{
	cout << "Testing enteties generation..." << std::endl;
	ChallengeManager cm;
	const mainDataType EntitiesToGenerate = 10000000;
	const mainDataType cyclesCount = EntitiesToGenerate / EntitiesStartPopulation;
	OperatorTestBase opbase;
	opbase.StartWatch();

	for (size_t i = 0; i < cyclesCount; i++)
	{
		cm.GenerateEntities();
		cm.ClearPopulation();
	}

	opbase.StopWatch();
	cout << "Average performance: " << EntitiesToGenerate * 1000 / opbase.GetElapsedMiliseconds() << " Enteties/sec." << std::endl;
}

void TestEntityProcessing()
{
	cout << "Testing enteties generation..." << std::endl;
	ChallengeManager cm;
	cm.GenerateEntities();
	const mainDataType EntitiesToGenerate = 80000000;
	const mainDataType cyclesCount = EntitiesToGenerate / EntitiesStartPopulation;
	OperatorTestBase opbase;
	opbase.StartWatch();

	for (size_t i = 0; i < cyclesCount; i++)
	{
		cm.ProcessEnteties();
	}

	opbase.StopWatch();
	cm.ClearPopulation();
	cout << "Average performance: " << EntitiesToGenerate * 1000 / opbase.GetElapsedMiliseconds() << " Enteties/sec." << std::endl;
}

void TestInputsGenerationAndFillingAnswers()
{
	cout << "Testing enteties generation..." << std::endl;
	ChallengeManager cm;
	const mainDataType OperationCount = 1000000;
	const mainDataType cyclesCount = OperationCount / ChallengeManager::ChallangesCount*ExternalInputsCount;
	
	OperatorTestBase opbase;
	opbase.StartWatch();

	for (size_t i = 0; i < cyclesCount; i++)
	{
		cm.GenerateRandomInputs();
		cm.FillAnswers();
	}

	opbase.StopWatch();
	cm.ClearPopulation();
	cout << "Average performance: " << OperationCount * 2 * 1000 / opbase.GetElapsedMiliseconds() << " Answers + inputs /sec." << std::endl;
}

void ComplexAchiveEffectivityTest()
{
	cout << "Testing enteties generation..." << std::endl;
	ChallengeManager cm;
	const mainDataType EntetiesCount = 1000000;
	const mainDataType cyclesCount = EntetiesCount / EntitiesStartPopulation;

	OperatorTestBase opbase;
	opbase.StartWatch();

	cm.GenerateRandomInputs();
	cm.FillAnswers();
	for (size_t i = 0; i < cyclesCount; i++)
	{
		cm.GenerateEntities();
		cm.ProcessEnteties();
		cm.CalculateEffectiveness();
		std::vector<Entity*> vinners = CustomAlgs::SelectTopNs(cm._population, 1);
		if (vinners.size() > 0)
		{
			if (vinners[0]->GetEffectiveness() >= 1.0) return;
			cm._population.push_back(vinners[0]);
		}
		cm.ClearPopulation();
	}

	opbase.StopWatch();
	cm.ClearPopulation();
	cout << "Average performance: " << EntetiesCount * 1000 / opbase.GetElapsedMiliseconds() << " Enteties /sec." << std::endl;
}




int _tmain(int argc, _TCHAR* argv[])
{
	ComplexAchiveEffectivityTest();
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

	//TestOperators();
	return 0;
}

