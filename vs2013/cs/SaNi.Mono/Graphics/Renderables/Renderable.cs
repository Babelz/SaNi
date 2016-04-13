using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public abstract class Renderable
    {
        #region Properties
        public Transform Transform
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        public Rectf LocalBounds
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
        public Rectf GlobalBounds
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
        public Rectf TextureSource
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
        public Texture2D Texture
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        #endregion

        public Renderable()
        {
        }
    }
}
