using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Content
{
    public static class ContentManager
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T Load<T>(string name) where T : Resource;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Exists(string name);
    }
}
