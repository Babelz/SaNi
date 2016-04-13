using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class Rectangle : Renderable
    {
        #region Fields
        private bool destroyed;
        #endregion

        #region Properties
        public float BorderThickness
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        public Color BorderFill
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        public Color Fill
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        public bool Destroyed
        {
            get
            {
                return destroyed;
            }
        }
        #endregion

        public Rectangle(float x, float y, float width, float height)
        {
            InternalCreateRectangle(x, y, width, height);
        }
        public Rectangle(Vector2 position, Vector2 size)
        {
            InternalCreateRectangle(position.X, position.Y, size.X, size.Y);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void InternalCreateRectangle(float x, float y, float width, float height);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void InternalReleaseRectangle();

        /// <summary>
        /// Destroys the rectangle, causing it to be 
        /// recycled by the engine immediately.
        /// </summary>
        public void Destroy()
        {
            if (destroyed) return;

            InternalReleaseRectangle();

            GC.SuppressFinalize(this);

            destroyed = true;
        }

        ~Rectangle()
        {
            if (!destroyed) InternalReleaseRectangle();
        }
    }
}
