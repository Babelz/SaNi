using SaNi.Mono.Resource;
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
                var value = 0;

                GetWidth(ref value);

                return value;
            }
        }
        public int Height
        {
            get
            {
                var value = 0;

                GetHeight(ref value);

                return value;
            }
        }
        public int ID
        {
            get
            {
                var value = 0;

                GetID(ref value);

                return value;
            }
        }
        public bool Disposed
        {
            get
            {
                var value = false;

                GetDisposed(ref value);

                return value;
            }
        }
        #endregion

        private Texture2D()
        {
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetWidth(ref int value);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetHeight(ref int value);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetID(ref int value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetDisposed(ref bool value);

        public override int GetHashCode()
        {
            return ID.GetHashCode();
        }
        public override string ToString()
        {
            Console.WriteLine("TOSTER");
            return string.Format("TEX2D w: {0} - h: {1} - id: {2}", Width, Height, ID);
        }
    }
}
