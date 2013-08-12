using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core
{
    public sealed class Channels : List<Channel>
    {
        public Channels(int capacity) : base(capacity) {}
        
        /// <summary>
        /// Setting up values for all channels
        /// </summary>
        public void SetValue(ulong value)
        {
            foreach (Channel currentChannel in this)
            {
                currentChannel.Value = value;
            }
        }

        /// <summary>
        /// Index with ulong instead of int
        /// </summary>
        public Channel this[ulong index]
        {
            get
            {
                return this[(int)index];
            }
            set
            {
                this[(int) index] = value;
            }
        }
    }
}
