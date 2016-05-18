using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Engine
{
    public static class RuntimeHelpers
    {
        [MethodImpl(MethodImplOptions.NoInlining)]
        public static string ThisFileName()
        {
            var sf = new StackTrace(true).GetFrame(0);

            return sf.GetFileName();
        }

        [MethodImpl(MethodImplOptions.NoInlining)]
        public static string ThisFunctionName()
        {
            var sf = new StackTrace(true).GetFrame(0);

            return sf.GetMethod().Name;
        }

        [MethodImpl(MethodImplOptions.NoInlining)]
        public static int ThisLinenumber()
        {
            var sf = new StackTrace(true).GetFrame(0);

            return sf.GetFileLineNumber();
        }
    }
}
