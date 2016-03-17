using OpenTK;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Scenes
{
    internal sealed class SpriteScene : Scene
    {
        #region Fields
        private Matrix4 transform;
        
        private int vbo;
        private int ibo;
        private int vao;
        #endregion

        #region Properties
        #endregion

        public SpriteScene()
            : base()
        {
        }

        public override void Draw(float delta)
        {
        }
    }
}
