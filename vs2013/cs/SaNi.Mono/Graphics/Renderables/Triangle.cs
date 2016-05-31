using SaNi.Mono.Graphics;
using SaNi.Mono.Math;
using System;
using System.Runtime.CompilerServices;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class Triangle : IRenderable
    {
        #region Fields
        private Transform transform;
        private Rectf localBounds;
        private Rectf globalbounds;
        private Rectf textureSource;
        private Texture2D texture;

        private Vector2 toppoint;
        private Vector2 leftpoint;
        private Vector2 rightpoint;

        private Color borderfill;
        private Color fill;

        private float borderthickness;

        private int id;
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
        public Vector2 TopPoint
        {
            get
            {
                GetTopPoint(ref toppoint);

                return toppoint;
            }
            set
            {
                SetTopPoint(value);
            }
        }
        public Vector2 LeftPoint
        {
            get
            {
                GetLeftPoint(ref leftpoint);

                return leftpoint;
            }
            set
            {
                SetLeftPoint(value);
            }
        }
        public Vector2 RightPoint
        {
            get
            {
                GetRightPoint(ref rightpoint);

                return rightpoint;
            }
            set
            {
                SetRightPoint(value);
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

        public Triangle(float x, float y, float w, float h)
        {
            InitializeMembers();

            var tx = x + w / 2.0f;
            var ty = y;

            var lx = x;
            var ly = y + h;

            var rx = x + w;
            var ry = y + h;

            Instantiate(tx, ty, lx, ly, rx, ry, ref id, ref ptr);
        }
        public Triangle(Vector2 position, Vector2 size)
            : this(position.x, position.y, size.x, size.y) {
        }
        
        public Triangle(float tx, float ty, float lx, float ly, float rx, float ry)
        {
            InitializeMembers();

            Instantiate(tx, ty, lx, ly, rx, ry, ref id, ref ptr);
        }
        public Triangle(Vector2 top, Vector2 left, Vector2 right)
            : this(top.x, top.y, left.x, left.y, right.x, right.y)
        {
        }

        private void InitializeMembers() 
        {
            transform    = Transform.Empty();
            globalbounds = Rectf.Empty();
            
            toppoint     = Vector2.Zero;
            leftpoint    = Vector2.Zero;
            rightpoint   = Vector2.Zero;
            
            borderfill   = new Color();
            fill         = new Color();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(float tx, float ty, float lx, float ly, float rx, float ry, ref int id, ref uint ptr);
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
        private extern void GetTextureSource(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTextureSource(Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetGlobalBounds(ref Rectf value);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTexture(ref Texture2D value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTexture(Texture2D value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetVisible(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVisible(bool value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTopPoint(ref Vector2 value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTopPoint(Vector2 value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetLeftPoint(ref Vector2 value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetLeftPoint(Vector2 value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetRightPoint(ref Vector2 value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetRightPoint(Vector2 value);

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
    }
}