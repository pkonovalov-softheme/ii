using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NativeWrapper
{
    internal static unsafe class Utils
    {
        public static uint[,] Fill2DArray(uint[,] array, uint* ptr)
        {
            for (int i1 = 0; i1 < array.GetLength(0); i1++)
            {
                for (int i2 = 0; i2 < array.GetLength(1); i2++)
                {
                    array[i1, i2] = *ptr;
                    ptr++;
                }
            }

            return array;
        }
    }
}
