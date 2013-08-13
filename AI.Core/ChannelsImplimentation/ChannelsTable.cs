using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AI.Core.OperatorsImplimentation;

namespace AI.Core.ChannelsImplimentation
{
    public struct ChannelTableKey
    {
      public readonly Operator FromOperator;
      public readonly Operator ToOperator;
      public ChannelTableKey(Operator fromOperator, Operator toOperator)
      {
        FromOperator = fromOperator;
        ToOperator = toOperator;
      }
    }

    public class ChannelsTable : Dictionary<ChannelTableKey, Channel> { }
}
