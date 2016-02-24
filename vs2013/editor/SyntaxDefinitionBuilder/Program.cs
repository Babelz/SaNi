using SyntaxDefinitionBuilder.GLSL;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SyntaxDefinitionBuilder
{
    internal sealed class Program
    {
        private static void Main(string[] args)
        {
            GLSLDesktopBuilder builder = new GLSLDesktopBuilder();
            
            var glslDesktopSyntaxDefinition = builder.BuildSyntaxDefinition();

            File.WriteAllLines("paska.xml", glslDesktopSyntaxDefinition);
        }
    }
}
