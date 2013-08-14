namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class Equal : Operator
    {
        /// <summary>
        /// Just repeats Enter on exit
        /// </summary>
        public Equal(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            ExitContacts.SetValue(EnterContacts[0].Value);
        }
    }
}
