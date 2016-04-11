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
        public int W;
        public int H;
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
                return X + W;
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
                return Y + H;
            }
        }
        #endregion

        public Recti(int x, int y, int w, int h)
        {
            X = x;
            Y = y;
            W = w;
            H = h;
        }
    }
}
