using OpenTK;
using OpenTK.Graphics.OpenGL;
using ShaderEditor.Drawables;
using ShaderEditor.Drawables.OpenGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Scenes.OpenGL
{
    public sealed class GLPlaneScene : BaseGLSCene
    {
        #region Fields
        private readonly Plane plane;

        private Matrix4 ortho;
        #endregion

        public GLPlaneScene(GLControl glControl)
            : base(glControl)
        {
            plane = new Plane();
            ortho = new Matrix4();

            RecomputeOrtho(glControl.Width, glControl.Height);
            UpdatePlane(glControl);

            ViewSizeChanged += GLPlaneScene_ViewSizeChanged;
        }

        #region Event handlers
        private void GLPlaneScene_ViewSizeChanged(object sender, EventArgs e)
        {
            var glControl = sender as GLControl;

            UpdateViewport(glControl.Width, glControl.Height);
            RecomputeOrtho(glControl.Width, glControl.Height);
            UpdatePlane(glControl);
        }
        #endregion

        private void UpdateViewport(int width, int height)
        {
            GL.Viewport(0, 0, width, height);
            Assert.GLAssert();
        }
        private void RecomputeOrtho(float width, float height)
        {
            ortho = Matrix4.CreateOrthographicOffCenter(0.0f, width, height, 0.0f, -1.0f, 1.0f);
        }
        private void UpdatePlane(GLControl glControl)
        {
            plane.Transform.size.X = (float)glControl.Size.Width;
            plane.Transform.size.Y = (float)glControl.Size.Height;

            plane.Transform.origin.X = plane.Transform.size.X / 2.0f;
            plane.Transform.origin.Y = plane.Transform.size.Y / 2.0f;
        }

        protected override void GLDraw(float delta, float time, Vector2 resolution)
        {
            if (Effect == null) return;

            Effect.Bind();
            Effect.SetUniformValue("transform", ortho, typeof(Matrix4));
            Effect.SetUniformValue("delta", delta, typeof(float));
            Effect.SetUniformValue("time", time / 100.0f, typeof(float));
            Effect.SetUniformValue("resolution", resolution, typeof(Vector2));

            plane.Texture = Texture;

            plane.Draw(delta, time);

            Effect.Unbind();
        }
    }
}
