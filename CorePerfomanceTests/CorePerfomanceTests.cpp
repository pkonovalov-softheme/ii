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
	ChallengeManager cm;
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

	cout << "Average performance: " << perfomanceSum/perfomanceCount << " operations/sec.\n"; 
	cout << "Result: " << result << std::endl;

}

void TestEntityGeneration()
{
	cout << "Testing EntityGenerationAndClear..." << std::endl;
	ChallengeManager cm;
	const mainDataType EntitiesToGenerate = 10000000;
	const mainDataType cyclesCount = EntitiesToGenerate / EntitiesStartPopulation;
	OperatorTestBase opbase;
	opbase.StartWatch();

	for (size_t i = 0; i < cyclesCount; i++)
	{
		cm._entityGenerator->GenerateEntity();
	}

	opbase.StopWatch();
	cout << "Average performance: " << EntitiesToGenerate * 1000 / opbase.GetElapsedMiliseconds() << " Enteties/sec." << std::endl;
}

void TestEntityProcessing()
{
	cout << "Testing enteties Processing..." << std::endl;
	ChallengeManager cm;

	Entity& ent = cm._entityGenerator->GenerateEntity();

	const mainDataType EntitiesToGenerate = 80000000;
	const mainDataType cyclesCount = EntitiesToGenerate / EntitiesStartPopulation;
	OperatorTestBase opbase;
	opbase.StartWatch();

	for (size_t i = 0; i < cyclesCount; i++)
	{
		for (int pr = 0; pr < EntityProcessCount; pr++) {
			ent.mProcessAll();
		}
	}

	opbase.StopWatch();
	cout << "Average performance: " << EntitiesToGenerate * 1000 / opbase.GetElapsedMiliseconds() << " Enteties/sec." << std::endl;
}

void TestInputsGenerationAndFillingAnswers()
{
	cout << "Testing InputsGenerationAndFillingAnswers..." << std::endl;
	ChallengeManager cm;
	const mainDataType OperationCount = 4000000;
	const mainDataType cyclesCount = OperationCount / ChallengeManager::ChallangesCount*ExternalInputsCount;
	
	OperatorTestBase opbase;
	opbase.StartWatch();

	for (size_t i = 0; i < cyclesCount; i++)
	{
		cm.GenerateRandomInputs();
		cm.FillAnswers();
	}

	opbase.StopWatch();
	cout << "Average performance: " << OperationCount * 2 * 1000 / opbase.GetElapsedMiliseconds() << " Answers + inputs /sec." << std::endl;
}


namespace Brans
{
	static const mainDataType EntetiesToProcessCount = 5 * 1000 * 1000 * 1000;
}

void ComplexAchiveEffectivity()
{
	cout << "Testing ComplexAchiveEffectivity generation..." << std::endl;
	const mainDataType EntetiesCount = 5000000;
	const mainDataType cyclesCount = EntetiesCount / EntitiesStartPopulation;

	OperatorTestBase opbase;
	opbase.StartWatch();

	EntetiesProcessed = 0;
	ChallengeManager* cm = new ChallengeManager();
	Entity* ent = cm->AchiveEffectivity(0.01);

	opbase.StopWatch();
	cout << "Average performance: " << EntetiesProcessed / opbase.GetElapsedMiliseconds() << " Enteties /sec." << std::endl;
	delete(cm);
}

void SelectNTest()
{
	cout << "Testing SelectN..." <<  std::endl;
	EntityGenerator entityGenerator;
	mainDataType EntitiesCount = 1000000;
	//mainDataType SelectionCount = 1000;

	ChallengeManager cm;
	std::vector<Entity*> all;
	all.reserve(EntitiesCount);

	std::vector<double> vinners;

	for (size_t i = 0; i < EntitiesCount; i++)
	{
		Entity& ent = entityGenerator.GenerateEntity();
		ent.SetCorrectAnswers(RandomValuesProvider::GetNextValue(500));
		ent.CalculateEffectiveness(700);
		all.push_back(&ent);
	}

	OperatorTestBase opbase;
	opbase.StartWatch();
	Entity* vinner = CustomAlgs::SelectTopNs(all, 1)[0]; //will be bullprt error
	vinners.push_back(vinner->GetEffectiveness());
	opbase.StopWatch();

	cout << "Vinner Effectivnes" << vinners[0] << std::endl;
	cout << "Average performance: " << /*SelectionCount **/ EntitiesCount * 1000 / opbase.GetElapsedMiliseconds() << "Enteties/sec"
		 << std::endl;

	while (!all.empty()) {
		delete all.back();
		all.pop_back();
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	ComplexAchiveEffectivity();
	//SelectNTest();
	//TestOperators();
	//TestEntityGenerationAndClear();
	//TestEntityProcessing();
//	TestInputsGenerationAndFillingAnswers();
	//ComplexAchiveEffectivity();
	return 0;
}

