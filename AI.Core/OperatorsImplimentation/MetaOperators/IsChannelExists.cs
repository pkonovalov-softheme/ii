using System;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    class IsChannelExists : ChannelOperator
    {
        /// <summary>
        /// Returns "1" if channel between two Entities(with respect to contact number) exists and "0" if not.
        /// </summary>
        public IsChannelExists(ulong id, Operators opers) : base(id, opers) {}

        public override void Action()
        {
            try
            {
                if (Entity[FromOperatorId].ExitContacts == Entity[ToOperatorId].EnterContacts[ToEntityContactNumber])
                {
                    ExitContacts.SetValue(1);
                    return;
                }
            }
            catch (ArgumentOutOfRangeException) { }
            ExitContacts.SetValue(0);
        }
    }
}
