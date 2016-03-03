﻿using OpenTK.Graphics.OpenGL4;
using ShaderEditor.Shaders;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Rendering
{
    internal sealed class SpriteBatch
    {
        #region Const fields
        private const int MaxSpritesCount       = 1024;
        private const int VertexElementsCount   = 9;
        private const int IndicesPerSprite      = 6;
        private const int VerticesPerSprite     = 4;

        private const int PositionLocation      = 0;
        private const int ColorLocation         = 1;
        private const int UVLocation            = 2;
        #endregion

        #region Fields
        private readonly float[] vertexBufferData;
        private readonly int[] sprites;
        
        private int vertexBuffer;
        private int indexBuffer;

        private int vertexBufferPointer;
        private int spritePointer;
        
        private Effect effect;
        #endregion

        public SpriteBatch()
        {
            vertexBufferData = new float[MaxSpritesCount * VertexElementsCount];
            sprites = new int[MaxSpritesCount];
        }

        private void UpdateVertexBufferData()
        {
            var vertexDataPointer = Marshal.AllocHGlobal(sizeof(float) * vertexBufferData.Length);

            Marshal.Copy(vertexBufferData, 0, vertexDataPointer, vertexBufferData.Length);

            GL.BufferSubData(BufferTarget.ArrayBuffer, IntPtr.Zero, new IntPtr(sizeof(float) * vertexBufferData.Length), vertexDataPointer);

            Marshal.FreeHGlobal(vertexDataPointer);
        }

        private void CreateVertexBuffer()
        {
            vertexBuffer = GL.GenBuffer();

            GL.BufferData(BufferTarget.ArrayBuffer, new IntPtr(MaxSpritesCount * sizeof(float)), IntPtr.Zero, BufferUsageHint.DynamicDraw);
        }
        private void CreateIndexBuffer()
        {
            var indicesCount = MaxSpritesCount * IndicesPerSprite;

            var indices = new int[MaxSpritesCount * VertexElementsCount];
            var indexPointer = 0;

            for (int i = 0; i < indicesCount; i += VerticesPerSprite)
            {
                indices[indexPointer++] = i;
                indices[indexPointer++] = i + 1;
                indices[indexPointer++] = i + 2;

                indices[indexPointer++] = i + 1;
                indices[indexPointer++] = i + 3;
                indices[indexPointer++] = i + 2;
            }

            indexBuffer = GL.GenBuffer();

            var indexDataPointer = Marshal.AllocHGlobal(sizeof(int) * indices.Length);

            Marshal.Copy(indices, 0, indexDataPointer, indices.Length);

            GL.BufferData(BufferTarget.ElementArrayBuffer, new IntPtr(MaxSpritesCount * sizeof(int)), indexDataPointer, BufferUsageHint.DynamicDraw);

            Marshal.FreeHGlobal(indexDataPointer);
        }
        private void CreatePipeline()
        {
            GL.EnableVertexAttribArray(PositionLocation);
            GL.EnableVertexAttribArray(ColorLocation);
            GL.EnableVertexAttribArray(UVLocation);

            GL.VertexAttribPointer(PositionLocation, 3, VertexAttribPointerType.Float, false, sizeof(float) * 9, 0);
            GL.VertexAttribPointer(ColorLocation, 4, VertexAttribPointerType.Float, false, sizeof(float) * 9, sizeof(float) * 3);
            GL.VertexAttribPointer(UVLocation, 2, VertexAttribPointerType.Float, false, sizeof(float) * 9, sizeof(float) * 7);
        }
        public void Initialize()
        {
            CreateVertexBuffer();
            CreateIndexBuffer();
            CreatePipeline();
        }
        public void Cleanup()
        {
            GL.DisableVertexAttribArray(PositionLocation);
            GL.DisableVertexAttribArray(ColorLocation);
            GL.DisableVertexAttribArray(UVLocation);

            GL.DeleteBuffer(vertexBuffer);
            GL.DeleteBuffer(indexBuffer);
        }

        public void Begin(Effect effect)
        {
            Debug.Assert(effect != null);

            this.effect = effect;

            vertexBufferPointer = 0;
            spritePointer = 0;
        }

        public void Draw(Sprite sprite)
        {
            sprites[spritePointer++] = sprite.Texture.ID;

            Debug.Assert(spritePointer < MaxSpritesCount);

            foreach (var vpct in sprite.RenderData.VertexData) vpct.CopyData(vertexBufferData, ref vertexBufferPointer);
        }

        public void End()
        {
        }
    }
}
