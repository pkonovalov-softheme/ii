using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    public class RemoveOperator : Operator
    {
        private ulong OperatorIdToRemove
        {
            get { return EnterContacts[0].Value; }
        }

        public RemoveOperator(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            ThisEntity.Operators.Remove(OperatorIdToRemove);
        }
    }
}
