namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    /// <summary>
    /// Base for the "meta-operators" that are managing Channels and Operators. 
    /// </summary>
    public abstract class ChannelOperator : Operator
    {
        protected ulong FromOperatorId
        {
            get { return EnterContacts[0].Value; }
            set { EnterContacts[0].Value = value; }
        }

        protected Operator FromOperator
        {
            get { return Entity.Operators[FromOperatorId]; }
            set { FromOperatorId = value.Id; }
        }

        protected ulong ToOperatorId
        {
            get { return EnterContacts[1].Value; }
            set { EnterContacts[1].Value = value; }
        }

        protected Operator ToOperator
        {
            get { return Entity.Operators[ToOperatorId]; }
            set { ToOperatorId = value.Id; }
        }

        protected ulong ToOperatorContactNumber
        {
            get { return EnterContacts[2].Value; }
            set { EnterContacts[2].Value = value; }
        }

        protected ChannelOperator(ulong id, Entity entity)
            : base(id, entity)
        {
            EnterContactsCount = 3;
        }
    }
}
