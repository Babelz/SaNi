using OpenTK.Graphics.OpenGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders
{
    internal sealed class Effect
    {
        #region Properties
        string VertexSource
        {
            get;
            set;
        }
        string FragmentSource
        {
            get;
            set;
        }
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
        public int ProgramID
        {
            get;
            private set;
        }
        #endregion

        public Effect(string vertexSource, string fragmentSource)
        {
            VertexSource = vertexSource;
            FragmentSource = fragmentSource;
        }

        public bool Compile()
        {
            LastVertexError = string.Empty;
            LastFragmentError = string.Empty;

            var vertex = GL.CreateShader(ShaderType.VertexShader);
            var fragment = GL.CreateShader(ShaderType.FragmentShader);

            GL.ShaderSource(vertex, VertexSource);
            GL.ShaderSource(fragment, FragmentSource);

            GL.CompileShader(vertex);
            GL.CompileShader(fragment);

            // Store errors.
            var vertexStatus = 0;
            var fragmenStatus = 0;

            GL.GetShader(vertex, ShaderParameter.CompileStatus, out vertexStatus);
            GL.GetShader(fragment, ShaderParameter.CompileStatus, out fragmenStatus);

            if (vertexStatus == 0) LastVertexError = GL.GetShaderInfoLog(vertex);

            if (fragmenStatus == 0) LastFragmentError = GL.GetShaderInfoLog(fragment);

            if (vertexStatus == 0 || fragmenStatus == 0) return false;

            var program = GL.CreateProgram();

            GL.AttachShader(program, vertex);
            GL.AttachShader(program, fragment);

            GL.LinkProgram(program);

            GL.DeleteShader(vertex);
            GL.DeleteShader(fragment);

            ProgramID = program;

            return true;
        }

        public void Bind()
        {
            if (ProgramID == 0) return;

            GL.UseProgram(ProgramID);
            Assert.GLAssert();
        }
        public void Unbind()
        {
            GL.UseProgram(0);
            Assert.GLAssert();
        }

        public void SetUniformValue(string name, object value, Type type)
        {
            var location = GL.GetUniformLocation(ProgramID, name);
            Assert.GLAssert();

            if (type == typeof(OpenTK.Matrix4))
            {
                var mat4 = (OpenTK.Matrix4)value;

                GL.UniformMatrix4(location, false, ref mat4);
                Assert.GLAssert();
            }
            else if (type == typeof(float))
            {
                GL.Uniform1(location, (float)value);
                Assert.GLAssert();
            }
            else
            {
                throw new InvalidOperationException("invalid or unsupported uniform type");
            }
        }

        public bool HasErrors()
        {
            return !string.IsNullOrEmpty(LastVertexError) || !string.IsNullOrEmpty(LastFragmentError);
        }
    }
}
