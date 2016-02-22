using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi
{
    internal static class Utils
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern void Print(string msg);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal static extern string GetString();
    }

    internal sealed class Program
    {
        private static void Main(string[] args)
        {
            foreach (var arg in args) Utils.Print(arg);

            Console.WriteLine(Utils.GetString());
        }
    }
}
