using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AI.Core.OperatorsImplimentation;

namespace AI.Core
{
    /// <summary>
    /// Represent contact on the base of operator and contact order number
    /// </summary>
    public struct Contact
    {
        private readonly Operator _oper;
        private readonly ulong _contactNumber;
        public Contact(Operator oper, ulong contactNumber)
        {
           _oper = oper;
           _contactNumber = contactNumber;
        }

        public ulong ContactNumber
        {
            get { return _contactNumber; }
        }

        public Operator Oper
        {
            get { return _oper; }
        }
    }
}
