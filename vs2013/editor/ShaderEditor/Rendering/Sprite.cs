using OpenTK;
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
        public Vector2 TextureSourcePosition
        {
            get;
            set;
        }
        public Vector2 TextureSourceSize
        {
            get;
            set;
        }
        public Texture2D Texture
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
        }

        public void ResetTextureSource()
        {
            TextureSourcePosition   = new Vector2(0.0f, 0.0f);
            TextureSourceSize       = new Vector2((float)Texture.Width, (float)Texture.Height);
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

            var localBottomRight = new Vector3();
            localBottomRight.X = Bounds.X * Scale.X;
            localBottomRight.Y = Bounds.Y * Scale.Y;

            // Apply rotation.
            var globalTopLeft = Position;
            var globalTopRight = Position;
            var globalBottomLeft = Position;
            var globalBottomRight = Position;

            globalTopLeft.X = globalTopLeft.X + (dx + localTopLeft.X) * cos - dy * sin;
            globalTopLeft.Y = globalTopLeft.Y + (dx + localTopLeft.X) * sin + dy * cos;

            globalTopRight.X = globalTopRight.X + (dx + localTopRight.X) * cos - dy * sin;
            globalTopRight.Y = globalTopRight.Y + (dx + localTopRight.X) * sin + dy * cos;

            globalBottomLeft.X = globalBottomLeft.X + dx * cos - (dy + localBottomLeft.Y) * sin;
            globalBottomLeft.Y = globalBottomLeft.Y + dx * sin + (dy + localBottomLeft.Y) * cos;

            globalBottomRight.X = globalBottomRight.X + (dx + localBottomLeft.X) * cos - (dy + localBottomRight.Y) * sin;
            globalBottomRight.Y = globalBottomRight.Y + (dx + localBottomLeft.X) * sin + (dy + localBottomRight.Y) * cos;

            // Compute coordinates.
            var sourceLeft = TextureSourcePosition.X;
            var sourceRight = TextureSourcePosition.X + TextureSourceSize.X;
            var sourceTop = TextureSourcePosition.Y;
            var sourceBottom = TextureSourcePosition.Y + TextureSourceSize.Y;

            var topLeftUV = new Vector3();
            topLeftUV.X = sourceLeft / Texture.Width;
            topLeftUV.Y = sourceBottom / Texture.Height;

            var topRightUV = new Vector3();
            topLeftUV.X = sourceRight / Texture.Width;
            topLeftUV.Y = sourceBottom / Texture.Height;

            var bottomLeftUV = new Vector3();
            bottomLeftUV.X = sourceLeft / Texture.Width;
            bottomLeftUV.Y = sourceTop / Texture.Height;

            var bottomRightUV = new Vector3();
            bottomRightUV.X = sourceRight / Texture.Width;
            bottomRightUV.Y = sourceTop / Texture.Height;

            // Apply position, uv and color.
            var vertexPositions = new[]
            {
                globalTopLeft,
                topLeftUV,
                
                globalTopRight,
                topRightUV,
                
                globalBottomLeft,
                bottomLeftUV,

                globalBottomRight,
                bottomRightUV
            };

            for (int i = 0; i < vertexPositions.Length; i += 2)
            {
                RenderData.VertexData[i].Position               = vertexPositions[i];
                RenderData.VertexData[i].TextureCoordinates.X   = vertexPositions[i + 1].X;
                RenderData.VertexData[i].TextureCoordinates.Y   = vertexPositions[i + 1].Y;
                RenderData.VertexData[i].Color                  = Color;
            }
        }
    }
}
