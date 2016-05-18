using SaNi.Mono.Graphics.Renderables;
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
        private static extern Layer Create(string name, IRenderable[] elements, LayerType layerType); 

        /// <summary>
        /// Creates new static layer.
        /// </summary>
        /// <param name="name">name of the layer</param>
        /// <param name="renderables">renderables that the static layer will contain</param>
        /// <returns>new dynamic layer</returns>
        public static Layer CreateStatic(string name, IRenderable[] elements)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Creates new dynamic layer.
        /// </summary>
        /// <param name="name">name of the layer</param>
        /// <param name="renderables">initial renderables the layer will contain</param>
        /// <returns>new dynamic layer</returns>
        public static Layer CreateDynamic(string name)
        {
            return Create(name, null, LayerType.Dynamic);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Destroy(Layer layer);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Layer[] GetLayers();

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
