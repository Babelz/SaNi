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
        private static readonly Recti empty;

        public int x;
        public int y;
        public int width;
        public int height;
        #endregion

        #region Properties
        public int Left
        {
            get
            {
                return x;
            }
        }
        public int Right
        {
            get
            {
                return x + width;
            }
        }
        public int Top
        {
            get
            {
                return y;
            }
        }
        public int Bottom
        {
            get
            {
                return y + height;
            }
        }
        #endregion

        static Recti()
        {
            empty = new Recti(0, 0, 0, 0);
        }

        public Recti(int x, int y, int width, int height)
        {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
        }

        public static Recti Empty()
        {
            return empty;
        }
    }
}
