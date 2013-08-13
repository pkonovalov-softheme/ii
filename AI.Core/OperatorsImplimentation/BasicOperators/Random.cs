using System;

namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class RandomNumber : Operator
    {
        public RandomNumber(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            var rnd = new Random();
            var value = (ulong)(rnd.NextDouble() * ulong.MaxValue);
            ExitContacts.SetValue(value);
        }
    }
}
