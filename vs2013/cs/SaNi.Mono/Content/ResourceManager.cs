using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Content
{
    /// <summary>
    /// Static interface that can be used to work with content.
    /// </summary>
    public static class ResourceManager
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern object InternalLoad(Type type, string name);

        /// <summary>
        /// Loads asset with given name.
        /// </summary>
        /// <param name="name">name of the asset</param>
        /// <returns>boxed asset or null</returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Load(string name);

        /// <summary>
        /// Loads asset with given name.
        /// </summary>
        /// <typeparam name="T">type of the asset</typeparam>
        /// <param name="name">name of the asset</param>
        /// <returns>asset or null</returns>
        public static T Load<T>(string name) where T : class, IResource
        {
            return InternalLoad(typeof(T), name) as T;
        }

        /// <summary>
        /// Unload content.
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unload();
    }
}
