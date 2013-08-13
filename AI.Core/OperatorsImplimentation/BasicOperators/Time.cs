using System;

namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class Time : Operator
    {
        /// <summary>
        /// Returns UTC ticks
        /// </summary>
        public Time(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 0;
        }

        public override void Action()
        {
            ExitContacts.SetValue((ulong)DateTime.UtcNow.Ticks); 
        }
    }
}
