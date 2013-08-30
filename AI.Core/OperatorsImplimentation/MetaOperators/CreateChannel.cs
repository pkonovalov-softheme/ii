using System;
using System.Linq;
using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    public class CreateChannel : ChannelOperator
    {
        /// <summary>
        /// Creates Channel between two Entities
        /// </summary>
        public CreateChannel(Entity thisEntity)
            : base(thisEntity) {}

        public override void Action()
        {
            Channel channel = null;
            try
            {
                ulong fromOpExitContactsCount = (ulong)FromOperator.ExitContacts.Count;

                //We will ignore requests when one of Contacts is used by other channel to require old channel be deleted before create new.
                if (ToOperator.EnterContacts[ToOperatorContactNumber] != null ||
                    FromOperator.ExitContacts[fromOpExitContactsCount] != null) return;

                var toContact = new Contact(ToOperator, ToOperatorContactNumber);
                var fromContact = new Contact(FromOperator, fromOpExitContactsCount);
                channel = new Channel(fromContact, toContact);
                FromOperator.ExitContacts.Add(channel);
                ToOperator.EnterContacts[ToOperatorContactNumber] = channel;
                ThisEntity.ChannelsTable.Add(new ChannelTableKey(FromOperator, ToOperator), channel);
            }
            catch (ArgumentOutOfRangeException)
            {
                if (FromOperator.ExitContacts.Last() == channel)
                    FromOperator.ExitContacts.RemoveAt(FromOperator.ExitContacts.Count);
            }
        }
    }
}
