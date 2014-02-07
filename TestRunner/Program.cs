using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using NativeWrapper;

namespace TestRunner
{
    static class Program
    {
        static void Main(string[] args)
        {
            IntPtr ptrOnEntity = NativeLibPrototypes.AchiveEffectivity();
            var goodEntityS = (EntityS)Marshal.PtrToStructure(ptrOnEntity, typeof(EntityS));

            unsafe
            {
                uint* ptrOnOpers = NativeLibPrototypes.GetOperatorsPtr(ptrOnEntity);
                var goodEntity = new Entity(goodEntityS, ptrOnOpers);
            }


            //var ret = new int[60,5];
            //unsafe
            //{
            //    int* ptrOnArray = NativeLibPrototypes.GetOpers();
            //    for (int i1 = 0; i1 < 60; i1++)
            //    {
            //        for (int i2 = 0; i2 < 5; i2++)
            //        {
            //            ret[i1, i2] = *ptrOnArray;
            //            ptrOnArray++;
            //        }
            //    }

            //}

            //SimpleObj ob = new SimpleObj();
            //var ptrOnSimple = NativeLibPrototypes.GetSimple();
            //SimpleObj personRes = (SimpleObj)Marshal.PtrToStructure(ptrOnSimple, typeof(SimpleObj));
        }
    }
}
