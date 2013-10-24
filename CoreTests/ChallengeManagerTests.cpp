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
		}

		TEST_METHOD(FillAnswersPlus)
		{
			ChallengeManager* cm = new ChallengeManager();
			cm->GenerateRandomInputs();
			cm->FillAnswers();
			for (mainDataType cline = 0; cline < ChallengeManager::ChallangesCount; cline++)
			{
				#define inputs cm->_inputs[cline];
				Assert::IsTrue(inputs[0] + inputs[1] == )
			}

			

		}
	};
}