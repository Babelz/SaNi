using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    internal sealed class Texture2D
    {
        #region Properties
        public int Width
        {
            get;
            private set;
        }
        public int Height
        {
            get;
            private set;
        }
        public int ID
        {
            get;
            private set;
        }
        #endregion
        
        public Texture2D(int width, int height, int id)
        {
            Width = width;
            Height = height;
            ID = id;
        }
    }
}
