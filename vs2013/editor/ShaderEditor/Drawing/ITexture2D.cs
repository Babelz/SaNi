using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Drawing
{
    public interface ITexture2D
    {
        #region Properties
        int Width
        {
            get;
        }
        int Height
        {
            get;
        }
        #endregion

        void Bind();
        void Unbind();
    }
}
