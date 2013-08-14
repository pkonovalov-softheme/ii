namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class If : Operator
    {
        public If(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 3;
        }

        public override void Action()
        {
            var currentValue = EnterContacts[0].Value;
            var downLimit = EnterContacts[1].Value;
            var upperLimit = EnterContacts[2].Value;
            if (currentValue >= downLimit && currentValue < upperLimit)
            {
                ExitContacts.SetValue(1);
            }
            else
            {
                ExitContacts.SetValue(0);
            }
        }
    }
}
