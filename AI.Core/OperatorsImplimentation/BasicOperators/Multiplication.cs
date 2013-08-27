using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    public class Multiplication : Operator
    {
        public Multiplication(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 2;
        }

        public override void Action()
        {
            var value = EnterContacts[0].Value * EnterContacts[1].Value;
            ExitContacts.SetValue(value);
        }
    }
}
