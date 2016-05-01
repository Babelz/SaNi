using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public static class Layers
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static Layer[] GetLayers();

        public static Layer Find(Func<Layer, bool> pred)
        {
            return GetLayers().FirstOrDefault(pred);
        }
        public static int Count()
        {
            return GetLayers().Length;
        }
    }
}
