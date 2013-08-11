using System;
using System.Collections.Generic;

namespace AI.Core.Operators
{
    /// <summary>
    /// Operator object. Base object that connects virtual & real world.
    /// </summary>
    public abstract class Operator
    {
        public Channel ExitContact { get; protected set; }
        public List<Channel> EnterContacts { get; protected set; }
        protected ushort EnterContactsCount;

        protected Operator() 
        {
            ExitContact = new Channel();
            EnterContacts = new List<Channel>(EnterContactsCount);
        }

        public abstract void Action();
    }
}
