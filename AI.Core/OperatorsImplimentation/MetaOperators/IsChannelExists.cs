using System;
using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    class IsChannelExists : ChannelOperator
    {
        /// <summary>
        /// Returns "1" if channel between two Entities(with respect to contact number) exists and "0" if not.
        /// </summary>
        public IsChannelExists(Entity thisEntity)
            : base(thisEntity){}

        public override void Action()
        {
            bool result = ThisEntity.ChannelsTable.ContainsKey(new ChannelTableKey(FromOperator, ToOperator));
            ExitContacts.SetValue(Convert.ToUInt64(result));
        }
    }
}
