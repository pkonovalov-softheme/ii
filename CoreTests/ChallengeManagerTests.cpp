#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\ChallengeManager.h"

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
			cm->_curChallangeType = chType;
			cm->GenerateRandomInputs();
			cm->FillAnswers();
			for (mainDataType cline = 0; cline < ChallengeManager::ChallangesCount; cline++)
			{
				for (mainDataType i = 0; i < ExternalInputsCount; i++)
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

		TEST_METHOD(Fill11)
		{
			//We really should use mocks threre, but i don;t want to add it now, maybe later

			//We will emulate StartSelection method
			ChallengeManager* cm = new ChallengeManager();
			//GenerateRandomInputs:
			cm->_inputs[0][0] = 1;
			cm->_inputs[0][1] = 2;

			//FillAnswers:
			cm->_correctAnswers[0][0] = 3;

			//GenerateEntities:
			Entity ent0;
			ent0.mCreateOperator(Plus);

			Entity ent1;
			ent1.mCreateOperator(Minus);


			cm->_population.push_back(&ent0);
			cm->_population.push_back(&ent1);

			//ProcessEntities:
			cm->ProcessEnteties();
			cm->CalculateEffectiveness();

			std::vector<Entity*> vinners = CustomAlgs::SelectTopNs(cm->_population, 3, EntitiesStartPopulation);

			delete (cm);
		}

		TEST_METHOD(CheckEntityCorrectAnswers)
		{
			ChallengeManager* cm = new ChallengeManager();
			cm->_inputs[0][0] = 1;
			cm->_inputs[0][1] = 2;

			cm->_correctAnswers[0][1] = 3;

			Entity* ent0 = new Entity();
			ent0->mCreateOperator(Plus);
			ent0->mCreateChannel(ExternalInputsCount + 1, ent0->GetOperatorsCount(), 1);
			ent0->mCreateChannel(ExternalInputsCount + 2, ent0->GetOperatorsCount(), 2);
			static const unsigned short outputValueColumn = 4;
			ent0->mCreateChannel(ent0->GetOperatorsCount(), 1, outputValueColumn);
			cm->_population.push_back(ent0);
			ent0->mProcessAll();
			ent0->CalculateEffectiveness(1);

			Assert::IsTrue(cm->_population[0]->GetEffectiveness() == 1.00);

			delete (cm);
		}

		TEST_METHOD(CheckEntityIncorrectAnswers)
		{
			ChallengeManager* cm = new ChallengeManager();
			cm->_inputs[0][0] = 1;
			cm->_inputs[0][1] = 2;

			cm->_correctAnswers[0][1] = 3;

			Entity* ent0 = new Entity();
			ent0->mCreateOperator(Minus);
			ent0->mCreateChannel(ExternalInputsCount + 1, ent0->GetOperatorsCount(), 1);
			ent0->mCreateChannel(ExternalInputsCount + 2, ent0->GetOperatorsCount(), 2);
			static const unsigned short outputValueColumn = 4;
			ent0->mCreateChannel(ent0->GetOperatorsCount(), 1, outputValueColumn);
			cm->_population.push_back(ent0);
			ent0->mProcessAll();
			ent0->CalculateEffectiveness(1);

			Assert::IsTrue(cm->_population[0]->GetEffectiveness() == 0.00);

			delete (cm);
		}
	};
}