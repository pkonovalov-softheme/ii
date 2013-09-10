#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\Entity.h"
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;

namespace CoreTests
{		
	TEST_CLASS(TestBasicOperators) 
	{
	private:
		Entity* entity;

		void ProcessArgsValues(mainDataType fContactValue, mainDataType sContactValue, mainDataType tContactValue)
		{
			entity->SetContactValue(2, entity->outputValueColumn, tContactValue);
			ProcessArgsValues(fContactValue, sContactValue);
		}

		void ProcessArgsValues(mainDataType fContactValue, mainDataType sContactValue)
		{
			entity->SetContactValue(1, entity->outputValueColumn, sContactValue);
			ProcessArgsValues(fContactValue);
		}

		void ProcessArgsValues(mainDataType fContactValue)
		{
			entity->SetContactValue(0, entity->outputValueColumn, fContactValue);
			Process();
		}

		void CreateOper(mainDataType operatorType)
		{
			entity->mCreateOperator(operatorType);
		}

		void Process()
		{
			mainDataType lastOper = GetLastOper();
			entity->mCreateChannel(0, lastOper, 1);
			entity->mCreateChannel(1, lastOper, 2);
			entity->mCreateChannel(2, lastOper, 3);
			entity->mProcessLast();
		}

		mainDataType GetResult()
		{
			//We have 3 operators for input value + 1 newly created so 3d is current (0-based)
			return entity->GetContactValue(3, entity->outputValueColumn);
		}

		mainDataType GetValue(mainDataType operatorId, mainDataType contactId)
		{
			return entity->GetContactValue(operatorId, contactId);
		}

		mainDataType GetLastOper()
		{
			return (entity->GetNextOperatorId() - 1);
		}

		mainDataType GetLastValue()
		{
			return GetValue(GetLastOper(), entity->outputValueColumn);
		}


	public:
		TEST_METHOD_INITIALIZE(ClassInitialize)
		{
			entity = new Entity();
			CreateOper(Nothing);

			CreateOper(Nothing);
			CreateOper(Nothing);
		}

		/* -------------------------------------------------------------------------------------
		                               Basic Operators
		--------------------------------------------------------------------------------------*/
		TEST_METHOD(TestPlus)
		{
			CreateOper(Plus);
			ProcessArgsValues(1, 2);
			Assert::IsTrue(GetResult() == (1+2));
		}

		TEST_METHOD(TestMinus)
		{
			CreateOper(Minus);
			ProcessArgsValues(3, 1);
			Assert::IsTrue(GetResult() == (3-1));
		}

		TEST_METHOD(TestMinusSubZero)
		{
			CreateOper(Minus);
			ProcessArgsValues(1, 3);
			Assert::IsTrue(GetResult() == (1-3));
		}

		TEST_METHOD(TestMultiplication)
		{
			CreateOper(Multiplication);
			ProcessArgsValues(2, 3);
			Assert::IsTrue(GetResult() == (2*3));
		}

		TEST_METHOD(TestMultiplicationZero)
		{
			CreateOper(Multiplication);
			ProcessArgsValues(0, 3);
			Assert::IsTrue(GetResult() == (0*3));
		}

		/*TEST_METHOD(TestMultiplicationInf)
		{
		entity->mCreateOperator(entity->Multiplication);
		entity->SetContactValue(0, 1, UINT_MAX);
		entity->SetContactValue(0, 2, 2);
		entity->mProcessLast();
		Assert::IsTrue(entity->GetContactValue(0, entity->outputValueColumn) == (UINT_MAX*2));
		}*/

		TEST_METHOD(TestDevision)
		{
			CreateOper(Division);
			ProcessArgsValues(8, 2);
			Assert::IsTrue(GetResult() == (8/2));
		}

		TEST_METHOD(TestDevisionOnZero)
		{
			CreateOper(Division);
			ProcessArgsValues(8, 0);
			Assert::IsTrue(GetResult() == (0));
		}

		TEST_METHOD(TestEqual)
		{
			CreateOper(Equal);
			ProcessArgsValues(3);
			Assert::IsTrue(GetResult() == 3);
		}

		TEST_METHOD(TestIf_false)
		{
			CreateOper(If);
			ProcessArgsValues(1, 3);
			Assert::IsTrue(GetResult() == 0);
		}

		TEST_METHOD(TestIf_true)
		{
			CreateOper(If);
			ProcessArgsValues(3, 1);
			Assert::IsTrue(GetResult() == 1);
		}

		TEST_METHOD(TestOne)
		{
			CreateOper(One);
			ProcessArgsValues(1);
			Assert::IsTrue(GetResult() == 1);
		}

		TEST_METHOD(TestTime)
		{
			CreateOper(Time);
			entity->mProcessLast();
			Assert::IsTrue(GetResult() == time(NULL));
		}

		/* Not implemented
		TEST_METHOD(RandomNumber)
		{
			CreateOper(Time);
			entity->mProcessLast();
			Assert::IsTrue(GetResult() == time(NULL));
		}*/ 

		/* -------------------------------------------------------------------------------------
		                               Meta Operators
		--------------------------------------------------------------------------------------*/

		TEST_METHOD(BasicCreateChannelTest)
		{
			CreateOper(Plus);
			CreateOper(Plus);
			CreateOper(CreateChannel);

			const mainDataType fromOperator = 3;
			const mainDataType toOperator = 4;
			const mainDataType toOperatorContactId = 1;

			ProcessArgsValues(fromOperator, toOperator, toOperatorContactId);
			Assert::IsTrue(GetValue(toOperator, toOperatorContactId) == fromOperator);
		}

		TEST_METHOD(UnderTheLimitCreateChannelTest)
		{
			CreateOper(Plus);
			CreateOper(Plus);
			CreateOper(CreateChannel);

			const mainDataType fromOperator = UINT_MAX * 10;
			const mainDataType toOperator = 4;
			const mainDataType toOperatorContactId = 1;

			ProcessArgsValues(fromOperator, toOperator, toOperatorContactId);
			Assert::IsTrue(GetValue(toOperator, toOperatorContactId) == 0);
		}

		TEST_METHOD(CreateOperatorTest)
		{
			CreateOper(CreateOperator);
			ProcessArgsValues(Plus);
			Assert::IsTrue(entity->GetContactValue(GetLastOper(), entity->operatorTypeColumn) == Plus);
		}

		TEST_METHOD(DeleteChannelTest)
		{
			const mainDataType fromOperator = 1;
			const mainDataType toOperator = 2;
			const mainDataType toOperatorContactId = 2;

			entity->mCreateChannel(fromOperator, toOperator, toOperatorContactId);
			CreateOper(DeleteChannel);
			ProcessArgsValues(toOperator, toOperatorContactId);
			Assert::IsTrue(GetValue(toOperator, toOperatorContactId) == 0);
		}

		TEST_METHOD(GetTypeOfOperatorTest)
		{
			CreateOper(GetTypeOfOperator);
			ProcessArgsValues(GetLastOper());
			Assert::IsTrue(GetLastValue() == GetTypeOfOperator);
		}

		TEST_METHOD(IsChannelExistsTest)
		{
			CreateOper(Plus);
			CreateOper(Plus);
			CreateOper(IsChannelExists);

			const mainDataType fromOperator = 3;
			const mainDataType toOperator = 4;
			const mainDataType toOperatorContactId = 1;

			entity->mCreateChannel(fromOperator, toOperator, toOperatorContactId);
			ProcessArgsValues(fromOperator, toOperator, toOperatorContactId);
			Assert::IsTrue(GetLastValue() == 1);
			ProcessArgsValues(fromOperator - 1, toOperator, toOperatorContactId);
			Assert::IsTrue(GetLastValue() == 0);
		}

		TEST_METHOD(RemoveOperatorTest)
		{
			CreateOper(Plus);
			CreateOper(RemoveOperator);
			mainDataType plusOperId = GetLastOper() - 1;
			ProcessArgsValues(plusOperId);
			Assert::IsTrue(entity->GetContactValue(plusOperId, entity->operatorTypeColumn) == Nothing);
		}

		TEST_METHOD(GetInputOperatorIdTest)
		{
			CreateOper(Plus);
			CreateOper(GetInputOperatorId);
			entity->mCreateChannel(3, 4, 1);
			entity->mProcessLast();
			Assert::IsTrue(GetLastValue() == 3);
		}

		TEST_METHOD(GetOperatorContactsCountTest)
		{
			CreateOper(Plus);
			CreateOper(GetOperatorContactsCount);
			ProcessArgsValues(GetLastOper() - 1);
			Assert::IsTrue(GetLastValue() == 2);
		}

		TEST_METHOD(NothingTest)
		{
			CreateOper(Nothing);
			ProcessArgsValues(1,2,3);
			Assert::IsTrue(GetLastValue() == 0);
		}
	};
}