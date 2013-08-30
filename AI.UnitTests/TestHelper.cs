using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AI.Core;
using AI.Core.ChannelsImplimentation;

namespace AI.UnitTests
{
    public static class TestHelper
    {
        public static Channel CreateNewChannel()
        {
           return new Channel(new Contact(), new Contact());
        }

        public static Channel CreateNewChannel(ulong channelValue)
        {
            return new Channel(new Contact(), new Contact()) { Value = channelValue };
        }
    }
}
