#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\EntityGenerator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{		
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

		TEST_METHOD(GeneratedOperatorsTypesAreValid)
		{
			for (mainDataType i = Entity::FirstInternalOper; i < EntityOperatorsCount; i++)
			{
				OperatorsTypes curOperType = (OperatorsTypes)testEntity->mGetOperatorType(i);
				if (!(curOperType >  OperatorsTypes::Zero && curOperType < OperatorsTypes::Nothing))
				{
					Assert::IsTrue(curOperType >  OperatorsTypes::Zero && curOperType < OperatorsTypes::Nothing);
				}
			}
		}

		TEST_METHOD(GeneratedOperatorsIdsAreValid)
		{
			for (mainDataType curOp = Entity::FirstInternalOper; curOp < EntityOperatorsCount; curOp++)
			{
				OperatorsTypes curOperType = (OperatorsTypes)testEntity->mGetOperatorType(curOp);
				for (int curContact = 1; curContact <= EntityGenerator::GetOperTypeContactsCount(curOperType); curContact++)
				{
					mainDataType curVal = testEntity->GetContactValue(curOp, curContact);
					Assert::IsTrue(curVal > 0 && curVal <= EntityOperatorsCount);
				}
			}
		}
	};
}