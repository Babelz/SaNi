using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders
{
    internal enum ShaderType 
    {
        Vertex,
        Fragment
    }

    internal sealed class Shader
    {
        #region Properties
        string Source
        {
            get;
            set;
        }
        #endregion

        public Shader(string source, ShaderType type)
        {
        }

        void Compile()
        {
        }

        public void Bind()
        {
        }
        public void Unbind()
        {
        }

        public bool Valid()
        {
            return true;
        }

        public string[] GetLastErrors()
        {
            return null;
        }
    }
}
