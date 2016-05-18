using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Engine
{
    public static class Log
    {
        //[MethodImpl(MethodImplOptions.InternalCall)]
        //public static extern void LogRaw(string text, LogLevel level, OutFlags flags);
        
        //public static void LogInfo(string text, OutFlags flags)
        //{
        //    LogRaw(text, LogLevel.Info, flags);
        //}
        //public static void LogWarning(string text, OutFlags flags)
        //{
        //    LogRaw(text, LogLevel.Warning, flags);
        //}
        //public static void LogError(string text, OutFlags flags)
        //{
        //    LogRaw(text, LogLevel.Error, flags);
        //}

        //public static void LogFunction(string text, LogLevel level, OutFlags flags)
        //{
        //    var func = RuntimeHelpers.ThisFunctionName();
        //    var line = RuntimeHelpers.ThisLinenumber();
            
        //    LogRaw(string.Format("C# FNC: {0}@LN {1}", func, line), level, flags);
        //}

        //public static void LogFunctionInfo(string text, OutFlags flags) 
        //{
        //}
        //public static void LogFunctionWarning(string text, OutFlags flags)
        //{
        //}
        //public static void LogFunctionError(string text, OutFlags flags)
        //{
        //}
    }
}
