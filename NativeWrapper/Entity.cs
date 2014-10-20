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
    public enum OperatorsTypes
    {
        /*Zero is restricted system value. After the first zero operator _operators array processing will be stopped. 
        Value of the zero operator is assuming as zero-only.
        Basic operators:*/
        Zero, If, Multipl, One, Plus, ExternalInput, ExternalOutput, Nothing
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct EntityS
    {
        public readonly double Effectiveness;

        public readonly uint IncorrectAnswersCount;

        public readonly uint CorrectAnswersCount;

        public readonly uint NextOperatorId; //returns IDs of the last used operator

        public readonly IntPtr Chmanager;
    }

    public unsafe class Entity
    {
        private const double TargetEf = 0.99;
        private readonly EntityS _entS;

        private readonly uint[,] _operators = new uint[BransGlobals.operatorsMaxCount, EntityConsts.operatorsTableWidth];

       // private readonly ChallengeManager _chMng;

        public Entity(EntityS entS, uint* opersPtr)
        {
            _entS = entS;
            Utils.Fill2DArray(_operators, opersPtr);

            // Works +- but not needed
           // uint* ptrOnInputs = NativeLibPrototypes.GetInputsPtr(Chmanager); 
           // uint* ptrOnCorrectAnswers = NativeLibPrototypes.GetCorrectAnswersPtr(Chmanager);
            //var chmanagerS = (ChallengeManagerS)Marshal.PtrToStructure(Chmanager, typeof(ChallengeManagerS));
            //_chMng = new ChallengeManager(chmanagerS, ptrOnInputs, ptrOnCorrectAnswers);

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

        public static Entity GenerateEntity()
        {
            IntPtr ptrOnEntity = NativeLibPrototypes.AchiveEffectivity(TargetEf);

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

            for(int r = 0; r < NextOperatorId; r++)
            {
                sb.AppendFormat("Id = {5}; [OpType = {0}({6}), Fcnt = {1}, Scnt = {2}, Tcnt = {3}, OutVal = {4}]",
                _operators[r, 0], 
                _operators[r, 1],
                _operators[r, 2], 
                _operators[r, 3], 
                _operators[r, 4], 
                r, 
                GetOperName((OperatorsTypes)_operators[r, EntityConsts.operatorTypeColumn]));
                sb.AppendLine();
            }

           
            return sb.ToString();
        }

        public void DumpEntity()
        {
            const string dir = @"C:\dump\";
            Directory.CreateDirectory(dir);
            File.WriteAllText(dir + "entity.txt", this.ToString());
        }

        public static string GetOperName(OperatorsTypes op)
        {
            return Enum.GetName(typeof(OperatorsTypes), op);
        }
    }
   
}
