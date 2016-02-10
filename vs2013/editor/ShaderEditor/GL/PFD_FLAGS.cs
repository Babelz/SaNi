using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.GL
{
    internal static class PFD_FLAGS
    {   
        public const int PFD_DOUBLEBUFFER           = 0x00000001;
        public const int PFD_STEREO                 = 0x00000002;
        public const int PFD_DRAW_TO_WINDOW         = 0x00000004;
        public const int PFD_DRAW_TO_BITMAP         = 0x00000008;
        public const int PFD_SUPPORT_GDI            = 0x00000010;
        public const int PFD_SUPPORT_OPENGL         = 0x00000020;
        public const int PFD_GENERIC_FORMAT         = 0x00000040;
        public const int PFD_NEED_PALETTE           = 0x00000080;
        public const int PFD_NEED_SYSTEM_PALETTE    = 0x00000100;
        public const int PFD_SWAP_EXCHANGE          = 0x00000200;
        public const int PFD_SWAP_COPY              = 0x00000400;
        public const int PFD_SWAP_LAYER_BUFFERS     = 0x00000800;
        public const int PFD_GENERIC_ACCELERATED    = 0x00001000;
        public const int PFD_SUPPORT_DIRECTDRAW     = 0x00002000;
        public const int PFD_DIRECT3D_ACCELERATED   = 0x00004000;
        public const int PFD_SUPPORT_COMPOSITION    = 0x00008000;
    }
}
