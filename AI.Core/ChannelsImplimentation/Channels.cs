using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Runtime.InteropServices;

namespace AI.Core.ChannelsImplimentation
{
    public sealed class Channels : List<Channel>
    {
        public Channels(int capacity)
        {
            //this. = Enumerable.Repeat((Channel)null, capacity).ToList();
            for(int i = 0; i < capacity; i++)
                Add(null);
        }

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
                this[(int)index] = value;
            }
        }
    }
}
