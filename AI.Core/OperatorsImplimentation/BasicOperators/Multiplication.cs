namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class Multiplication : Operator
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
