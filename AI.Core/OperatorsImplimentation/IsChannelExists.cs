using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core.OperatorsImplimentation
{
    class IsChannelExists : ChannelOperator
    {
        /// <summary>
        /// Returns "1" if channel between two Entities(with respect to contact number) exists and "0" if not.
        /// </summary>
        public IsChannelExists(ulong id, Operators opers) : base(id, opers) {}

        public override void Action()
        {
            try
            {
                if (Entity[FromEntity].ExitContacts == Entity[ToEntity].EnterContacts[ToEntityContactNumber])
                {
                    ExitContacts.SetValue(1);
                    return;
                }
            }
            catch (ArgumentOutOfRangeException) { }
            ExitContacts.SetValue(0);
        }
    }
}
