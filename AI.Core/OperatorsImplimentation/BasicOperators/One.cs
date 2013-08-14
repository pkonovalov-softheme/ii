namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    class One : Operator
    {
        /// <summary>
        /// Always 1
        /// </summary>
        public One(Entity thisEntity)
            : base(thisEntity)
        {
            ExitContacts.SetValue(1);
        }

        public override void Action()
        {
            ExitContacts.SetValue(1);
        }
    }
}
