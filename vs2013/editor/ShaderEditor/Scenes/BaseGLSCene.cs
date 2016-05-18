using OpenTK;
using OpenTK.Graphics.OpenGL;
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
    public abstract class BaseGLSCene : IScene
    {
        #region Fields
        private readonly GLControl glControl;
        #endregion

        #region Properties
        public Color ClearColor
        {
            get;
            set;
        }
        public IEffect Effect
        {
            get;
            set;
        }
        public Texture2D Texture
        {
            get;
            set;
        }
        #endregion

        #region Events
        protected event EventHandler ViewSizeChanged
        {
            add
            {
                glControl.SizeChanged += value;
            }
            remove
            {
                glControl.SizeChanged -= value;
            }
        }
        #endregion

        public BaseGLSCene(GLControl glControl)
        {
            this.glControl = glControl;

            ClearColor = Color.CornflowerBlue;

            GL.Viewport(0, 0, glControl.Size.Width, glControl.Size.Height);
            GL.Enable(EnableCap.Blend);
            GL.BlendFunc(BlendingFactorSrc.SrcAlpha, BlendingFactorDest.OneMinusSrcAlpha);
            Assert.GLAssert();
        }

        protected abstract void GLDraw(float delta, float time, Vector2 resolution);

        public void Draw(float delta, float time)
        {
            GLDraw(delta, time, new Vector2(glControl.Width, glControl.Height));

            GL.ClearColor(ClearColor);

            glControl.SwapBuffers();

            GL.Clear(ClearBufferMask.ColorBufferBit);
        }
    }
}
