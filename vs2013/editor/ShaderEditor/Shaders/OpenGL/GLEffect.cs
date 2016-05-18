using OpenTK;
using OpenTK.Graphics.OpenGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Shaders.OpenGL
{
    internal sealed class GLEffect : IEffect
    {
        #region Properties
        public int ProgramID
        {
            get;
            private set;
        }
        #endregion

        public GLEffect(int programID)
        {
            ProgramID = programID;
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

            if (type == typeof(Matrix4))
            {
                var mat4 = (Matrix4)value;

                GL.UniformMatrix4(location, true, ref mat4);
                Assert.GLAssert();
            }
            else if (type == typeof(float))
            {
                GL.Uniform1(location, (float)value);
                Assert.GLAssert();
            }
            else if (type == typeof(Vector2))
            {
                GL.Uniform2(location, (Vector2)value);
                Assert.GLAssert();
            }
            else
            {
                throw new InvalidOperationException("invalid or unsupported uniform type");
            }
        }
    }
}
