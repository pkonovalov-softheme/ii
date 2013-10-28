#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\CustomAlgs.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{
	TEST_CLASS(CustomAlgsTests)
	{
	public:
		
		TEST_METHOD(SelectTopNs)
		{
			EntityStats retAr[4] = {};

			EntityStats es1;
			es1.AddAnswer(true);
			es1.AddAnswer(true);
			es1.AddAnswer(true);
			es1.CalculateEffectiveness(3);

			EntityStats es2;
			es2.AddAnswer(true);
			es2.CalculateEffectiveness(2);
	
			EntityStats es3;
			es3.AddAnswer(true);
			es3.CalculateEffectiveness(10);

			EntityStats es4;
			es4.AddAnswer(true);
			es4.AddAnswer(true);
			es4.CalculateEffectiveness(31);

			retAr[1] = es2;
			retAr[2] = es3;
			retAr[3] = es4;
			retAr[0] = es1;
			EntityStats* esret = CustomAlgs::SelectTopNs(retAr, 2, 4);
			Assert::IsTrue(esret[0].GetEffectiveness() == 1.0);
			Assert::IsTrue(esret[1].GetEffectiveness() == 0.5);
		}
	};
}