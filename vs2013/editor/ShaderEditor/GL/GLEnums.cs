using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.GL
{
    public static class GLEnums
    {
        public const uint ColorBufferBit = 0x00004000;
        public const uint DepthBufferBit = 0x00000100;
        public const uint Blend = 0x0BE2;
        public const uint SrcAlpha = 0x0302;
        public const uint OneMinusSrcAlpha = 0x0303;
        public const uint Alpha = 0x1906;

        public const uint Texture1D = 0x0DE0;
        public const uint Texture2D = 0x0DE1;

        public const uint SurfaceFormatRGBA = 0x1908;

        public const uint GLByte = 0x1400;
        public const uint GLUByte = 0x1401;
        public const uint GLShort = 0x1402;
        public const uint GLUshort = 0x1403;
        public const uint GLInt = 0x1404;
        public const uint GLUint = 0x1405;
        public const uint GLFloat = 0x1406;
        public const uint GLMat3F = 0x8B5B;

        public const uint VertexShader = 0x8B31;
        public const uint FragmentShader = 0x8B30;
        public const uint CompileStatus = 0x8B81;
        public const uint InfoLogLength = 0x8B84;
        public const uint LinkStatus = 0x8B82;
    }
}
