using System;
using System.Collections.Generic;
using AI.Core.ChannelsImplimentation;
using AI.Core.OperatorsImplimentation.BasicOperators;

namespace AI.Core.OperatorsImplimentation
{
    /// <summary>
    /// Operator object. Base object that connects virtual & real world.
    /// </summary>
    public abstract class Operator
    {
        protected enum OperatorsTypes
        {
            Division, Equal, If, Minus, Multiplication, One, Plus, Power, RandomNumber, Time, CreateChannel, CreateOperator, DeleteChannel, GetTypeOfOperator,
            IsChannelExists,  RemoveOperator
        };
        protected Entity ThisEntity { get; private set; }
        public ulong Id { get; protected set; }
        public ulong OperatorType { get; protected set; }
        public Channels ExitContacts; //To do: Add safe thread logic for external setter
        public Channels EnterContacts; //To do: Add safe thread logic for external setter
        protected ushort EnterContactsCount;

        public abstract void Action();

        /// <summary>
        /// Initialize new Operator
        /// </summary>
        /// <param name="thisEntity">Operators collection of the Entity</param>
        protected Operator(Entity thisEntity)
        {
            Id = ThisEntity.Operators.GetNewUniqueId();
            ThisEntity = thisEntity;
            ExitContacts = new Channels(1);
            EnterContacts = new Channels(EnterContactsCount);
        }
    }
}
