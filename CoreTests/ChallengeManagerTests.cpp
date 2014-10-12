#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\ChallengeManager.h"
#include <iostream>
#include <string>
#include <assert.h>  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{
	TEST_CLASS(ChallengeManagerTests)
	{
	public:
		TEST_METHOD(RandomInputs)
		{
			ChallengeManager* cm = new ChallengeManager();
			cm->GenerateRandomInputs();
			mainDataType stats[ChallengeManager::RandomUpperLimit + 1] = {};
			mainDataType test = ChallengeManager::ChallangesCount;
			for (mainDataType cline = 0; cline < ChallengeManager::ChallangesCount; cline++)
			{
				for (mainDataType i = 0; i < ExternalInputsCount; i++)
				{
					mainDataType curVal = cm->_inputs[cline][i];
					stats[curVal]++;
				}
			}

			mainDataType totalCount = ChallengeManager::ChallangesCount * ExternalInputsCount;
			double avg = 1 / (double)ChallengeManager::RandomUpperLimit;
			
			Assert::IsTrue(stats[0] == 0);
			for (mainDataType i = 1; i < ChallengeManager::RandomUpperLimit; i++)
			{
				double freq = stats[i] / (double) totalCount;
				Assert::IsTrue(freq > 0.7 * avg  && freq < 1.3 * avg);
			}
			delete (cm);
		}

		TEST_METHOD(FillAnswersPlus)
		{
			FillAnswerBase(ChallengeManager::Plus);
		}

		TEST_METHOD(FillAnswersMinus)
		{
			FillAnswerBase(ChallengeManager::Minus);
		}

		TEST_METHOD(FillAnswersDivision)
		{
			FillAnswerBase(ChallengeManager::Division);
		}

		TEST_METHOD(FillAnswersIf)
		{
			FillAnswerBase(ChallengeManager::If);
		}

		TEST_METHOD(FillAnswersMultiplication)
		{
			FillAnswerBase(ChallengeManager::Multiplication);
		}

		TEST_METHOD(FillAnswersOne)
		{
			FillAnswerBase(ChallengeManager::One);
		}

		TEST_METHOD(FillAnswersEqual)
		{
			FillAnswerBase(ChallengeManager::Equal);
		}

		void FillAnswerBase(ChallengeManager::ChallengeTypes chType)
		{
			ChallengeManager* cm = new ChallengeManager();
			cm->SetChallengeType(chType);
			cm->GenerateRandomInputs();
			cm->FillAnswers();
			for (mainDataType cline = 0; cline < ChallengeManager::ChallangesCount; cline++)
			{
				for (mainDataType i = 0; i < ExternalInputsCount - 1; i++)
				{
					mainDataType leftOp = cm->_inputs[cline][i];
					mainDataType rightOp = cm->_inputs[cline][i + 1];
					mainDataType expr;

					switch (chType)
					{
					case Brans::ChallengeManager::Division:
						if (rightOp != 0)
							expr = leftOp / rightOp;
						else
							expr = 0;
						break;
					case Brans::ChallengeManager::Equal:
						expr = leftOp;
						break;
					case Brans::ChallengeManager::If:
						expr = leftOp > rightOp;
						break;
					case Brans::ChallengeManager::Minus:
						expr = leftOp - rightOp;
						break;
					case Brans::ChallengeManager::Multiplication:
						expr = leftOp * rightOp;
						break;
					case Brans::ChallengeManager::One:
						expr = 1;
						break;
					case Brans::ChallengeManager::Plus:
						expr = leftOp + rightOp;
						break;
					default:
						throw L"Not implemented";
						break;
					}

					Assert::IsTrue(expr == cm->_correctAnswers[cline][i]);
				}
			}
			delete (cm);
		}

		TEST_METHOD(ComplexEntitySelectionTest)
		{
			//We will emulate StartSelection method
			ChallengeManager* cm = new ChallengeManager();
			//GenerateRandomInputs:
			cm->_inputs[0][0] = 1;
			cm->_inputs[0][1] = 2;

			//FillAnswers:
			cm->_correctAnswers[0][0] = 3;

			std::vector<Entity*> population;

			//GenerateEntities:
			Entity* ent1 = GenerateEntity(Plus);
			ent1->mProcessAll();
			ent1->CalculateEffectiveness(1);
			population.push_back(ent1);
			Entity* ent2 = GenerateEntity(Minus);
			ent2->mProcessAll();
			ent2->CalculateEffectiveness(1);
			population.push_back(ent2);
			Entity* ent3 = GenerateEntity(Multiplication);
			ent3->mProcessAll();
			ent3->CalculateEffectiveness(1);
			population.push_back(ent3);
			Entity* ent4 = GenerateEntity(Plus);
			ent4->mProcessAll();
			ent4->CalculateEffectiveness(1);
			population.push_back(ent4);
			Entity* ent5 = GenerateEntity(Division);
			ent5->mProcessAll();
			ent5->CalculateEffectiveness(1);
			population.push_back(ent5);

			//ProcessEntities:
//			cm->ProcessEnteties();
//			cm->CalculateEffectiveness();

			std::vector<Entity*> vinners = CustomAlgs::SelectTopNs(population, 2);
			Assert::IsTrue(vinners.size() == 2);
			Assert::IsTrue(vinners[0]->GetContactValue(Entity::FirstInternalOper, 0) == Plus);
			Assert::IsTrue(vinners[1]->GetContactValue(Entity::FirstInternalOper, 0) == Plus);
			delete (ent1);
			delete (ent2);
			delete (ent3);
			delete (ent4);
			delete (ent5);
			delete (cm);
		}

		TEST_METHOD(CheckEntityCorrectAnswers)
		{
			ChallengeManager* cm = new ChallengeManager();
			cm->_inputs[0][0] = 1;
			cm->_inputs[0][1] = 2;
			cm->_correctAnswers[0][0] = 3;
			Entity* ent0 = GenerateEntity(Plus);
			ent0->mProcessAll();
			ent0->CalculateEffectiveness(1);
			Assert::IsTrue(ent0->GetEffectiveness() == 1.00);
			delete (cm);
		}

		TEST_METHOD(CheckAllAnswersAreCorrect)
		{
			/*Assert::IsTrue(ExternalInputsCount == 2 && ExternalOutputsCount == 1,
				L"Inputs and outputs must counts must match");*/
			ChallengeManager* cm = new ChallengeManager();
			cm->SetChallengeType(ChallengeManager::ChallengeTypes::Plus);
			cm->GenerateRandomInputs();
			cm->FillAnswers();

			//Entity* ent = GenerateEntity(Plus);

			Entity* ent = GenerateEntity(Plus, ExternalOutputsCount);

			const static unsigned int RedefEntityProcessCount = 10;
			for (int pr = 0; pr < RedefEntityProcessCount; pr++) {
				ent->mProcessAll();
			}

			ent->CalculateEffectiveness(RedefEntityProcessCount);
			Assert::IsTrue(ent->GetEffectiveness() == 1.00);
			delete (ent);
			delete (cm);
		}

		TEST_METHOD(CheckEntityIncorrectAnswers)
		{
			ChallengeManager* cm = new ChallengeManager();
			cm->_inputs[0][0] = 1;
			cm->_inputs[0][1] = 2;
			cm->_correctAnswers[0][0] = 3;
			Entity* ent0 = GenerateEntity(Minus);
			for (int pr = 0; pr < EntityProcessCount; pr++) {
				ent0->mProcessAll();
			}
			ent0->CalculateEffectiveness(EntityProcessCount);
			Assert::IsTrue(ent0->GetEffectiveness() == 0.00);
			delete (ent0);
			delete (cm);
		}

		Entity* GenerateEntityEx(OperatorsTypes opT)
		{
			Entity* ent0 = new Entity;
			for (mainDataType i = 0; i < ExternalInputsCount; i++) {
				ent0->mCreateOperator(opT);
				ent0->mCreateChannel(ExternalInputsCount + 1 + i, ent0->GetOperatorsCount(), 1);
				ent0->mCreateChannel(ExternalInputsCount + 2 + i, ent0->GetOperatorsCount(), 2);
				ent0->mCreateChannel(ent0->GetOperatorsCount(), 1 + i, Entity::outputValueColumn);
			}
			return ent0;
		}

		Entity* GenerateEntity(OperatorsTypes opT, int inputGroupId)
		{
			Entity* ent0 = new Entity;
			ent0->mCreateOperator(opT);

			Assert::IsTrue(ExternalInputsCount >= Entity::mGetOperTypeContactsCount(opT),
				L"ExternalInputsCount must be larger or the same as generated oper contacts count.");

			do
			{
				ent0->mCreateChannel(Entity::FirstExtInputPos + inputGroupId,
					ent0->GetOperatorsCount(),
					Entity::FirstContact);

				ent0->mCreateChannel(Entity::FirstExtInputPos + inputGroupId + 1,
					ent0->GetOperatorsCount(),
					Entity::SecondContact);

				ent0->mCreateChannel(ent0->GetOperatorsCount(),
					Entity::FirstExtOutputPos + inputGroupId,
					Entity::FirstContact); //We will write output value of last created oper to the first external output

				inputGroupId--;
			} while (inputGroupId >= 0);

			return ent0;
		}

		Entity* GenerateEntity(OperatorsTypes opT)
		{
			return GenerateEntity(opT, 0);
		}
	};
}
