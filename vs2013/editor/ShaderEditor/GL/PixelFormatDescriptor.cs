using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Collections.ObjectModel;

namespace ShaderEditor.GL
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct PixelFormatDescriptor
    {
        #region Fields
        private ushort Size;
        private ushort Version;
        private int Flags;
        private byte PixelType;
        private byte ColorBits;
        private byte RedBits;
        private byte RedShift;
        private byte GreenBits;
        private byte GreenShift;
        private byte BlueBits;
        private byte BlueShift;
        private byte AlphaBits;
        private byte AlphaShift;
        private byte AccumBits;
        private byte AccumRedBits;
        private byte AccumGreenBits;
        private byte AccumBlueBits;
        private byte AccumAlphaBits;
        private byte DepthBits;
        private byte StencilBits;
        private byte AuxBuffers;
        private byte LayerType;
        private byte Reserved;
        private uint LayerMask;
        private uint VisibleMask;
        private uint DamageMask;
        #endregion

        public static PixelFormatDescriptor Create()
        {
            // Create pfd.
            PixelFormatDescriptor pfd = new PixelFormatDescriptor(); 

            pfd.Size            = (ushort)Marshal.SizeOf(typeof(PixelFormatDescriptor));
            pfd.Version         = 1;
            pfd.Flags           = PFD_FLAGS.PFD_DRAW_TO_WINDOW | PFD_FLAGS.PFD_SUPPORT_OPENGL | PFD_FLAGS.PFD_DOUBLEBUFFER;
            pfd.PixelType       = PFD_PIXEL_TYPES.PFD_TYPE_RGBA;
            pfd.ColorBits       = 32;
            pfd.RedBits         = 0;
            pfd.RedShift        = 0;
            pfd.GreenBits       = 0;
            pfd.GreenShift      = 0;
            pfd.BlueBits        = 0;
            pfd.BlueShift       = 0;
            pfd.AlphaBits       = 0;
            pfd.AlphaShift      = 0;
            pfd.AccumBits       = 0;
            pfd.AccumRedBits    = 0;
            pfd.AccumGreenBits  = 0;
            pfd.AccumBlueBits   = 0;
            pfd.AccumAlphaBits  = 0;
            pfd.DepthBits       = 32;
            pfd.StencilBits     = 8;
            pfd.AuxBuffers      = 0;
            pfd.LayerType       = PFD_LAYER_TYPES.PFD_MAIN_PLANE;
            pfd.Reserved        = 0;
            pfd.LayerMask       = 0;
            pfd.VisibleMask     = 0;
            pfd.DamageMask      = 0;

            return pfd;
        }
    }
}
