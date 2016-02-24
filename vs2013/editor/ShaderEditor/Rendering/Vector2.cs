using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{    
    /// <summary>
    /// Simplified vector with x and y components.
    /// </summary>
    internal struct Vector2
    {
        #region Fields
        public float X;
        public float Y;
        #endregion

        public Vector2(float x, float y)
        {
            X = x;
            Y = y;
        }
    }
}
