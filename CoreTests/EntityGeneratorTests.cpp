#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\Entity.h"
#include "..\Core\EntityGenerator.h"
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{		
	const mainDataType operatorsCount = 10000;
	const mainDataType externalEntersCount = 5;
	const mainDataType externalExitsCount = 7;

	TEST_CLASS(TestBasicEntityGenerator) 
	{
	private:
		EntityGenerator* entityGenerator;
		Entity* testEntity;

	public:
		TEST_METHOD_INITIALIZE(ClassInitialize)
		{
			entityGenerator = new EntityGenerator();
			testEntity = &entityGenerator->GenerateEntity(operatorsCount, externalEntersCount, externalExitsCount);
		}

		TEST_METHOD(TestExternalEntersCount)
		{
			OperatorsTypes opType = (OperatorsTypes)testEntity->mGetOperatorType(externalEntersCount);
			Assert::IsTrue(opType == ExternalInput);
            opType = (OperatorsTypes)testEntity->mGetOperatorType(externalEntersCount + 1);
			Assert::IsFalse(opType == ExternalInput);
		}
	};
}