#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\EntityGenerator.h"
#include <algorithm>    // std::sort

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

		TEST_METHOD_CLEANUP(CleanUp)
		{
			delete entityGenerator;
		}

		TEST_METHOD(TestExternalOutputs)
		{
			OperatorsTypes opType = static_cast<OperatorsTypes>(testEntity->mGetOperatorType(ExternalOutputsCount));
			Assert::IsTrue(opType == ExternalOutput);
		}

		TEST_METHOD(TestExternalInputs)
		{
			OperatorsTypes opType = static_cast<OperatorsTypes>(testEntity->mGetOperatorType
				(ExternalOutputsCount + ExternalInputsCount));
			Assert::IsTrue(opType == ExternalInput);
		}

		TEST_METHOD(GeneratedOperatorsTypesAreValid)
		{
			for (size_t i = 0; i < 1000; i++)
			{
				Entity* curEntity = &entityGenerator->GenerateEntity();
				for (mainDataType i = Entity::FirstInternalOper; i < EntityOperatorsCount; i++)
				{
					OperatorsTypes curOperType = static_cast<OperatorsTypes>(curEntity->mGetOperatorType(i));
					Assert::IsTrue(curOperType >  Zero && curOperType < ExternalInput);
				}
			}
		}

		TEST_METHOD(GeneratedOperatorsIdsAreValid)
		{
			Entity* curEntity;
			for (size_t i = 0; i < 1000; i++)
			{
				curEntity = &entityGenerator->GenerateEntity();
				for (mainDataType curOp = Entity::FirstInternalOper; curOp < EntityOperatorsCount; curOp++)
				{
					OperatorsTypes curOperType = static_cast<OperatorsTypes>(curEntity->mGetOperatorType(curOp));
					//Assert::IsTrue(curOperType != ExternalOutput, L"Must not be connected with ExternalOutput");

					for (int curContact = Entity::FirstContact; curContact <= Entity::mGetOperTypeContactsCount(curOperType); curContact++)
					{
						mainDataType curVal = curEntity->GetContactValue(curOp, curContact);
						//if (!(curVal > 0 && curVal < EntityOperatorsCount))
						//{
						//	curVal = curVal;
						//}

						Assert::IsTrue(curVal > 0 && curVal < EntityOperatorsCount, L"All connection must be with valid operators");
					}
				}
			}
		}

		TEST_METHOD(LastGeneratedOperatorIsNotZero)
		{
			Entity* curEntity;
			for (size_t i = 0; i < 1000; i++)
			{
				curEntity = &entityGenerator->GenerateEntity();
				mainDataType lastOpId = curEntity->GetOperatorsCount();
				Assert::IsTrue(curEntity->GetContactValue(lastOpId, 0) != Zero);
			}
		}

		TEST_METHOD(GeneratedSequencesNotSame)
		{
			EntityGenerator entityGenerator1;
			EntityGenerator entityGenerator2;

			Entity* ent1 = &entityGenerator1.GenerateEntity();
			Entity* ent2 = &entityGenerator2.GenerateEntity();

			Assert::IsFalse(ent1->IsEqual(ent2));
		}

		TEST_METHOD(ExternalOutputsConnectionsAreValid)
		{
			for (size_t i = 0; i < 100; i++)
			{
				Entity* curEntity = &entityGenerator->GenerateEntity();
				for (int curOper = Entity::FirstExtOutputPos; curOper < Entity::FirstExtOutputPos + ExternalOutputsCount; curOper++)
				{
					int fromOperId = curEntity->GetContactValue(curOper, Entity::FirstContact);
					OperatorsTypes fromOperType = (OperatorsTypes)curEntity->mGetOperatorType(fromOperId);
					Assert::IsTrue(fromOperType > Zero && fromOperType < ExternalOutput, L"From Operator must be not Zero or External Output op.");
				}
			}
		}

		TEST_METHOD(GeneratedCoreEntityIsValid)
		{
			EntityGenerator entityGenerator;

			while (entityGenerator.NextEntityCore())
			{
				for (size_t i = 0; i < EntityInternalOperatorsCount; i++)
				{
					Assert::IsTrue(entityGenerator.state[i] > OperatorsTypes::Zero
								&& entityGenerator.state[i] < OperatorsTypes::ExternalInput,
								   L"All generated operators must be valid");
				}
			}

		}

		TEST_METHOD(GeneratedCoreEntitiesAreDifferent)
		{
			EntityGenerator entityGenerator;
			std::vector<int> generetedEnteties;
			int curVal = 0;

			while (entityGenerator.NextEntityCore())
			{
				for (size_t i = 0; i < EntityInternalOperatorsCount; i++)
				{
					curVal *= 10;
					curVal += entityGenerator.state[i];
				}

				generetedEnteties.push_back(curVal);
				curVal = 0;
			}

			std::sort(generetedEnteties.begin(), generetedEnteties.end());
			std::vector<int>::iterator it;
			it = std::unique(generetedEnteties.begin(), generetedEnteties.end());
			size_t size = std::distance(generetedEnteties.end(), it);

			if (size < 0)
			{
				Assert::Fail(L"There are duplicates");
			}
		}
	};
}