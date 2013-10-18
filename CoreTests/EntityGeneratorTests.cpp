#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\EntityGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{		
	const mainDataType operatorsCount = 10000;


	TEST_CLASS(TestBasicEntityGenerator) 
	{
	private:
		EntityGenerator* entityGenerator;
		Entity* testEntity;

	public:
		TEST_METHOD_INITIALIZE(ClassInitialize)
		{
			entityGenerator = new EntityGenerator();
			testEntity = &entityGenerator->GenerateEntity();
		}

		TEST_METHOD(TestExternalOutputs)
		{
			OperatorsTypes opType = (OperatorsTypes) testEntity->mGetOperatorType(ExternalOutputsCount);
			Assert::IsTrue(opType == ExternalOutput);
		}

		TEST_METHOD(TestExternalInputs)
		{
			OperatorsTypes opType = (OperatorsTypes) testEntity->mGetOperatorType(ExternalOutputsCount + ExternalInputsCount);
			Assert::IsTrue(opType == ExternalInput);
		}

		TEST_METHOD(GeneratedOperatorsAreValid)
		{
			for (mainDataType i = Entity::FirstInternalOper; i < EntityOperatorsCount; i++)
			{
				OperatorsTypes curOperType = (OperatorsTypes)testEntity->mGetOperatorType(i);
				if (!(curOperType >  OperatorsTypes::Zero && curOperType < OperatorsTypes::Nothing))
				{
					Assert::IsTrue(curOperType >  OperatorsTypes::Zero && curOperType < OperatorsTypes::Nothing);
				}
			}
			Assert::IsTrue(true);
		}
	};
}