using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.GL
{
    internal sealed class PFDFlags
    {
        public const int DoubleBuffer          = 0x00000001;
        public const int Stereo                = 0x00000002;
        public const int DrawToWindow          = 0x00000004;
        public const int DrawToBitmap          = 0x00000008;
        public const int SupportGDI            = 0x00000010;
        public const int SupportOpenGL         = 0x00000020;
        public const int GenericFormat         = 0x00000040;
        public const int NeedPalette           = 0x00000080;
        public const int NeedSystemPalette     = 0x00000100;
        public const int SwapExchange          = 0x00000200;
        public const int SwapCopy              = 0x00000400;
        public const int SwapLayerBUffers      = 0x00000800;
        public const int GenericAccelerated    = 0x00001000;
        public const int SupportDirectDraw     = 0x00002000;
        public const int D3DAccelerated        = 0x00004000;
        public const int SupportComposition    = 0x00008000;
    }
}
