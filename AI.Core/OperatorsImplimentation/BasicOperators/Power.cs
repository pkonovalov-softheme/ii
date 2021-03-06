﻿using System;
using AI.Core.ChannelsImplimentation;

namespace AI.Core.OperatorsImplimentation.BasicOperators
{
    public class Power : Operator
    {
        public Power(Entity thisEntity)
            : base(thisEntity)
        {
            EnterContactsCount = 2;
        }

        public override void Action()
        {
            var value = Convert.ToUInt64(Math.Pow(EnterContacts[0].Value, EnterContacts[1].Value));
            ExitContacts.SetValue(value);
        }
    }
}
