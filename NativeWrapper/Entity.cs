using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using ManagedPlusPlusWrapper;
using System.IO;
using System.Runtime.Serialization.Formatters.Soap;


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

        private readonly uint[,] _operators = new uint[BransGlobals.operatorsMaxCount, EntityConsts.operatorsTableWidth];

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

        public uint[,] Operators
        {
            get { return _operators; }
        }

        private void InitOperatorsArray(uint* opersPtr)
        {
            for (int i1 = 0; i1 < BransGlobals.operatorsMaxCount; i1++)
            {
                for (int i2 = 0; i2 < EntityConsts.operatorsTableWidth; i2++)
                {
                    _operators[i1, i2] = *opersPtr;
                    opersPtr++;
                }
            }
        }

        public static Entity GenerateEntity()
        {
            IntPtr ptrOnEntity = NativeLibPrototypes.AchiveEffectivity();
            var goodEntityS = (EntityS)Marshal.PtrToStructure(ptrOnEntity, typeof(EntityS));

            unsafe
            {
                uint* ptrOnOpers = NativeLibPrototypes.GetOperatorsPtr(ptrOnEntity);
                return new Entity(goodEntityS, ptrOnOpers);
            }
        }

        public override string ToString()
        {
            var sb = new StringBuilder();
            sb.AppendFormat("CorrectAnswersCount: '{0}'", CorrectAnswersCount);
            sb.AppendLine();
            sb.AppendFormat("Effectiveness: '{0}'", Effectiveness);
            sb.AppendLine();
            sb.AppendFormat("NextOperatorId: '{0}'", NextOperatorId);
            sb.AppendLine();
            sb.AppendLine("Operators: ");

            for(int r = 0; r < BransGlobals.operatorsMaxCount; r++)
            {
                sb.AppendFormat("[Id = {0}, Fcnt = {1}, Scnt = {2}, Tcnt = {3}, OutVal = {4}]",
                    _operators[r, 0], _operators[r, 1], _operators[r, 2], _operators[r, 3], _operators[r, 4]);
                sb.AppendLine();
            }

            return sb.ToString();
        }

        public void DumpEntity()
        {
            System.IO.File.WriteAllText(@"C:\dump\entity.txt", this.ToString());
        }
    }
   
}
