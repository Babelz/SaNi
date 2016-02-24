using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    /// <summary>
    /// Defines vertex that has position, color and texture coordinates.
    /// Contains total 9 elements.
    /// </summary>
    internal sealed class VertexPositionColorTexture
    {
        internal const int VertexElementsCount = 9;

        #region Fields
        public Vector3 Position;
        
        public Vector4 Color;

        public Vector2 TextureCoordinates;
        #endregion

        public VertexPositionColorTexture()
        {
            Position            = new Vector3();
            Color               = new Vector4();
            TextureCoordinates  = new Vector2();
        }

        /// <summary>
        /// Copy data from this vertex to given buffer.
        /// </summary>
        /// <param name="buffer">buffer we are copying to</param>
        /// <param name="bufferPointer">index where the first element will be placed</param>
        public void CopyData(float[] buffer, ref int bufferPointer)
        {
            buffer[bufferPointer++] = Position.X;
            buffer[bufferPointer++] = Position.Y;
            buffer[bufferPointer++] = Position.Z;

            buffer[bufferPointer++] = Color.X;
            buffer[bufferPointer++] = Color.Y;
            buffer[bufferPointer++] = Color.Z;
            buffer[bufferPointer++] = Color.W;

            buffer[bufferPointer++] = TextureCoordinates.X;
            buffer[bufferPointer++] = TextureCoordinates.Y;
        }
    }
}
