using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders
{
    internal static class DefaultShaderSources
    {
        public static string DefaultVertexShaderSource()
        {
            return File.ReadAllText("Default shaders\\default vertex.txt");
        }

        public static string DefaultFragmentShaderSource()
        {
            return File.ReadAllText("Default shaders\\default fragment.txt");
        }
    }
}
