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
        /*
            GLuint      = 32u
            GLenum      = 32
            GLsizei     = 32
            GLbitfield  = 32
        */

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

        [DllImport(GL_DLL, EntryPoint = "glGenTextures")]
        public static extern void GLGenTextures(int count, ref int textures);

        [DllImport(GL_DLL, EntryPoint = "glBindTexture")]
        public static extern void GLBindTexture(uint target, uint texture);

        [DllImport(GL_DLL, EntryPoint = "glTexImage2D")]
        public static extern void GLTexImage2D(uint target, int level, int internalFormat, int width, int height, int border,
                                               uint format, uint type, IntPtr data);

        [DllImport(GL_DLL, EntryPoint = "glTexParametri")]
        public static extern void GLTexParametri(uint target, uint field, int value);
        
        [DllImport(GL_DLL, EntryPoint="glGenBuffers")]
        public static extern void GLGenBuffers(int count, ref int buffers);

        [DllImport(GL_DLL, EntryPoint="glBufferData")]
        public static extern void GLBufferData(uint target, uint offset, uint bytes, IntPtr data);

        [DllImport(GL_DLL, EntryPoint="glBufferSubData")]
        public static extern void GLBufferSubData(uint target, uint offset, uint bytes, IntPtr data);

        [DllImport(GL_DLL, EntryPoint = "glDeleteBuffers")]
        public static extern void GLDeleteBuffers(int count, ref int buffers);
        
        [DllImport(GL_DLL, EntryPoint = "glDrawElements")]
        public static extern void GLDrawElements(uint mode, int count, uint type, int indices);

        [DllImport(GL_DLL, EntryPoint = "glEnableVertexAttribArray")]
        public static extern void GLEnableVertexAttribArray(uint location);
        
        [DllImport(GL_DLL, EntryPoint = "glDisableVertexAttribArray")]
        public static extern void GLDisableVertexAttribArray(uint location);

        [DllImport(GL_DLL, EntryPoint = "glVertexAttribPointer")]
        public static extern void GLVertexAttribPointer(uint location, int size, uint type, bool normalized, int stride, IntPtr pointer);

        [DllImport(GL_DLL, EntryPoint = "glUseProgram")]
        public static extern void GLUseProgram(uint program);

        [DllImport(GL_DLL, EntryPoint = "glGetUniformLocation")]
        public static extern uint GLGetUniformLocation(uint program, char[] name);

        [DllImport(GL_DLL, EntryPoint = "glUniformMatrix3fv")]
        public static extern void GLUniformMatrix3fv(uint location, IntPtr data);

        [DllImport(GL_DLL, EntryPoint = "glUniform1f")]
        public static extern void GLUniformMatrix3fv(uint location, float data);

        [DllImport(GL_DLL, EntryPoint = "glCreateShader")]
        public static extern uint GLCreateShader(uint type);

        [DllImport(GL_DLL, EntryPoint = "glShaderSource")]
        public static extern void GLShaderSource(uint shader, int count, ref char[] source, ref int length);

        [DllImport(GL_DLL, EntryPoint = "glCompileShader")]
        public static extern void GLCompileShader(uint shader);

        [DllImport(GL_DLL, EntryPoint = "glGetShaderiv")]
        public static extern void GLGetShaderiv(uint shader, uint pname, ref int param);

        [DllImport(GL_DLL, EntryPoint = "glGetShaderInfoLog")]
        public static extern void GLGetShaderInfoLog(uint shader, int maxLength, ref int length, char[] infoLog);

        [DllImport(GL_DLL, EntryPoint = "glDeleteShader")]
        public static extern void GLDeleteShader(uint shader);

        [DllImport(GL_DLL, EntryPoint = "glCreateProgram")]
        public static extern uint GLCreateProgram();
        
        [DllImport(GL_DLL, EntryPoint = "glAttachShader")]
        public static extern void GLAttachShader(uint program, uint shader);

        [DllImport(GL_DLL, EntryPoint = "glGetProgramiv")]
        public static extern void GLGetProgramiv(uint program, uint pname, ref int param);
        
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
