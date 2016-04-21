using ShaderEditor.Shaders.OpenGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders
{
    public sealed class EffectCompilers
    {
        #region Fields
        private readonly IEffectCompiler[] compilers;
        #endregion

        public EffectCompilers()
        {
            compilers = new IEffectCompiler[2];
            compilers[(int)ShadingLanguages.GLSL] = new GLEffectCompiler();
            compilers[(int)ShadingLanguages.HLSL] = null;
        }

        public IEffect Compile(ShadingLanguages targetLanguage, string vertexSource, string fragmentSource)
        {
            return compilers[(int)targetLanguage].Compile(vertexSource, fragmentSource);
        }
        public bool HasErrors(ShadingLanguages targetLanguage)
        {
            return compilers[(int)targetLanguage].HasErrors();
        }
        public void GetLastErrors(ShadingLanguages targetLanguage, ref string outVertexError, ref string outFragmentError)
        {
            var compiler = compilers[(int)targetLanguage];

            outVertexError = compiler.LastVertexError;
            outFragmentError = compiler.LastFragmentError;
        }
    }
}
