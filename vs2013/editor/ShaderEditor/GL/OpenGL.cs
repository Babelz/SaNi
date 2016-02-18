using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

namespace ShaderEditor.GL
{
    internal static class OpenGL
    {
        private const string USER32_DLL     = "user32.dll";
        private const string GDI_DLL        = "gdi32.dll";
        private const string GL_DLL         = "opengl32.dll";
        private const string KERNEL_DLL     = "kernel32.dll";

        // user32.dll.
        [DllImport(USER32_DLL, CharSet = CharSet.Auto, SetLastError = false, ExactSpelling = true)]
        public static extern IntPtr GetDC(IntPtr hWnd);

        // gdi32.dll.
        [DllImport(GDI_DLL)]
        public static unsafe extern int ChoosePixelFormat(uint hDC, PixelFormatDescriptor* pfd);

        [DllImport(GDI_DLL)]
        public static unsafe extern int SetPixelFormat(uint hDC, int iPixelFormat, PixelFormatDescriptor* pfd);

        [DllImport(GDI_DLL)]
        public static extern int SwapBuffers(uint hDC);

        // opengl32.dll.
        [DllImport(GL_DLL, EntryPoint = "wglMakeCurrent")]
        public static extern int WGLMakeCurrent(uint hDC, int hglrc);

        [DllImport(GL_DLL, EntryPoint = "wglCreateContext")]
        public static extern int WGLCreateContext(uint hDC);

        [DllImport(GL_DLL, EntryPoint = "glClear")]
        public static extern void GLClear(uint mask);

        [DllImport(GL_DLL, EntryPoint = "glClearColor")]
        public static extern void GLClearColor(float r, float g, float b, float a);

        [DllImport(GL_DLL, EntryPoint = "glViewport")]
        public static extern void GLViewport(int x, int y, uint w, uint h);

        [DllImport(GL_DLL, EntryPoint = "glGetError")]
        public static extern uint GLGetError();

        [DllImport(GL_DLL, EntryPoint = "glEnable")]
        public static extern void GLEnable(uint cap);

        [DllImport(GL_DLL, EntryPoint = "glBlendFunc")]
        public static extern void GLBlendFunc(uint sfactor, uint dfactor);

        // kernel32.dll.
        [DllImport(KERNEL_DLL)]
        public static extern uint GetLastError();

        public static PixelFormatDescriptor CreateDefaultPixelFormatDescriptor()
        {
            // Create pfd.
            PixelFormatDescriptor pfd = new PixelFormatDescriptor();

            pfd.Size = (ushort)Marshal.SizeOf(typeof(PixelFormatDescriptor));
            pfd.Version = 1;
            pfd.Flags = PFDFlags.DrawToWindow | PFDFlags.SupportOpenGL | PFDFlags.DoubleBuffer;
            pfd.PixelType = PFDPixelTypes.TypeRGBA;
            pfd.ColorBits = 32;
            pfd.RedBits = 0;
            pfd.RedShift = 0;
            pfd.GreenBits = 0;
            pfd.GreenShift = 0;
            pfd.BlueBits = 0;
            pfd.BlueShift = 0;
            pfd.AlphaBits = 0;
            pfd.AlphaShift = 0;
            pfd.AccumBits = 0;
            pfd.AccumRedBits = 0;
            pfd.AccumGreenBits = 0;
            pfd.AccumBlueBits = 0;
            pfd.AccumAlphaBits = 0;
            pfd.DepthBits = 32;
            pfd.StencilBits = 8;
            pfd.AuxBuffers = 0;
            pfd.LayerType = PDFLayerType.MainPlane;
            pfd.Reserved = 0;
            pfd.LayerMask = 0;
            pfd.VisibleMask = 0;
            pfd.DamageMask = 0;

            return pfd;
        }

        /// <summary>
        /// Creates a new OpenGL context using the given handle.
        /// </summary>
        /// <param name="hWnd"></param>
        public static unsafe void CreateContext(IntPtr hWnd)
        {
            PixelFormatDescriptor pfd   = CreateDefaultPixelFormatDescriptor();
            IntPtr deviceContext        = GetDC(hWnd);

            uint deviceContextLocation  = (uint)deviceContext;
            
            int pixelFormat = ChoosePixelFormat(deviceContextLocation, &pfd);    
            SetPixelFormat(deviceContextLocation, pixelFormat, &pfd);

            int glContext = WGLCreateContext(deviceContextLocation);
            WGLMakeCurrent(deviceContextLocation, glContext);
        }
    }
}
