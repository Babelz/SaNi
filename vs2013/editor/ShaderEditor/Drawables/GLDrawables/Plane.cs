using OpenTK;
using OpenTK.Graphics.OpenGL4;
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
        private static readonly IntPtr IndexBufferBytesCount   = new IntPtr(sizeof(byte) * 6);

        private static readonly byte[] Indices = new byte[]
        {
            0, 1, 2,
            1, 3, 2
        };
        #endregion

        #region Fields
        private readonly VertexPositionColorTexture[] vertices;

        private readonly Transform transform;

        private int vertexBuffer;
        private int vertexArray;
        private int indexBuffer;

        private Texture2D texture;
        #endregion

        #region Properties
        public Color Color
        {
            get;
            set;
        }
        public Texture2D Texture
        {
            get
            {
                return texture;
            }
            set
            {
                texture = value;

                if (texture == null) return;

                transform.size.X = texture.Width;
                transform.size.Y = texture.Height;
            }
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

            InitializeVertexPointers();
            BindBuffers();
            UpdateBuffersData();

            Texture.Bind();
        }
        private void UpdateVertices()
        {
            var color = new Vector4(Color.R / 255.0f, Color.G / 255.0f, Color.B / 255.0f, Color.A / 255.0f);

            var topLeft = new VertexPositionColorTexture();
            topLeft.position.X = -1.0f;//transform.position.X;
            topLeft.position.Y = 1.0f;//transform.position.Y;
            topLeft.uv.X = 0.0f;
            topLeft.uv.Y = 1.0f;
            topLeft.color = color;

            var topRight = new VertexPositionColorTexture();
            topRight.position.X = 1.0f;//transform.position.X + transform.size.X * transform.scale.X;
            topRight.position.Y = 1.0f;//transform.position.Y;
            topRight.uv.X = 1.0f;
            topRight.uv.Y = 1.0f;
            topRight.color = color;

            var bottomLeft = new VertexPositionColorTexture();
            bottomLeft.position.X = -1.0f;//transform.position.X;
            bottomLeft.position.Y = -1.0f;//transform.position.Y + transform.size.Y * transform.scale.Y;
            bottomLeft.uv.X = 0.0f;
            bottomLeft.uv.Y = 0.0f;
            bottomLeft.color = color;

            var bottomRight = new VertexPositionColorTexture();
            bottomRight.position.X = 1.0f;//transform.position.X + transform.size.X * transform.scale.X;
            bottomRight.position.Y = -1.0f;//transform.position.Y + transform.size.Y * transform.scale.Y;
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
            GL.BindBuffer(BufferTarget.ArrayBuffer, vertexBuffer);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, indexBuffer);
            Assert.GLAssert();
        }
        private void UpdateBuffersData()
        {
            GL.BindVertexArray(vertexArray);
            Assert.GLAssert();

            var verticesData = new List<float>();

            foreach (var vpct in vertices)
            {
                verticesData.Add(vpct.position.X);
                verticesData.Add(vpct.position.Y);
                verticesData.Add(vpct.position.Z);

                verticesData.Add(vpct.color.X);
                verticesData.Add(vpct.color.Y);
                verticesData.Add(vpct.color.Z);
                verticesData.Add(vpct.color.W);

                verticesData.Add(vpct.uv.X);
                verticesData.Add(vpct.uv.Y);
            }

            GL.BufferSubData(BufferTarget.ArrayBuffer, IntPtr.Zero, VertexBufferBytesCount, verticesData.ToArray());
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
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            GL.BindBuffer(BufferTarget.ElementArrayBuffer, 0);
            Assert.GLAssert();
        
            GL.BindVertexArray(0);
            Assert.GLAssert();
        }
        private void UnbindBuffers()
        {
            GL.DisableVertexAttribArray(0);
            GL.DisableVertexAttribArray(1);
            GL.DisableVertexAttribArray(2);
            Assert.GLAssert();
        }

        public void Draw(float delta)
        {
            if (Texture == null) return;

            BeginDraw();

            GL.DrawElements(BeginMode.Triangles, 6, DrawElementsType.UnsignedByte, 0);
            Assert.GLAssert();

            EndDraw();

            //var VertexArrayID = GL.GenVertexArray();
            //GL.BindVertexArray(VertexArrayID);

            //var g_vertex_buffer_data = new[]{
            //   new Vector3(-1.0f, -1.0f, 0.0f),
            //   new Vector3(1.0f, -1.0f, 0.0f),
            //   new Vector3(0.0f,  1.0f, 0.0f),
            //};

            //// This will identify our vertex buffer
            //var vertexbuffer = GL.GenBuffer();
            //// The following commands will talk about our 'vertexbuffer' buffer
            //GL.BindBuffer(BufferTarget.ArrayBuffer, vertexbuffer);
            //// Give our vertices to OpenGL.
            //GL.BufferData(BufferTarget.ArrayBuffer, new IntPtr(sizeof(float) * 9), g_vertex_buffer_data, BufferUsageHint.StaticDraw);

            //GL.EnableVertexAttribArray(0);
            //GL.BindBuffer(BufferTarget.ArrayBuffer, vertexbuffer);
            //GL.VertexAttribPointer(
            //   0,
            //   3,                  // size
            //   VertexAttribPointerType.Float,           // type
            //   false,           // normalized?
            //   sizeof(float) * 3,                  // stride
            //   sizeof(float) * 1            // array buffer offset
            //);

            //// Draw the triangle !
            //GL.DrawArrays(PrimitiveType.Triangles, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
            //GL.DisableVertexAttribArray(0);
        }
    }
}
