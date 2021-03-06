﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AI.Core.ChannelsImplimentation;
using AI.Core.OperatorsImplimentation;

namespace AI.Core
{
    /// <summary>
    /// 
    /// </summary>
    public class Entity
    {
        private readonly ChannelsTable _channelsTable;
        private readonly Operators _operators;

        public Entity()
        {
            _operators = new Operators();
            _channelsTable = new ChannelsTable();
        }

        public ChannelsTable ChannelsTable
        {
            get { return _channelsTable; }
        }

        public Operators Operators
        {
            get { return _operators; }
        }
    }
}
