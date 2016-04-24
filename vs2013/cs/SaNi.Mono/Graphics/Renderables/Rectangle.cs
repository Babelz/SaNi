using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class Rectangle : IRenderable
    {
        #region Fields
        public int num;
        private bool destroyed;
        #endregion

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
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        public extern Rectf GlobalBounds
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
        }
        public Rectf TextureSource
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        public Texture2D Texture
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
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
        public int ID
        {
            get;
            private set;
        }
        public bool Visible
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Print();

        public Rectangle(float x, float y, float width, float height)
        {
            ID = InternalCreateRectangle(x, y, width, height);

            num = ID * 10;

            Console.WriteLine("id: {0}", ID);
        }
        public Rectangle(Vector2 position, Vector2 size)
            : this(position.x, position.y, size.x, size.y)
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalCreateRectangle(float x, float y, float width, float height);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void InternalReleaseRectangle(int id);

        /// <summary>
        /// Destroys the rectangle, causing it to be 
        /// recycled by the engine immediately.
        /// </summary>
        public void Destroy()
        {
            if (destroyed) return;

            Console.WriteLine("destr");

            InternalReleaseRectangle(ID);

            GC.SuppressFinalize(this);

            destroyed = true;
        }

        ~Rectangle()
        {
            Console.WriteLine("dtor");
            if (!destroyed) InternalReleaseRectangle(ID);
        }
    }
}
