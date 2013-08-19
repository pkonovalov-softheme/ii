using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    class GetOperatorContactsCount : ChannelOperator
    {
        public GetOperatorContactsCount(Entity thisEntity) 
            : base(thisEntity)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            ExitContacts.SetValue(ThisEntity.Operators[TargetOperatorId].OperatorType);
        }

        private ulong TargetOperatorId
        {
            get { return EnterContacts[0].Value; }
        }
    }
}
