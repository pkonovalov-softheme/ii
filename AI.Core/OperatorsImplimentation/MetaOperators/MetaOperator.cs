using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    public abstract class MetaOperator : Operator
    {
        protected MetaOperator(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 1;
        }
    }
}
