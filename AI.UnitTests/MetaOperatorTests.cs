using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AI.Core;
using AI.Core.OperatorsImplimentation;
using AI.Core.OperatorsImplimentation.MetaOperators;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace AI.UnitTests
{
    public class MetaOperatorTests
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
            _oper = new CreateChannel(_entity);
            _oper.EnterContacts[0] = TestHelper.CreateNewChannel(8);
            _oper.EnterContacts[1] = TestHelper.CreateNewChannel(4);
            _oper.ExitContacts[0] = TestHelper.CreateNewChannel();
            _oper.Action();
            Assert.IsTrue(_oper.ExitContacts[0].Value == 2);
        }
    }
}
