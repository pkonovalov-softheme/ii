#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\Entity.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{		
	TEST_CLASS(TestBasicOperators)
	{
	public:
		Entity* ent;
		TEST_METHOD_INITIALIZE(ClassInitialize)
		{
			ent = new Entity();
		}

		TEST_METHOD(TestPlus)
		{
			Entity* ent2 = new Entity();
			ent2->CreateOperator(
		}

	};
}