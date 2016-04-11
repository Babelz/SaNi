using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public abstract class Texture : GraphicsResource
    {
        #region Properties
        public int Width
        {
            get
            {
                return InternalGetWidth();
            }
        }
        public int Height
        {
            get
            {
                return InternalGetHeight();
            }
        }
        #endregion

        public Texture()
            : base()
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetWidth();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetHeight();
    }
}
