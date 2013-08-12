using System;
using System.Collections.Generic;

namespace AI.Core.OperatorsImplimentation
{
    /// <summary>
    /// Operator object. Base object that connects virtual & real world.
    /// </summary>
    public abstract class Operator
    {
        public Operators Entity { get; protected set; }
        public ulong Id { get; protected set; }
        public Channels ExitContacts; //To do: Add safe thread logic for external setter
        public Channels EnterContacts; //To do: Add safe thread logic for external setter
        protected ushort EnterContactsCount;

        public abstract void Action();

        /// <summary>
        /// Initialize new Operator
        /// </summary>
        /// <param name="id">Unique number for Operator identification</param>
        /// <param name="opers">Operators collection of the Entity</param>
        protected Operator(ulong id, Operators opers)
        {
            Id = id;
            Entity = opers;
            ExitContacts = new Channels(1);
            EnterContacts = new Channels(EnterContactsCount);
        }
    }
}
