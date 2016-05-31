using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Engine
{
    public static class SaNiEngine
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Exit();
    }
}
