using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation
{
    class Equal : Operator
    {
        /// <summary>
        /// Just repeats Enter on exit
        /// </summary>
        public Equal(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            ExitContacts.SetValue(EnterContacts[0].Value);
        }
    }
}
