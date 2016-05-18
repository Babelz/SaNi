using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public enum LayerType : byte
    {			
        /// Static layers are rendered once and the results 
        /// can be used many times.
        Static = 0,

        /// Dynamic layers are rendered each frame.
        Dynamic = 1
    }
}
