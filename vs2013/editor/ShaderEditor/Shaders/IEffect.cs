using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders
{
    public interface IEffect
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

        void Bind();
        void Unbind();

        bool Compile();

        void SetUniformValue(string name, object value, Type type);

        bool HasErrors();
    }
}
