using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    /// <summary>
    /// Simplified vector with x, y, z and w components.
    /// </summary>
    internal struct Vector4
    {
        #region Fields
        public float X;
        public float Y;
        public float Z;
        public float W;
        #endregion

        public Vector4(float x, float y, float z, float w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }
    }
}
