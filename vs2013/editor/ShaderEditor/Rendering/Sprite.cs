using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    /// <summary>
    /// Simplified sprite class that has position, color,
    /// scale, bounds, texture source, origin and rotation.
    /// </summary>
    internal sealed class Sprite
    {
        internal const int VerticesCount    = 4;
        internal const int IndicesCount     = 6;

        #region Properties
        public Vector3 Position
        {
            get;
            set;
        }
        public Vector2 Origin
        {
            get;
            set;
        }
        public Vector4 Color
        {
            get;
            set;
        }
        public Vector2 Scale
        {
            get;
            set;
        }
        public Vector2 Bounds
        {
            get;
            set;
        }
        public Rectf TextureSource
        {
            get;
            set;
        }

        public RenderData RenderData
        {
            get;
            private set;
        }

        public float Rotation
        {
            get;
            set;
        }
        #endregion

        public Sprite()
        {
            RenderData = new RenderData(VerticesCount, IndicesCount);

            InitializeIndices();
            DefaultTextureSource();
        }

        private void InitializeIndices()
        {
            RenderData.Indices[0] = 0;
            RenderData.Indices[1] = 1;
            RenderData.Indices[2] = 2;

            RenderData.Indices[3] = 2;
            RenderData.Indices[4] = 3;
            RenderData.Indices[5] = 1;
        }

        public void DefaultTextureSource()
        {
            TextureSource.X = 0;
            TextureSource.Y = 0;

            TextureSource.Width = Scale.X * Bounds.X;
            TextureSource.Height = Scale.Y * Bounds.Y; 
        }

        public void Update(float delta)
        {
            var sin = (float)Math.Sin(Rotation);
            var cos = (float)Math.Sin(Rotation);

            var dx = -Origin.X * Scale.X;
            var dy = -Origin.Y * Scale.Y;
            
            // Update vertex positions and rotation.
            var localTopLeft = new Vector3();

            var localTopRight = new Vector3();
            localTopRight.X = Bounds.X * Scale.X;

            var localBottomLeft = new Vector3();
            localBottomLeft.Y = Bounds.Y * Scale.Y;

            var localBottomRight = new Vector2();
            localBottomRight.X = Bounds.X * Scale.X;
            localBottomRight.Y = Bounds.Y * Scale.Y;
        }
    }
}
