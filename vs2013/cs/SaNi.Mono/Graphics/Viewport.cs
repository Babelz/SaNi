using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    /// <summary>
    /// Viewport of the device.
    /// </summary>
    public struct Viewport
    {
        #region Fields
        public int x;
        public int y;

        public uint width;
        public uint height;
        #endregion

        public Viewport(int x, int y, uint width, uint height)
        {
            this.x = x;
            this.y = y;

            this.width = width;
            this.height = height;
        }

        public static Viewport Empty()
        {
            return new Viewport(0, 0, 0, 0);
        }
    }
}
