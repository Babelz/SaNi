using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    /// <summary>
    /// Simplified float rectangle.
    /// </summary>
    internal sealed class Rectf
    {
        #region Fields
        public float X;
        public float Y;
        public float Width;
        public float Height;
        #endregion

        #region Properties
        public float Left
        {
            get
            {
                return X;
            }
        }
        public float Right
        {
            get
            {
                return X + Width;
            }
        }
        public float Top
        {
            get
            {
                return Y;
            }
        }
        public float Bottom
        {
            get
            {
                return Y + Bottom;
            }
        }
        #endregion
    }
}
