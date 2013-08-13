using System;
using System.Collections.Generic;
using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    class DeleteChannel : ChannelOperator
    {
        /// <summary>
        /// Delete Channel
        /// </summary>
        public DeleteChannel(ulong id, Entity entity) : base(id, entity) {}

        public override void Action()
        {
            try
            {
                Channel channel;
                var chktey = new ChannelTableKey(FromOperator, ToOperator);
                try
                {
                    channel = Entity.ChannelsTable[chktey];
                }
                catch (KeyNotFoundException) {return;}

                FromOperator.ExitContacts[channel.FromContact.ContactNumber] = null;
                ToOperator.EnterContacts[channel.ToContact.ContactNumber] = null;
                Entity.ChannelsTable[chktey] = null;
            }
            catch (ArgumentOutOfRangeException){}
        }
    }
}
