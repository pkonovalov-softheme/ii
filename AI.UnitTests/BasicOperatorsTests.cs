using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using AI.Core;
using AI.Core.OperatorsImplimentation.BasicOperators;

namespace AI.UnitTests
{
    [TestClass]
    public class BasicOperatorsTests
    {
        [TestMethod]
        public void TestMethod1()
        {
            var entity = new Entity();
            var dev = new Division(entity);
            dev.EnterContacts.Add(8);
            dev.EnterContacts[1].Value = 4;
            dev.Action();
            Assert.IsTrue(dev.ExitContacts.TrueForAll(x=>x.Equals(2)));
        }
        
    }
}
