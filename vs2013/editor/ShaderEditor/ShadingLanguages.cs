using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor
{
    [Flags()]
    public enum ShadingLanguages : int
    {
        GLSL = 0,
        HLSL = 1
    }
}
