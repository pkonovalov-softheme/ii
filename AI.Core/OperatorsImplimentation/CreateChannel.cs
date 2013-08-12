using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation
{
    class CreateChannel : ChannelOperator
    {
        /// <summary>
        /// Creates Channel between two Entities
        /// </summary>
        public CreateChannel(ulong id, Operators opers) : base(id, opers) {}

        public override void Action()
        {
            var channel = new Channel();
            try
            {
                Entity[FromEntity].ExitContacts = channel;
                Entity[ToEntity].EnterContacts[ToEntityContactNumber] = channel;
            }
            catch (ArgumentOutOfRangeException) {}
        }
    }
}
