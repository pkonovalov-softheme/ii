namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class Equal : Operator
    {
        /// <summary>
        /// Just repeats Enter on exit
        /// </summary>
        public Equal(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            ExitContacts.SetValue(EnterContacts[0].Value);
        }
    }
}
