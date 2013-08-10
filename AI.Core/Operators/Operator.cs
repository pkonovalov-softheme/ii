using System;
using System.Collections.Generic;

namespace AI.Core.Operators
{
    /// <summary>
    /// Operator object. Base object that connects virtual & real world.
    /// </summary>
    public abstract class Operator
    {
        public ExitContact ExitContact { get; protected set; }
        public List<EnterContact> EnterContacts { get; protected set; }

        protected Operator() 
        {
            ExitContact = new ExitContact();
        }

        public abstract void Action();
    }
}
