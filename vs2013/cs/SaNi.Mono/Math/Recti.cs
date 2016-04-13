using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    public struct Recti
    {
        #region Fields
        public int X;
        public int Y;
        public int Width;
        public int Height;
        #endregion

        #region Properties
        public int Left
        {
            get
            {
                return X;
            }
        }
        public int Right
        {
            get
            {
                return X + Width;
            }
        }
        public int Top
        {
            get
            {
                return Y;
            }
        }
        public int Bottom
        {
            get
            {
                return Y + Height;
            }
        }
        #endregion

        public Recti(int x, int y, int width, int height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }
    }
}
