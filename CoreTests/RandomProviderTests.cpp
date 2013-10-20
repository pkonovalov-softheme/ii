#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\RandomProvider.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{
	TEST_CLASS(RandomProviderTests)
	{
	private:
		
		RandomOperatorsProvider _rop;
		const mainDataType ValuesUpperLimit = 3;
		const int Cycles = 10000;

		void CheckDistribution(int one, int two, int three)
		{
			double onePerc = one / (double)Cycles;
			double twoPerc = two / (double)Cycles;
			double threePerc = three / (double)Cycles;

			Assert::IsTrue(onePerc > 0.20 && onePerc < 0.40);
			Assert::IsTrue(twoPerc > 0.20 && twoPerc < 0.40);
			Assert::IsTrue(threePerc > 0.20 && threePerc < 0.40);
		}

	public:
		
		TEST_METHOD(RandomValuesProviderInstance)
		{
			RandomValuesProvider rvp = RandomValuesProvider(ValuesUpperLimit);
			int one = 0, two = 0, three = 0;

			for (int i = 0; i < Cycles; i++)
			{
				mainDataType res = rvp.GetNextValue();
				if (res == 1) one++;
				if (res == 2) two++;
				if (res == 3) three++;
			}

			CheckDistribution(one, two, three);
		}

		TEST_METHOD(RandomValuesProviderStatic)
		{
			int one = 0, two = 0, three = 0;

			for (int i = 0; i < Cycles; i++)
			{
				mainDataType res = RandomValuesProvider::GetNextValue(ValuesUpperLimit);
				if (res == 1) one++;
				if (res == 2) two++;
				if (res == 3) three++;
			}

			CheckDistribution(one, two, three);
		}

		TEST_METHOD(RandomOperatorsProvider)
		{
			const mainDataType GeneratedOperatorsCount = OperatorsCount - 3;
			double perc = 1 / (double)GeneratedOperatorsCount;
			double upperLim = 1.5 * perc;
			double downLim = 0.5 * perc;

			/*double vZero = 0, vDivision = 0, vEqual = 0, vIf = 0, vMinus = 0, vMultiplication = 0, vOne = 0, 
				vPlus = 0, vRandomNumber = 0, vTime = 0, vCreateChannel = 0, vCreateOperator = 0, vDeleteChannel = 0,
				vGetTypeOfOperator = 0, vIsChannelExists = 0, vRemoveOperator = 0, vGetInputOperatorId = 0,
				vGetOperatorContactsCount = 0, vExternalInput = 0, vExternalOutput = 0, vNothing = 0;*/

			double results[OperatorsCount] = {};

			for (int i = 0; i < Cycles; i++)
			{
				OperatorsTypes opT = (OperatorsTypes)RandomOperatorsProvider::GetNextOperator();
				switch (opT)
				{
				case Brans::Zero:
					Assert::Fail(L"BadOper: Zero");
					break;
				case Brans::Division:
					results[Division]++;
					break;
				case Brans::Equal:
					results[Equal]++;
					break;
				case Brans::If:
					results[If]++;
					break;
				case Brans::Minus:
					results[Minus]++;
					break;
				case Brans::Multiplication:
					results[Multiplication]++;
					break;
				case Brans::One:
					results[One]++;
					break;
				case Brans::Plus:
					results[Plus]++;
					break;
				case Brans::RandomNumber:
					results[RandomNumber]++;
					break;
				case Brans::Time:
					results[Time]++;
					break;
				case Brans::CreateChannel:
					results[CreateChannel]++;
					break;
				case Brans::CreateOperator:
					results[CreateOperator]++;
					break;
				case Brans::DeleteChannel:
					results[DeleteChannel]++;
					break;
				case Brans::GetTypeOfOperator:
					results[GetTypeOfOperator]++;
					break;
				case Brans::IsChannelExists:
					results[IsChannelExists]++;
					break;
				case Brans::RemoveOperator:
					results[RemoveOperator]++;
					break;
				case Brans::GetInputOperatorId:
					results[GetInputOperatorId]++;
					break;
				case Brans::GetOperatorContactsCount:
					results[GetOperatorContactsCount]++;
					break;
				case Brans::ExternalInput:
					Assert::Fail(L"BadOper: ExternalInput");
					break;
				case Brans::ExternalOutput:
					Assert::Fail(L"BadOper: ExternalOutput");
					break;
				case Brans::Nothing:
					Assert::Fail(L"BadOper: Nothing");
					break;
				default:
					Assert::Fail(L"BadOper: Unknown operator type");
					break;
				}
			}

			for (int i = Division; i < ExternalInput; i++)
			{
				double curPerc = results[i] / (double)Cycles;

				if (!(curPerc > downLim && curPerc < upperLim))
				{
					curPerc = curPerc;
				}
				Assert::IsTrue(curPerc > downLim && curPerc < upperLim);
			}


		}

	};
}