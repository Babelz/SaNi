using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    internal sealed class Viewport
    {
        #region Properties
        public int X
        {
            get;
            set;
        }
        public int Y
        {
            get;
            set;
        }
        public int Width
        {
            get;
            set;
        }
        public int Height
        {
            get;
            set;
        }
        #endregion

        public Viewport(int x, int y, int width, int height)
        {
            X       = x;
            Y       = y;
            Width   = width;
            Height  = height;
        }
    }
}
