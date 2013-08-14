using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AI.Core.OperatorsImplimentation.BasicOperators;

namespace AI.Core.OperatorsImplimentation.MetaOperators
{
    public class CreateOperator : Operator
    {
        /// <summary>
        /// Create new operator of specified type and returns ID of new created operator. 
        /// </summary>
        /// <param name="thisEntity"></param>
        public CreateOperator(Entity thisEntity) 
            : base(thisEntity)
        {
            EnterContactsCount = 1;
        }

        public override void Action()
        {
            Operator oper = CreateOperatorInternal();
            ThisEntity.Operators.Add(oper.Id, CreateOperatorInternal());
            ExitContacts.SetValue(oper.Id);
        }

        private ulong OperatorTypeToAdd
        {
            get { return EnterContacts[0].Value; }
        }

        //We don't using Activator because of it's bad performance. http://rogeralsing.com/2008/02/28/linq-expressions-creating-objects is better but still 2x slower than 'new'.
        private Operator CreateOperatorInternal()
        {
            switch ((OperatorsTypes)OperatorTypeToAdd)
            {
                case (OperatorsTypes.Division):
                    return new Division(ThisEntity);
                case (OperatorsTypes.Equal):
                    return new Equal(ThisEntity);
                case (OperatorsTypes.Minus):
                    return new Minus(ThisEntity);
                case (OperatorsTypes.Multiplication):
                    return new Multiplication(ThisEntity);
                case (OperatorsTypes.One):
                    return new One(ThisEntity);
                case (OperatorsTypes.Plus):
                    return new Plus(ThisEntity);
                case (OperatorsTypes.Power):
                    return new Power(ThisEntity);
                case (OperatorsTypes.RandomNumber):
                    return new RandomNumber(ThisEntity);
                case (OperatorsTypes.Time):
                    return new Time(ThisEntity);
                case (OperatorsTypes.CreateChannel):
                    return new CreateChannel(ThisEntity);
                case (OperatorsTypes.CreateOperator):
                    return new CreateOperator(ThisEntity);
                case (OperatorsTypes.DeleteChannel):
                    return new DeleteChannel(ThisEntity);
                case (OperatorsTypes.GetTypeOfOperator):
                    return new GetTypeOfOperator(ThisEntity);
                case (OperatorsTypes.IsChannelExists):
                    return new IsChannelExists(ThisEntity);
                case (OperatorsTypes.RemoveOperator):
                    return new RemoveOperator(ThisEntity);
            }
        }
    }
}
