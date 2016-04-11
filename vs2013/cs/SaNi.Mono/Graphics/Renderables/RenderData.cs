using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class RenderData
    {
        #region Properties
        public int VerticesCount
        {
            get;
            set;
        }
        public int VertexIndicesCount
        {
            set;
            get;
        }

        public int RenderElementsCount
        {
            set;
            get;
        }
        public int RenderElementIndicesCount
        {
            set;
            get;
        }
        #endregion

        public RenderData()
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern List<VertexPositionColorTexture> GetVertices();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern List<int> GetVertexIndices();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern List<RenderElementData> GetRenderElements();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern List<int> GetRenderElementIndices();
    }
}
