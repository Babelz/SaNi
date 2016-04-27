using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Rectf
    {   
        #region Fields
        public float x;
        public float y;
        public float width;
        public float height;
        #endregion

        #region Properties
        public float Left
        {
            get
            {
                return x;
            }
        }
        public float Right
        {
            get
            {
                return x + width;
            }
        }
        public float Top
        {
            get
            {
                return y;
            }
        }
        public float Bottom
        {
            get
            {
                return y + height;
            }
        }
        #endregion

        public Rectf(float x, float y, float width, float height)
        {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
        }
    }
}
