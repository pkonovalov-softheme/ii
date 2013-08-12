using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation
{
    class One : Operator
    {
        /// <summary>
        /// Always 1
        /// </summary>
        public One(ulong id, Operators opers)
            : base(id, opers)
        {
            ExitContacts.SetValue(1);
        }

        public override void Action()
        {
            ExitContacts.SetValue(1);
        }
    }
}
