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
        public float W;
        public float H;
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
                return X + W;
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
                return Y + H;
            }
        }
        #endregion

        public Rectf(float x, float y, float w, float h)
        {
            X = x;
            Y = y;
            W = w;
            H = h;
        }
    }
}
