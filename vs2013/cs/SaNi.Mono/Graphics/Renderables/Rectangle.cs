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
    public sealed class Rectangle : IRenderable
    {
        #region Fields
        private Transform transform;
        private Rectf localBounds;
        private Rectf globalBounds;
        private Rectf textureSource;
        private Color borderFill;
        private Color fill;

        private readonly int id;

        private bool destroyed;
        #endregion

        #region Properties
        public Transform Transform
        {
            get
            {
                GetTransform(ref transform);

                return transform;
            }
            set
            {
                SetTransform(value);
            }
        }
        public Rectf LocalBounds
        {
            get
            {
                GetLocalBounds(ref localBounds);

                return localBounds;
            }
            set
            {
                SetLocalBounds(value);
            }
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
            get
            {
                return id;
            }
        }
        public bool Visible
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }
        #endregion

        public Rectangle(float x, float y, float width, float height)
        {
            Instantiate(x, y, width, height, ref id);

            transform       = Transform.Empty();
            localBounds     = Rectf.Empty();
            globalBounds    = Rectf.Empty();
            textureSource   = Rectf.Empty();
            borderFill      = Color.White;
            fill            = Color.White;
        }
        public Rectangle(Vector2 position, Vector2 size)
            : this(position.x, position.y, size.x, size.y)
        {
        }

        #region Internal get/set methods
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTransform(ref Transform value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTransform(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetLocalBounds(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetLocalBounds(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetGlobalBounds(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetGlobalBounds(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTextureSource(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTextureSource(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTexture(ref Texture2D value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTexture(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetBorderThickness(ref float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetBorderThickness(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetBorderFill(ref Color value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetBorderFill(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetFill(ref Color value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetFill(object value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetVisible(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVisible(object value);
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(float x, float y, float width, float height, ref int id);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Release(int id);

        /// <summary>
        /// Destroys the rectangle, causing it to be 
        /// recycled by the engine immediately.
        /// </summary>
        public void Destroy()
        {
            if (destroyed) return;

            Release(ID);

            GC.SuppressFinalize(this);

            destroyed = true;
        }

        ~Rectangle()
        {
            if (!destroyed) Release(ID);
        }
    }
}
