using OpenTK.Graphics.OpenGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders.OpenGL
{
    public sealed class GLEffectCompiler : IEffectCompiler
    {
        #region Properties
        public string LastVertexError
        {
            get;
            private set;
        }
        public string LastFragmentError
        {
            get;
            private set;
        }
        #endregion

        public GLEffectCompiler()
        {
        }

        public IEffect Compile(string vertexSource, string fragmentSource)
        {
            LastVertexError = string.Empty;
            LastFragmentError = string.Empty;

            var vertex = GL.CreateShader(ShaderType.VertexShader);
            var fragment = GL.CreateShader(ShaderType.FragmentShader);

            GL.ShaderSource(vertex, vertexSource);
            GL.ShaderSource(fragment, fragmentSource);

            GL.CompileShader(vertex);
            GL.CompileShader(fragment);

            // Store errors.
            var vertexStatus = 0;
            var fragmenStatus = 0;

            GL.GetShader(vertex, ShaderParameter.CompileStatus, out vertexStatus);
            GL.GetShader(fragment, ShaderParameter.CompileStatus, out fragmenStatus);

            if (vertexStatus == 0) LastVertexError = GL.GetShaderInfoLog(vertex);

            if (fragmenStatus == 0) LastFragmentError = GL.GetShaderInfoLog(fragment);

            if (vertexStatus == 0 || fragmenStatus == 0) return null;

            var program = GL.CreateProgram();

            GL.AttachShader(program, vertex);
            GL.AttachShader(program, fragment);

            GL.LinkProgram(program);

            GL.DeleteShader(vertex);
            GL.DeleteShader(fragment);

            return new GLEffect(program);
        }
        public bool HasErrors()
        {
            return !string.IsNullOrEmpty(LastFragmentError) || !string.IsNullOrEmpty(LastVertexError);
        }
    }
}
