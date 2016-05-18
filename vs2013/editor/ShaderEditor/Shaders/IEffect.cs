using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders
{
    public interface IEffect
    {
        void Bind();
        void Unbind();

        void SetUniformValue(string name, object value, Type type);
    }
}
