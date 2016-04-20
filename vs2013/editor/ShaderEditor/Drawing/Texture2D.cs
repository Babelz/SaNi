using OpenTK.Graphics.OpenGL4;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Drawing
{
    public sealed class Texture2D : ITexture2D
    {
        #region Properties
        public int ID
        {
            get;
            private set;
        }
        public int Width
        {
            get;
            private set;
        }
        public int Height
        {
            get;
            private set;
        }
        #endregion

        private Texture2D(int id, int width, int height)
        {
            ID = id;
            Width = width;
            Height = height;
        }

        public void Bind()
        {
            GL.BindTexture(TextureTarget.Texture2D, ID);
        }
        public void Unbind()
        {
            GL.BindTexture(TextureTarget.Texture2D, 0);
        }

        public static Texture2D LoadFromFile(string filename)
        {
            var id = 0;

            id = GL.GenTexture();
            GL.BindTexture(TextureTarget.Texture2D, id);

            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMinFilter, (int)TextureMinFilter.Linear);
            GL.TexParameter(TextureTarget.Texture2D, TextureParameterName.TextureMagFilter, (int)TextureMinFilter.Linear);

            var bmp = new Bitmap(filename);
            var bmpData = bmp.LockBits(new Rectangle(0, 0, bmp.Width, bmp.Height), System.Drawing.Imaging.ImageLockMode.ReadOnly, System.Drawing.Imaging.PixelFormat.Format32bppArgb);

            GL.TexImage2D(TextureTarget.Texture2D, 0, PixelInternalFormat.Rgba, bmpData.Width, bmpData.Height, 0, PixelFormat.Bgra, PixelType.UnsignedByte, bmpData.Scan0);

            return new Texture2D(id, bmp.Width, bmp.Height);
        }
    }
}
