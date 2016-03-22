using OpenTK.Graphics.OpenGL4;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Scenes
{
    internal abstract class Scene
    {
        #region Properties
        public int Width
        {
            get;
            protected set;
        }
        public int Height
        {
            get;
            protected set;
        }
        #endregion

        public Scene()
        {
        }

        public virtual void Resize(int width, int height)
        {
            Width   = width;
            Height  = height;

            GL.Viewport(0, 0, width, height);
        }

        public abstract void Draw(float delta);
    }
}
