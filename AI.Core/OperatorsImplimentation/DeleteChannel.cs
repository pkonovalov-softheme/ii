using System;

namespace AI.Core.OperatorsImplimentation
{
    class DeleteChannel : ChannelOperator
    {
        /// <summary>
        /// Delete Channel
        /// </summary>
        public DeleteChannel(ulong id, Operators opers) : base(id, opers) {}

        public override void Action()
        {
            try
            {
                //We will delete only ii is the same channel for Enter and Exit
                if (Entity[ToEntity].EnterContacts[ToEntityContactNumber] == Entity[FromEntity].ExitContacts)
                {
                    Entity[FromEntity].ExitContacts = null;
                    Entity[ToEntity].EnterContacts[ToEntityContactNumber] = null;
                }
            }
            catch (ArgumentOutOfRangeException){}
        }
    }
}
