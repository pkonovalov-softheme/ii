﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using ManagedPlusPlusWrapper;


namespace NativeWrapper
{

    [StructLayout(LayoutKind.Sequential)]
    public struct EntityS
    {
        public readonly double Effectiveness;

        public readonly uint CorrectAnswersCount;

        public readonly uint NextOperatorId; //returns IDs of the last used operator

        public readonly IntPtr Chmanager;
    }

    public unsafe class Entity
    {
        private readonly EntityS _entS;

        private readonly uint[,] _operators = new uint[BransGlobals.OperatorsCount, EntityConsts.operatorsTableWidth];

        public Entity(EntityS entS, uint* opersPtr)
        {
            
            _entS = entS;
            InitOperatorsArray(opersPtr);
        }

        public double Effectiveness
        {
            get { return _entS.Effectiveness; }
        }

        public uint CorrectAnswersCount
        {
            get { return _entS.CorrectAnswersCount; }
        }

        public uint NextOperatorId
        {
            get { return _entS.NextOperatorId; }
        }

        public IntPtr Chmanager
        {
            get { return _entS.Chmanager; }
        }

        private void InitOperatorsArray(uint* opersPtr)
        {
            for (int i1 = 0; i1 < 60; i1++)
            {
                for (int i2 = 0; i2 < 5; i2++)
                {
                    _operators[i1, i2] = *opersPtr;
                    opersPtr++;
                }
            }
        }
    }
   
}
