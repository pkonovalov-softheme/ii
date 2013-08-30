using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    /// <summary>
    /// Returns Id of operator from witch channel is enter. Value in channel is ignored.
    /// </summary>
    public class GetOperatorId : Operator
    {
        public GetOperatorId(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            ExitContacts.SetValue(EnterChannel.FromContact.Oper.Id);
        }

        private Channel EnterChannel
        {
            get { return EnterContacts[0]; }
        }
    }
}
