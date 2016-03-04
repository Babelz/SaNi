using OpenTK.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    internal sealed class Camera2D
    {
        #region Fields
        private readonly Viewport viewport;
        
        public float rotation;
        public float zoom;
        #endregion

        public Camera2D(Viewport viewport)
        {
            this.viewport = viewport;

            zoom     = 1.0f;
            rotation = 0.0f;
        }

        public void ResetZoom()
        {
            zoom = 1.0f;
        }
        public void ResetRotation()
        {
            rotation = 0.0f;
        }

        public void Zoom(float amount)
        {
            zoom += amount;
        }
        public void Rotate(float amount)
        {
            rotation += amount;
        }

        public OpenTK.Matrix4 Transform()
        {
            var transform = OpenTK.Matrix4.CreateOrthographic((float)viewport.Width, (float)viewport.Height, 1.0f, 100.0f);
            transform = OpenTK.Matrix4.CreateTranslation(-0.0f, -0.0f, 0.0f) * transform;

            return transform;
        }
    }
}
