using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders
{
    public interface IEffectCompiler
    {
        #region Properties
        string LastVertexError
        {
            get;
        }
        string LastFragmentError
        {
            get;
        }
        #endregion

        IEffect Compile(string vertexShaderSource, string fragmentShaderSource);

        bool HasErrors();
    }
}
