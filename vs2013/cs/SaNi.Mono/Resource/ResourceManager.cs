using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SaNi.Mono.Resource
{
    /// <summary>
    /// Static interface that can be used to work with content.
    /// </summary>
    public static class ResourceManager
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern object InternalLoad(string assetName, string typeName);

        /// <summary>
        /// Loads asset with given name.
        /// </summary>
        /// <typeparam name="T">type of the asset</typeparam>
        /// <param name="name">name of the asset</param>
        /// <returns>asset or null</returns>
        public static T Load<T>(string assetName) where T : class, IResource
        {
            return InternalLoad(assetName, typeof(T).Name) as T;
        }

        /// <summary>
        /// Unload content.
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Unload();
    }
}
