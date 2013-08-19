using System.Collections.Generic;

namespace AI.Core.ChannelsImplimentation
{
    public sealed class Channels : List<Channel>
    {
        public Channels(int capacity) : base(capacity) 
        {
            for (int i = 0; i < capacity; i++)
                this.Add(null);
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
                this[(int) index] = value;
            }
        }
    }
}
