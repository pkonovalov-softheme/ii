using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    public class One : Operator
    {
        /// <summary>
        /// Always 1
        /// </summary>
        public One(Entity thisEntity)
            : base(thisEntity)
        {}

        public override void Action()
        {
            ExitContacts.SetValue(1);
        }
    }
}
