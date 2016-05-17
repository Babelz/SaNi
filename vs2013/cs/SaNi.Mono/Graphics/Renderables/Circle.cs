using SaNi.Mono.Math;
using System;
using System.Runtime.CompilerServices;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class Circle : IRenderable
    {
        #region Constants
        public const uint SmoothCircle  = 36;

        public const uint RoughCircle   = 9;
        #endregion

        #region Fields
        private Transform transform;

        private Rectf localBounds;
        private Rectf globalbounds;
        private Rectf textureSource;
        
        private Color borderfill;
        private Color fill;

        private Texture2D texture;
        
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
                SetTextureSource(value);
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
        public float Radius
        {
            get
            {
                var value = 0.0f;

                GetRadius(ref value);

                return value;
            }
            set
            {
                SetRadius(value);
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
                GetBorderFill(ref borderfill);

                return borderfill;
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
        #endregion

        public Circle(float x, float y, float radius, uint vertices = SmoothCircle)
        {
            transform    = Transform.Empty();

            localBounds  = Rectf.Empty();
            globalbounds = Rectf.Empty();

            borderfill  = new Color();
            fill        = new Color();

            Instantiate(x, y, radius, vertices, ref id, ref ptr);
        }
        public Circle(Vector2 position, float radius, uint vertices = SmoothCircle)
            : this(position.x, position.y, radius, vertices)
        {
        }
        public Circle(Vector3 xyr, uint vertices = SmoothCircle)
            : this(xyr.x, xyr.y, xyr.z, vertices)
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(float x, float y, float radius, uint vertices, ref int id, ref uint ptr);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Release();

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
        private extern void GetVisible(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVisible(bool value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetRadius(ref float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetRadius(float value);

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
        #endregion

        public void Destroy()
        {
            if (destroyed) return;

            Release();

            GC.SuppressFinalize(this);

            destroyed = true;
        }

        ~Circle()
        {
            if (!destroyed) Release();
        }
    }
}