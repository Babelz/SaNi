using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    /// <summary>
    /// Render data that is defined by vertex, index and texture data.
    /// </summary>
    internal sealed class RenderData
    {
        #region Properties
        public VertexPositionColorTexture[] VertexData
        {
            get;
            private set;
        }
        #endregion

        public RenderData(int verticesCount, int indicesCount)
        {
            VertexData  = new VertexPositionColorTexture[verticesCount];
        }
    }
}
