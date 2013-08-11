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
        /// <summary>
        /// Current number of quantum's in channel. There is a question about uint type. We should see on memory usage and change it if that will be useful.
        /// </summary>
        public ulong Value;
    }
}
