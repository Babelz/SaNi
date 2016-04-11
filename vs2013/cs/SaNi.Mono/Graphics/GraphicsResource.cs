using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public abstract class GraphicsResource
    {
        /*
            TODO: add internal calls.
            TODO: make device impl.
         */

        #region Fields
        public int ID
        {
            get
            {
                return InternalGetID();
            }
        }
        public bool Disposed
        {
            get
            {
                return InternalGetDisposed();
            }
        }
        #endregion

        public GraphicsResource()
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern bool InternalGetDisposed();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetID();
    }
}
