using OpenTK;
using OpenTK.Graphics.OpenGL;
using ShaderEditor.Drawing;
using ShaderEditor.Shaders;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Drawables.GLDrawables
{
    public sealed class Plane : IDrawable
    {
        #region Static fields
        private static readonly IntPtr VertexBufferBytesCount  = new IntPtr(sizeof(float) * 9 * 4);
        private static readonly IntPtr IndexBufferBytesCount   = new IntPtr(sizeof(uint) * 6);

        private static readonly uint[] Indices = new uint[]
        {
            0, 1, 2,
            2, 1, 3
        };
        #endregion

        #region Fields
        private readonly VertexPositionColorTexture[] vertices;

        private readonly Transform transform;

        private int vertexBuffer;
        private int vertexArray;
        private int indexBuffer;
        #endregion

        #region Properties
        public Color Color
        {
            get;
            set;
        }
        public Texture2D Texture
        {
            get;
            set;
        }
        public Transform Transform
        {
            get
            {
                return transform;
            }
        }
        #endregion

        public Plane()
        {
            vertices  = new VertexPositionColorTexture[4];
            transform = new Transform();
            Color = Color.Red;

            GenerateBuffers();

            transform.scale = Vector2.One;
            transform.position = Vector2.Zero;
        }

        private void GenerateBuffers()
        {
            vertexBuffer = GL.GenBuffer();
            vertexArray = GL.GenVertexArray();
            indexBuffer = GL.GenBuffer();

            GL.BindVertexArray(vertexArray);

            GL.BindBuffer(BufferTarget.ArrayBuffer, vertexBuffer);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, indexBuffer);
            Assert.GLAssert();

            GL.BufferData(BufferTarget.ArrayBuffer, VertexBufferBytesCount, vertices, BufferUsageHint.DynamicDraw);
            GL.BufferData(BufferTarget.ElementArrayBuffer, IndexBufferBytesCount, Indices, BufferUsageHint.StaticDraw);
            Assert.GLAssert();

            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
            Assert.GLAssert();

            GL.BindVertexArray(0);
        }

        private void BeginDraw()
        {
            UpdateVertices();

            BindBuffers();
            InitializeVertexPointers();
            UpdateBuffersData();

            Texture.Bind();
        }
        private void UpdateVertices()
        {
            var color = new Vector4(Color.R / 255.0f, Color.G / 255.0f, Color.B / 255.0f, Color.A / 255.0f);

            var topLeft = new VertexPositionColorTexture();
            topLeft.position.X = transform.position.X - transform.origin.X;
            topLeft.position.Y = -transform.position.Y - transform.origin.Y;
            topLeft.uv.X = 0.0f;
            topLeft.uv.Y = 1.0f;
            topLeft.color = color;

            var topRight = new VertexPositionColorTexture();
            topRight.position.X = transform.position.X + transform.size.X * transform.scale.X - transform.origin.X;
            topRight.position.Y = -transform.position.Y - transform.origin.Y;
            topRight.uv.X = 1.0f;
            topRight.uv.Y = 1.0f;
            topRight.color = color;

            var bottomLeft = new VertexPositionColorTexture();
            bottomLeft.position.X = transform.position.X - transform.origin.X;
            bottomLeft.position.Y = -transform.position.Y + transform.size.Y * transform.scale.Y - transform.origin.Y;
            bottomLeft.uv.X = 0.0f;
            bottomLeft.uv.Y = 0.0f;
            bottomLeft.color = color;

            var bottomRight = new VertexPositionColorTexture();
            bottomRight.position.X = transform.position.X + transform.size.X * transform.scale.X - transform.origin.X;
            bottomRight.position.Y = -transform.position.Y + transform.size.Y * transform.scale.Y - transform.origin.Y;
            bottomRight.uv.X = 1.0f;
            bottomRight.uv.Y = 0.0f;
            bottomRight.color = color;

            vertices[0] = topLeft;
            vertices[1] = topRight;
            vertices[2] = bottomLeft;
            vertices[3] = bottomRight;
        }
        private void InitializeVertexPointers()
        {
            GL.BindVertexArray(vertexArray);
            Assert.GLAssert();

            GL.EnableVertexAttribArray(0);
            GL.EnableVertexAttribArray(1);
            GL.EnableVertexAttribArray(2);
            Assert.GLAssert();

            GL.VertexAttribPointer(0, 3, VertexAttribPointerType.Float, false, sizeof(float) * 9, 0);
            GL.VertexAttribPointer(1, 4, VertexAttribPointerType.Float, false, sizeof(float) * 9, sizeof(float) * 3);
            GL.VertexAttribPointer(2, 2, VertexAttribPointerType.Float, false, sizeof(float) * 9, sizeof(float) * 7);
            Assert.GLAssert();
        }
        private void BindBuffers()
        {
            GL.BindVertexArray(vertexArray);
            Assert.GLAssert();

            GL.BindBuffer(BufferTarget.ArrayBuffer, vertexBuffer);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, indexBuffer);
            Assert.GLAssert();
        }
        private void UpdateBuffersData()
        {
            GL.BufferSubData(BufferTarget.ArrayBuffer, IntPtr.Zero, VertexBufferBytesCount, vertices);
            Assert.GLAssert();
        }

        private void EndDraw()
        {
            Texture.Unbind();

            DeinitializeVertexPointers();
            UnbindBuffers();
        }
        private void DeinitializeVertexPointers()
        {
            GL.DisableVertexAttribArray(0);
            GL.DisableVertexAttribArray(1);
            GL.DisableVertexAttribArray(2);
            Assert.GLAssert();
        }
        private void UnbindBuffers()
        {
            GL.BindVertexArray(0);
            Assert.GLAssert();

            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
            Assert.GLAssert();
        }

        public void Draw(float delta, float total)
        {
            if (Texture == null) return;

            BeginDraw();

            GL.DrawElements(BeginMode.Triangles, 6, DrawElementsType.UnsignedInt, 0);
            Assert.GLAssert();

            EndDraw();
        }
    }
}
