using System;

namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    public class RandomNumber : Operator
    {
        private readonly Random _rnd;

        public RandomNumber(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 1;
            _rnd = new Random();
        }

        public override void Action()
        {
            var value = (ulong)(_rnd.NextDouble() * EnterContacts[0].Value);
            ExitContacts.SetValue(value);
        }
    }
}
