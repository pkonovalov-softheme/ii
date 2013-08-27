using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using AI.Core.ChannelsImplimentation;
using AI.Core.OperatorsImplimentation;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using AI.Core;
using AI.Core.OperatorsImplimentation.BasicOperators;
using Moq;

namespace AI.UnitTests
{
    [TestClass]
    public class BasicOperatorsTests
    {
        private static Entity _entity;
        private static Operator _oper;

        [ClassInitialize]
        public static void SetUp(TestContext context)
        {
            _entity = new Entity();
        }

        [TestMethod]
        public void TestDivision1()
        {
            _oper = new Division(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(8);
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(4);
            _oper.ExitContacts[0]  = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 2);
        }

        [TestMethod]
        public void TestDivision2()
        {
            _oper = new Division(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(4);
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(4);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 1);
        }

        [TestMethod]
        public void TestDivision3()
        {
            _oper = new Division(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(4);
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(8);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 0);
        }

        [TestMethod]
        public void TestEqual()
        {
            const ushort inputVal = 4;
            _oper = new Equal(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(inputVal);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == inputVal);
        }

        [TestMethod]
        public void TestIf_Below()
        {
            _oper = new If(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(8); //currentValue
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(10); //downLimit
            _oper.EnterContacts[2] = TestHelper.CreateNewChannel(15); //upperLimit
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 0);
        }

        [TestMethod]
        public void TestIf_In()
        {
            _oper = new If(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(10); //currentValue
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(10); //downLimit
            _oper.EnterContacts[2] = TestHelper.CreateNewChannel(15); //upperLimit
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 1);
        }

        [TestMethod]
        public void TestIf_Out()
        {
            _oper = new If(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(15); //currentValue
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(10); //downLimit
            _oper.EnterContacts[2] = TestHelper.CreateNewChannel(15); //upperLimit
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 0);
        }

        [TestMethod]
        public void TestMinus()
        {
            _oper = new Minus(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(15); 
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(10); 
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 5);
        }

        [TestMethod]
        public void TestMultiplication()
        {
            _oper = new Multiplication(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(2);
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(3);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 6);
        }

        [TestMethod]
        public void TestOne()
        {
            _oper = new One(_entity);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 1);
        }

        [TestMethod]
        public void TestPlus()
        {
            _oper = new Plus(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(2);
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(3);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 5);
        }

        [TestMethod]
        public void TestPower()
        {
            _oper = new Power(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(2);
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(3);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 8);
        }

        [TestMethod]
        public void RandomNumber()
        {
            const uint limit = 100; 
            var results = new List<ulong>();
            _oper = new RandomNumber(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(limit);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            for (int i = 0; i < 1000; i++)
            {
                _oper.Action();
                var res = _oper.ExitContacts[0].Value;
                if (res >= limit) {Assert.Fail("Under the limit!");}
                results.Add(res);
            }

            ulong sum = 0;
            foreach (var res in results)
            {
                sum += res;
            }

            double mid = (double)sum/results.Count;
            Assert.IsTrue((mid > limit * 0.4d) && (mid < limit * 0.6d), "Arithmetic mean was:" + mid);
        }

        [TestMethod]
        public void TestTime()
        {
            _oper = new Time(_entity);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            TimeSpan ts = TimeSpan.FromTicks((long)_oper.ExitContacts[0].Value);
            Assert.IsTrue(ts.Seconds == DateTime.Now.Second);
        }
    }
}
