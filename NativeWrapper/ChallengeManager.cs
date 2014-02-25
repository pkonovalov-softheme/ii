using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using ManagedPlusPlusWrapper;

namespace NativeWrapper
{
    public enum ChallengeTypes
    {
        Division, Equal, If, Minus, Multiplication, One, Plus
    };

    [StructLayout(LayoutKind.Sequential)]
    public struct ChallengeManagerS
    {
        public readonly uint ChallangesCount;

        public readonly uint RandomUpperLimit;

        public readonly uint CurChallangeType; //returns IDs of the last used operator

        public readonly IntPtr Chmanager;
    }

    public unsafe class ChallengeManager
    {
        private readonly ChallengeManagerS _challengeManagerS;
        private readonly uint[,] _inputs = new uint[ChManagerConsts.ChallengesCount, BransGlobals.ExternalInputsCount];
        private readonly uint[,] _correctAnswers = new uint[ChManagerConsts.ChallengesCount, BransGlobals.ExternalInputsCount];
        public ChallengeManager(ChallengeManagerS chM, uint* inputsPtr, uint* correctAnswersPtr)
        {
            _challengeManagerS = chM;
            Utils.Fill2DArray(_inputs, inputsPtr);
            Utils.Fill2DArray(_correctAnswers, inputsPtr);
        }

        public double ChallangesCount
        {
            get { return _challengeManagerS.ChallangesCount; }
        }

        public double RandomUpperLimit
        {
            get { return _challengeManagerS.RandomUpperLimit; }
        }

        public ChallengeTypes CurChallengeType
        {
            get { return (ChallengeTypes)_challengeManagerS.CurChallangeType; }
        }

        public uint[,] Inputs
        {
            get { return _inputs; }
        }

        public uint[,] CorrectAnswers
        {
            get { return _correctAnswers; }
        }

        public override string ToString()
        {
            var sb = new StringBuilder();
            sb.AppendFormat("ChallangesCount: '{0}'", ChallangesCount);
            sb.AppendLine();
            sb.AppendFormat("RandomUpperLimit: '{0}'", RandomUpperLimit);
            sb.AppendLine();
            sb.AppendFormat("CurChallengeType: '{0}'", GetChallengeName(CurChallengeType));
            sb.AppendLine();

            for (int r = 0; r < ChallangesCount; r++)
            {
                sb.Append("Inputs: [");
                for (int c = 0; c < BransGlobals.ExternalInputsCount; c++)
                {
                    sb.AppendFormat("{0}, ", _inputs[r, c]);
                }
                sb.AppendLine("]");

                sb.Append("Correct: [");
                for (int c = 0; c < BransGlobals.ExternalOutputsCount; c++)
                {
                    sb.AppendFormat("{0}, ", _correctAnswers[r, c]);
                }
                sb.AppendLine("]");
            }


            return sb.ToString();
        }

        public void DumpManager()
        {
            System.IO.File.WriteAllText(@"C:\dump\manager.txt", this.ToString());
        }

        private static string GetChallengeName(ChallengeTypes chT)
        {
            return Enum.GetName(typeof(ChallengeTypes), chT);
        }

    }
}
