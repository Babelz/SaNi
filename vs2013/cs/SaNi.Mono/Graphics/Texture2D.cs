using SaNi.Mono.Content;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public sealed class Texture2D : ITexture, IResource
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

        private Texture2D()
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetWidth();
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetHeight();
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetID();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern bool InternalGetDisposed();
    }
}
