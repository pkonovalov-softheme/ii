using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Runtime.InteropServices;

namespace AI.Core.ChannelsImplimentation
{
    public sealed class Channels
    {
        private readonly List<Channel> _rawChannels;

        public Channels(int capacity)
        {
            _rawChannels = Enumerable.Repeat((Channel)null, capacity).ToList();
        }

        /// <summary>
        /// Setting up values for all channels
        /// </summary>
        public void SetValue(ulong value)
        {
            foreach (Channel currentChannel in _rawChannels)
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
                return _rawChannels[(int)index];
            }
            set
            {
                _rawChannels[(int)index] = value;
            }
        }

        public ulong Count
        {
            get
            {
                return (ulong)_rawChannels.Count;
            }
        }

        public void Add(Channel channel)
        {
            _rawChannels.Add(channel);
        }
    }
}
