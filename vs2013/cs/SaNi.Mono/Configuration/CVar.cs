using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Configuration
{
    private sealed class CVar
    {
        #region Fields
        private uint ptr;
        #endregion

        #region Properties
        public CVarValueType ValueType
        {
            get
            {
                var value = CVarValueType.Null;

                GetValueType(ref value);

                return value;
            }
        }
        public string Name
        {
            get
            {
                var value = string.Empty;

                GetName(ref value);

                return value;
            }
        }
        public bool CanWrite
        {
            get
            {
                var value = false;

                GetCanWrite(ref value);

                return value;
            }
        }
        public bool HasChanged
        {
            get
            {
                var value = false;

                GetHasChanged(ref value);

                return value;
            }
        }
        public bool IsSynced
        {
            get
            {
                var value = false;

                GetIsSynced(ref value);

                return value;
            }
        }
        #endregion

        private CVar(uint ptr)
        {
            this.ptr = ptr;
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern object Read();
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern bool Write(object value);

        #region Internal get methods
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetValueType(ref CVarValueType value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetName(ref string value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetCanWrite(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetHasChanged(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetIsSynced(ref bool value);
        #endregion
    }
}
