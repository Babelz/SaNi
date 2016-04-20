using OpenTK;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Drawing
{
    [StructLayout(LayoutKind.Sequential)]
    public struct VertexPositionColorTexture
    {
        #region Fields
        public Vector3 position;
        public Vector4 color;
        public Vector2 uv;
        #endregion
    }
}
