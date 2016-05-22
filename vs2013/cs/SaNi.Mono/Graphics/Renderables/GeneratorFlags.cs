using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    [Flags()]
    public enum GeneratorFlags : short
    {
        None                        = 0,
        VaryingSpawnLocation        = 1,
        VaryingVelocity             = 2,	
        VaryingAcceleration         = 4,
        VaryingScale                = 8,
        VaryingScaleAcceleration    = 16,
        UseScaleAcceleration        = 32,
        VaryingScaleVelocity        = 64,
        UseScaleVelocity            = 128,
        VaryingAngularVelocity      = 256,
        VaryingAngularAcceleration  = 512,
        VaryingDecayTime            = 1024,
        VaryingColor                = 2048,
        VaryingAttributes           = 4096	
    }
}
