using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation
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
