using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation
{
    class If : Operator
    {
        public If(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 3;
        }

        public override void Action()
        {
            var currentValue = EnterContacts[0].Value;
            var downLimit = EnterContacts[1].Value;
            var upperLimit = EnterContacts[2].Value;
            if (currentValue >= downLimit && currentValue < upperLimit)
            {
                ExitContacts.SetValue(1);
            }
            else
            {
                ExitContacts.SetValue(0);
            }
        }
    }
}
