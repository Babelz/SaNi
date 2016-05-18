using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public interface IGraphicsResource
    {
        #region Properties
        int ID
        {
            get;
        }
        bool Disposed
        {
            get;
        }
        #endregion
    }
}
