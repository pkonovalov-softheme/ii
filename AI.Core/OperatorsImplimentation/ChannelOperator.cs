using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace AI.Core.OperatorsImplimentation
{
    /// <summary>
    /// Base for the "meta-operators" that are managing Channels and Operators. 
    /// </summary>
    public abstract class ChannelOperator : Operator
    {
        protected ulong FromEntity
        {
            get { return EnterContacts[0].Value; }
            set { EnterContacts[0].Value = value; }
        }

        protected ulong ToEntity
        {
            get { return EnterContacts[1].Value; }
            set { EnterContacts[1].Value = value; }
        }

        protected int ToEntityContactNumber 
        {
            //int because list index is int type. Some lose of precision but it is fine because really we are using ushort for contact count number
            get { return (int)EnterContacts[2].Value; }
            set { EnterContacts[2].Value = (ulong)value; }
        }

        protected ChannelOperator(ulong id, Operators opers)
            : base(id, opers)
        {
            EnterContactsCount = 3;
        }
    }
}
