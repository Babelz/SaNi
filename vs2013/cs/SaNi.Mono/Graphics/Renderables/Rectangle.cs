using SaNi.Mono.Engine;
using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class Rectangle //: IRenderable
    {
        #region Fields
        private readonly int id;

        //private bool destroyed;
        #endregion

        #region Properties
        //public Transform Transform
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    set;
        //}
        public Rectf LocalBounds
        {
            get
            {
                Console.WriteLine("GET_REKT");
                return GetLocalBounds();
            }
            set
            {
                SetLocalBounds(value);
            }
        }
        //public extern Rectf GlobalBounds
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //}
        //public Rectf TextureSource
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    set;
        //}
        //public Texture2D Texture
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    set;
        //}
        //public float BorderThickness
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    set;
        //}
        //public Color BorderFill
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    set;
        //}
        //public Color Fill
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    set;
        //}
        //public bool Destroyed
        //{
        //    get
        //    {
        //        return destroyed;
        //    }
        //}
        public int ID
        {
            get
            {
                return id;
            }
        }
        //public bool Visible
        //{
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    get;
        //    [MethodImpl(MethodImplOptions.InternalCall)]
        //    set;
        //}
        #endregion

        //[MethodImpl(MethodImplOptions.InternalCall)]
        //public extern void ASD();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Rectangle Instantiate(float x, float y, float width, float height);

        public static Rectangle Instantiate(Vector2 position, Vector2 size)
        {
            return Instantiate(position.x, position.y, size.x, size.y);
        }

        private Rectangle(int id)
        {
            this.id = id;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern Rectf GetLocalBounds();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void SetLocalBounds(Rectf value);
      
        //[MethodImpl(MethodImplOptions.InternalCall)]
        //private extern void Release(int id);

        ///// <summary>
        ///// Destroys the rectangle, causing it to be 
        ///// recycled by the engine immediately.
        ///// </summary>
        //public void Destroy()
        //{
        //    if (destroyed) return;

        //    Release(ID);

        //    GC.SuppressFinalize(this);

        //    destroyed = true;
        //}

        //~Rectangle()
        //{
        //    if (!destroyed) Release(ID);
        //}
    }
}
