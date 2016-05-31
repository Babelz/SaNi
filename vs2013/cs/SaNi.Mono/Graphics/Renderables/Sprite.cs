using SaNi.Mono.Math;
using System;
using System.Runtime.CompilerServices;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class Sprite : IRenderable
    {
        #region Fields
        private Transform transform;
        
        private Rectf localBounds;
        private Rectf globalbounds;
        private Rectf textureSource;

        private Texture2D texture;
        
        private Color color;

        private readonly int id;
        private readonly uint ptr;

        private uint layer;

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
                GetGlobalBounds(ref globalbounds);

                return globalbounds;
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
                SetTextureSource(textureSource);
            }
        }
        public Texture2D Texture
        {
            get
            {
                GetTexture(ref texture);

                return texture;
            }
            set
            {
                SetTexture(value);
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
                var value = false;

                GetVisible(ref value);

                return value;
            }
            set
            {
                SetVisible(value);
            }
        }
        public Color Color
        {
            get
            {
                GetColor(ref color);

                return color;
            }
            set
            {
                SetColor(value);
            }
        }
        #endregion

        public Sprite(float x, float y, float width, float height, Texture2D texture)
        {
            transform       = Transform.Empty();
            
            globalbounds    = Rectf.Empty();
            localBounds     = Rectf.Empty();
            textureSource   = Rectf.Empty();

            color           = new Color();

            Instantiate(x, y, width, height, texture, ref id, ref ptr);
        }
        public Sprite(float x, float y, Texture2D texture)
            : this(x, y, texture.Width, texture.Height, texture)
        {
        }
        public Sprite(Vector2 position, Vector2 size, Texture2D texture)
            : this(position.x, position.y, size.x, size.y, texture)
        {
        }
        public Sprite(Vector2 position, Texture2D texture)
            : this(position.x, position.y, texture.Width, texture.Height, texture)
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(float x, float y, float width, float height, Texture2D texture, ref int id, ref uint ptr);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Release();

        #region Internal get/set methods
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTransform(ref Transform value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTransform(Transform value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetGlobalBounds(ref Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetLocalBounds(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetLocalBounds(Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTextureSource(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTextureSource(Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTexture(ref Texture2D value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTexture(Texture2D value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetVisible(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVisible(bool value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetColor(ref Color value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetColor(Color value);
        #endregion

        public void Destroy()
        {
            if (destroyed) return;

            Release();

            GC.SuppressFinalize(this);

            destroyed = true;
        }
    }
}