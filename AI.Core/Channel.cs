using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AI.Core
{
    /// <summary>
    /// Channel object
    /// </summary>
    public sealed class Channel
    {
        public Channel(ExitContact start, EnterContact end)
        {
            Start = start;
            End = end;
        }

        /// <summary>
        /// Start of the Channel. It has no sense to change Start or End they can be only selected at start. 
        /// </summary>
        public ExitContact Start { get; private set; }

        /// <summary>
        /// End of the Channel.
        /// </summary>
        public EnterContact End { get; private set; }

        /// <summary>
        /// Current number of quantum's in channel. There is a question about uint type. We should see on memory usage and change it if that will be useful.
        /// </summary>
        public uint Value;
    }
}
