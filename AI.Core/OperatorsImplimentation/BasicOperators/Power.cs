using System;

namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class Power : Operator
    {
        public Power(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 2;
        }

        public override void Action()
        {
            var value = Convert.ToUInt64(Math.Pow(EnterContacts[0].Value, EnterContacts[1].Value));
            ExitContacts.SetValue(value);
        }
    }
}
