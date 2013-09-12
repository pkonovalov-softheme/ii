// CorePerfomanceTests.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "OperatorTestBase.h"
#include "..\Core\Entity.h"
#include "C:\Program Files\Microsoft Visual Studio 11.0\VC\include\iostream"

using namespace Brans;

const unsigned long long numberOfCycles = 1000000;

int _tmain(int argc, _TCHAR* argv[])
{
	OperatorTestBase* opbase = new OperatorTestBase(Plus);
	opbase->Process(numberOfCycles);
	std::cout << "Plus result = " << opbase->GetResult() <<"\n"; 
	return 0;
}

void TestPlus()
{
	OperatorTestBase* opbase = new OperatorTestBase(Plus);
	opbase->Process(numberOfCycles);
	std::cout << "Plus result = " << opbase->GetResult() <<"/n"; 
}