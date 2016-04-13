using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public struct VertexPositionColorTexture
    {
        #region Properties
        public VertexPositionColor PositionColor
        {
            get;
            set;
        }
        public Vector2 UV
        {
            get;
            set;
        }
        #endregion
    }
}
