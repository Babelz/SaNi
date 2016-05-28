using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Configuration
{
    public static class CVars
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern CVar[] GetCVars();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern CVar Create(ValueType valueType, string name, bool synced, object value);

        public static CVar Create(object statements, ValueType valueType, string name, bool synced, object value)
        {
            throw new NotImplementedException();
        }
    }
}
