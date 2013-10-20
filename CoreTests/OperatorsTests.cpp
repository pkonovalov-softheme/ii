#pragma once
#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Core\Entity.h"
#include "Windows.h"
#include <time.h>
#include <string.h>
#include <atlstr.h>
#include <iostream>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Brans;
using namespace std;

namespace CoreTests
{

	TEST_CLASS(TestBasicOperators) 
	{
	private:
		Entity* entity;
		//Here we setting up values of output column for first 3 operators(nothing) then we will create channels between them
		//and last operators input contacts, so it will process that values
		void ProcessArgsValues(mainDataType fContactValue, mainDataType sContactValue, mainDataType tContactValue)
		{
			entity->SetContactValue(Entity::FirstInternalOper + 2, entity->outputValueColumn, tContactValue);
			ProcessArgsValues(fContactValue, sContactValue);
		}

		void ProcessArgsValues(mainDataType fContactValue, mainDataType sContactValue)
		{
			entity->SetContactValue(Entity::FirstInternalOper + 1, entity->outputValueColumn, sContactValue);
			ProcessArgsValues(fContactValue);
		}

		void ProcessArgsValues(mainDataType fContactValue)
		{
			entity->SetContactValue(Entity::FirstInternalOper, entity->outputValueColumn, fContactValue);
			mainDataType lastOper = GetLastOper();
			entity->mCreateChannel(Entity::FirstInternalOper, lastOper, 1);
			entity->mCreateChannel(Entity::FirstInternalOper + 1, lastOper, 2);
			entity->mCreateChannel(Entity::FirstInternalOper + 2, lastOper, 3);
			entity->mProcessLast();
		}

		void CreateOper(mainDataType operatorType)
		{
			entity->mCreateOperator(operatorType);
		}

		mainDataType GetResult()
		{
			//We have 3 operators for input value + 1 newly created so 3d is current (0-based)
			return entity->GetContactValue(GetLastOper(), entity->outputValueColumn);
		}

		mainDataType GetValue(mainDataType operatorId, mainDataType contactId)
		{
			mainDataType result = entity->GetContactValue(operatorId, contactId);
			return result;
		}

		mainDataType GetLastOper()
		{
			return (entity->GetNextOperatorId() - 1);
		}

		mainDataType GetLastValue()
		{
			return GetValue(GetLastOper(), entity->outputValueColumn);
		}

		void WriteToDebugWindow(double val)
		{
			CString strBuffer;
			strBuffer.Format(_T("%f"), val);
			OutputDebugString(strBuffer);
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
		TEST_METHOD(PlusOp)
		{
			CreateOper(Plus);
			ProcessArgsValues(1, 2);
			mainDataType result = GetResult();
			Assert::IsTrue(result == (1+2));
		}

		TEST_METHOD(MinusOp)
		{
			CreateOper(Minus);
			ProcessArgsValues(3, 1);
			Assert::IsTrue(GetResult() == (3-1));
		}

		TEST_METHOD(OpMinusSubZero)
		{
			CreateOper(Minus);
			ProcessArgsValues(1, 3);
			Assert::IsTrue(GetResult() == (1-3));
		}

		TEST_METHOD(MultiplicationOp)
		{
			CreateOper(Multiplication);
			ProcessArgsValues(2, 3);
			Assert::IsTrue(GetResult() == (2*3));
		}

		TEST_METHOD(OpMultiplicationZero)
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

		TEST_METHOD(DevisionOp)
		{
			CreateOper(Division);
			ProcessArgsValues(8, 2);
			Assert::IsTrue(GetResult() == (8/2));
		}

		TEST_METHOD(DevisionOnZeroOp)
		{
			CreateOper(Division);
			ProcessArgsValues(8, 0);
			Assert::IsTrue(GetResult() == (0));
		}

		TEST_METHOD(EqualOp)
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

		TEST_METHOD(OneOp)
		{
			CreateOper(One);
			ProcessArgsValues(1);
			Assert::IsTrue(GetResult() == 1);
		}

		TEST_METHOD(TimeOp)
		{
			CreateOper(Time);
			entity->mProcessLast();
			Assert::IsTrue(GetResult() == time(NULL));
		}


		TEST_METHOD(RandomNumberOp)
		{
			CreateOper(RandomNumber);
			int one = 0, two = 0, three = 0, unlim = 0;
			const int cycles = 10000;

			for (int i = 0; i < cycles; i++)
			{
				entity->mProcessLast();
				ProcessArgsValues(3);
				mainDataType res = GetLastValue();
				if (res == 1) one++;
				if (res == 2) two++;
				if (res == 3) three++;
			}

			double onePerc = one / (double)cycles;
			double twoPerc = two / (double)cycles;
			double threePerc = three / (double)cycles;

    		Assert::IsTrue(onePerc > 0.20 && onePerc < 0.40);
			Assert::IsTrue(twoPerc > 0.20 && twoPerc < 0.40);
			Assert::IsTrue(threePerc > 0.20 && threePerc < 0.40);
		}

		/* -------------------------------------------------------------------------------------
		                               Meta Operators
		--------------------------------------------------------------------------------------*/

		TEST_METHOD(BasicCreateChannelOp)
		{
			CreateOper(Plus);
			CreateOper(Plus);
			CreateOper(CreateChannel);

			const mainDataType fromOperator = Entity::FirstInternalOper + 3;
			const mainDataType toOperator = fromOperator + 1;
			const mainDataType toOperatorContactId = 1;

			ProcessArgsValues(fromOperator, toOperator, toOperatorContactId);
			Assert::IsTrue(GetValue(toOperator, toOperatorContactId) == fromOperator);
		}

		TEST_METHOD(UnderTheLimitCreateChannelOp)
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

		TEST_METHOD(CreateOperatorOp)
		{
			CreateOper(CreateOperator);
			ProcessArgsValues(Plus);
			Assert::IsTrue(entity->GetContactValue(GetLastOper(), entity->operatorTypeColumn) == Plus);
		}

		TEST_METHOD(DeleteChannelOp)
		{
			//Same as create channel
			CreateOper(Plus);
			CreateOper(Plus);
			CreateOper(CreateChannel);

			const mainDataType fromOperator = Entity::FirstInternalOper + 3;
			const mainDataType toOperator = fromOperator + 1;
			const mainDataType toOperatorContactId = 1;

			ProcessArgsValues(fromOperator, toOperator, toOperatorContactId);
			Assert::IsTrue(GetValue(toOperator, toOperatorContactId) == fromOperator);
			//.

			CreateOper(DeleteChannel);
			ProcessArgsValues(toOperator, toOperatorContactId);
			Assert::IsFalse(GetValue(toOperator, toOperatorContactId) == fromOperator);
		}

		TEST_METHOD(GetTypeOfOperatorOp)
		{
			CreateOper(Plus);
			const mainDataType fromOperator = Entity::FirstInternalOper + 3;
			CreateOper(GetTypeOfOperator);
			const mainDataType toOperator = fromOperator + 1;
			const mainDataType toOperatorContactId = 1;
			entity->mCreateChannel(fromOperator, toOperator, toOperatorContactId);
			entity->mProcessLast();
			Assert::IsTrue(GetLastValue() == Plus);
		}

		TEST_METHOD(IsChannelExistsOp)
		{
			CreateOper(Plus);
			CreateOper(Plus);
			CreateOper(IsChannelExists);

			const mainDataType fromOperator = Entity::FirstInternalOper + 3;
			const mainDataType toOperator = fromOperator + 1;
			const mainDataType toOperatorContactId = 1;

			entity->mCreateChannel(fromOperator, toOperator, toOperatorContactId);
			ProcessArgsValues(fromOperator, toOperator, toOperatorContactId);
			Assert::IsTrue(GetLastValue() == 1);
			ProcessArgsValues(fromOperator - 1, toOperator, toOperatorContactId);
			Assert::IsTrue(GetLastValue() == 0);
		}

		TEST_METHOD(RemoveOperatorOp)
		{
			CreateOper(Plus);
			CreateOper(RemoveOperator);
			mainDataType plusOperId = GetLastOper() - 1;
			ProcessArgsValues(plusOperId);
			Assert::IsTrue(entity->GetContactValue(plusOperId, entity->operatorTypeColumn) == Nothing);
		}

		TEST_METHOD(GetInputOperatorIdOp)
		{
			CreateOper(Plus);
			CreateOper(GetInputOperatorId);
			mainDataType lastOper = GetLastOper();
			entity->mCreateChannel(lastOper - 1, lastOper, 1);
			entity->mProcessLast();
			Assert::IsTrue(GetLastValue() == lastOper - 1);
		}

		TEST_METHOD(GetOperatorContactsCountOp)
		{
			CreateOper(Plus);
			CreateOper(GetOperatorContactsCount);
			mainDataType plusOperId = GetLastOper() - 1;
			entity->mCreateChannel(plusOperId, GetLastOper(), 1);
			entity->mProcessLast();
			const mainDataType plusContactsCount = 2;
			Assert::IsTrue(GetLastValue() == plusContactsCount);
		}

		TEST_METHOD(NothingOp)
		{
			CreateOper(Nothing);
			ProcessArgsValues(1,2,3);
			Assert::IsTrue(GetLastValue() == 0);
		}
	};
}