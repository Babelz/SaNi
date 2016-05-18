using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public interface ITexture : IGraphicsResource
    {
        #region Properties
        int Width
        {
            get;
        }
        int Height
        {
            get;
        }
        #endregion
    }
}
