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
        private readonly uint ptr;

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
        public Rectf GlobalBounds
        {
            get
            {
                GetGlobalBounds(ref globalBounds);

                return globalBounds;
            }
        }
        public Rectf TextureSource
        {
            get
            {
                GetTextureSource(ref textureSource);

                return textureSource;
            }
            set
            {
                SetTextureSource(value);
            }
        }
        public Texture2D Texture
        {
            get
            {
                Texture2D texture = null;

                GetTexture(ref texture);

                return texture;
            }
            set
            {
                SetTexture(value);
            }
        }
        public float BorderThickness
        {
            get
            {
                var value = 0.0f;

                GetBorderThickness(ref value);
                
                return value;
            }
            set
            {
                SetBorderThickness(value);
            }
        }
        public Color BorderFill
        {
            get
            {
                GetBorderFill(ref borderFill);

                return borderFill;
            }
            set
            {
                SetBorderFill(value);
            }
        }
        public Color Fill
        {
            get
            {
                GetFill(ref fill);

                return fill;
            }
            set
            {
                SetFill(value);
            }
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
            get
            {
                bool visible = false;

                GetVisible(ref visible);

                return visible;
            }
            set
            {
                SetVisible(value);
            }
        }
        #endregion

        public Rectangle(float x, float y, float width, float height)
        {
            Instantiate(x, y, width, height, ref id, ref ptr);

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
        private extern void SetTransform(Transform value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetLocalBounds(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetLocalBounds(Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetGlobalBounds(ref Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTextureSource(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTextureSource(Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTexture(ref Texture2D value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTexture(Texture2D value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetBorderThickness(ref float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetBorderThickness(float value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetBorderFill(ref Color value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetBorderFill(Color value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetFill(ref Color value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetFill(Color value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetVisible(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVisible(bool value);
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(float x, float y, float width, float height, ref int id, ref uint ptr);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Release();

        /// <summary>
        /// Destroys the rectangle, causing it to be 
        /// recycled by the engine immediately.
        /// </summary>
        public void Destroy()
        {
            if (destroyed) return;

            Release();

            GC.SuppressFinalize(this);

            destroyed = true;
        }
    }
}
