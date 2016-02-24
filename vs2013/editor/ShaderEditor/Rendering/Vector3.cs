using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    /// <summary>
    /// Simplified vector with x, y and z components.
    /// </summary>
    internal struct Vector3
    {
        #region Fields
        public float X;
        public float Y;
        public float Z;
        #endregion

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
    }
}
