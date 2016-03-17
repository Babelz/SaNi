using OpenTK.Graphics.OpenGL4;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor
{
    internal static class Assert
    {
        public static void GLAssert()
        {
#if DEBUG
            var error = GL.GetError();

            if (error != ErrorCode.NoError) throw new Exception("gl assertion failure, " + "\"" + Enum.GetName(typeof(ErrorCode), error) + "\"");
#endif
        }
    }
}
