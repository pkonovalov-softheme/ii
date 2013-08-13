using System;
using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    class CreateChannel : ChannelOperator
    {
        /// <summary>
        /// Creates Channel between two Entities
        /// </summary>
        public CreateChannel(ulong id, Entity entity) : base(id, entity) {}

        public override void Action()
        {
            try
            {
                //We will ignore requests when one of Contacts is used by other channel to require old channel be deleted before create new.
                if (ToOperator.EnterContacts[ToOperatorContactNumber] == null ||
                    FromOperator.ExitContacts[FromOperator.ExitContacts.Count] == null) return;

                var toContact = new Contact(ToOperator, ToOperatorContactNumber);
                var fromContact = new Contact(FromOperator, ToOperatorContactNumber);
                var channel = new Channel(fromContact, toContact);
                FromOperator.ExitContacts.Add(channel);
                ToOperator.EnterContacts[ToOperatorContactNumber] = channel;
                Entity.ChannelsTable.Add(new ChannelTableKey(FromOperator, ToOperator), channel);
            }
            catch (ArgumentOutOfRangeException) {}
        }
    }
}
