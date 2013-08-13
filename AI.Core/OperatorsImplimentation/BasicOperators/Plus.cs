namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class Plus : Operator
    {
        public Plus(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 2;
        }

        public override void Action()
        {
            var value = EnterContacts[0].Value + EnterContacts[1].Value;
            ExitContacts.SetValue(value);
        }
    }
}
