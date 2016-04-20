using ShaderEditor.Drawables;
using ShaderEditor.Drawing;
using ShaderEditor.Shaders;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Scenes
{
    public interface IScene
    {
        #region Properties
        Color ClearColor
        {
            get;
            set;
        }
        IEffect Effect
        {
            get;
            set;
        }
        Texture2D Texture
        {
            get;
            set;
        }
        #endregion

        void Draw(float delta);
    }
}
