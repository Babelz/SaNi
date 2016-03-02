using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.GL
{
    public static class GLEnums
    {
        public const uint ColorBufferBit       = 0x00004000;
        public const uint DepthBufferBit       = 0x00000100;
        public const uint Blend                = 0x0BE2;
        public const uint SrcAlpha             = 0x0302;
        public const uint OneMinusSrcAlpha     = 0x0303;
        public const uint Alpha                = 0x1906;

        public const uint Texture1D            = 0x0DE0;
        public const uint Texture2D            = 0x0DE1;
    }
}
