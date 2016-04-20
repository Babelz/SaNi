using OpenTK;
using ShaderEditor.Drawing;
using ShaderEditor.Shaders;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Drawables
{
    public interface IDrawable
    {
        #region Properties
        Color Color
        {
            get;
            set;
        }
        Transform Transform
        {
            get;
        }
        Texture2D Texture
        {
            get;
            set;
        }
        #endregion

        void Draw(float delta, float total);
    }
}
