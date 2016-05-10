using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    [Flags()]
    public enum PropertySettings : int
    {
        None    = 0,
        
        Get     = 1,
        
        Set     = 2,

        GetSet  = 3
    }
}
