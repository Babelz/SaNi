using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    [Flags()]
    public enum PropertyReadSettings : int
    {
        None            = 0,
        Default         = 1,
        Reference       = 2
    }
}
