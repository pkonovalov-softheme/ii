using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation
{
    class Plus : Operator
    {
        public Plus(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 2;
        }

        public override void Action()
        {
            var value = EnterContacts[0].Value + EnterContacts[1].Value;
            ExitContacts.SetValue(value);
        }
    }
}
