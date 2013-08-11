using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.Operators
{
    class Plus : Operator
    {
        public Plus()
        {
            EnterContactsCount = 2;
        }

        public override void Action()
        {
            ExitContact.Value = EnterContacts[0].Value + EnterContacts[1].Value;
        }
    }
}
