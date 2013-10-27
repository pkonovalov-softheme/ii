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
			es1.effectiveness = 3.3;
			EntityStats es2;
			es2.effectiveness = 0.1;
			EntityStats es3;
			es3.effectiveness = 2.2;
			EntityStats es4;
			es4.effectiveness = 4.4;
			retAr[1] = es2;
			retAr[2] = es3;
			retAr[3] = es4;
			retAr[0] = es1;
			EntityStats* esret = CustomAlgs::SelectTopNs(retAr, 2, 4);
			Assert::IsTrue(esret[0].effectiveness == 3.3);
			Assert::IsTrue(esret[1].effectiveness == 4.4);
		}
	};
}