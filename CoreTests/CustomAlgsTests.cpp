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
			std::vector<Entity*> retAr;
			retAr.reserve(4);

			Entity es1;
			es1.SetCorrectAnswers(3);
			es1.CalculateEffectiveness(3);

			Entity es2;
			es2.SetCorrectAnswers(1);
			es2.CalculateEffectiveness(2);
	
			Entity es3;
			es3.SetCorrectAnswers(1);
			es3.CalculateEffectiveness(10);

			Entity es4;
			es4.SetCorrectAnswers(2);
			es4.CalculateEffectiveness(31);

			retAr.push_back(&es1);
			retAr.push_back(&es2);
			retAr.push_back(&es3);
			retAr.push_back(&es4);

			std::vector<Entity*> esret = CustomAlgs::SelectTopNs(retAr, 2);
			Assert::IsTrue(esret[0]->GetEffectiveness() == 0.5);
			Assert::IsTrue(esret[1]->GetEffectiveness() == 1.0);
		}
	};
}