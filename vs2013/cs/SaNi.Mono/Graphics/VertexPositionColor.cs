using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public struct VertexPositionColor
    {
        #region Properties
        public Vector3 Position
        {
            get;
            set;
        }
        public Vector4 Color
        {
            get;
            set;
        }
        #endregion
    }
}
