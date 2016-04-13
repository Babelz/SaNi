using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    public struct Rectf
    {   
        #region Fields
        public float X;
        public float Y;
        public float Width;
        public float Height;
        #endregion

        #region Properties
        public float Left
        {
            get
            {
                return X;
            }
        }
        public float Right
        {
            get
            {
                return X + Width;
            }
        }
        public float Top
        {
            get
            {
                return Y;
            }
        }
        public float Bottom
        {
            get
            {
                return Y + Height;
            }
        }
        #endregion

        public Rectf(float x, float y, float width, float height)
        {
            X = x;
            Y = y;
            Width = width;
            Height = height;
        }
    }
}
