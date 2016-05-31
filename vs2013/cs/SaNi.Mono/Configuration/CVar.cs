using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Configuration
{
    public sealed class CVar
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
        private extern void ReadString(ref string value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void ReadInt(ref int value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void ReadFloat(ref float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void ReadDouble(ref double value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern bool InternalWrite(ref object value, string typeName);

        public object Read()
        {
            switch (ValueType)
            {
                case CVarValueType.StringVal:
                    var str = string.Empty;

                    ReadString(ref str);

                    return str;
                case CVarValueType.IntVal:
                    var ival = 0;

                    ReadInt(ref ival);

                    return ival;
                case CVarValueType.FloatVal:
                    var fval = 0.0f;

                    ReadFloat(ref fval);

                    return fval;
                case CVarValueType.DoubleVal:
                    var dval = 0.0;

                    ReadDouble(ref dval);

                    return dval;
                default:
                    break;
            }

            return null;
        }
        public bool Write(object value)
        {
            if (value.GetType() == typeof(int)      && ValueType != CVarValueType.IntVal)       return false;
            if (value.GetType() == typeof(string)   && ValueType != CVarValueType.StringVal)    return false;
            if (value.GetType() == typeof(float)    && ValueType != CVarValueType.FloatVal)     return false;
            if (value.GetType() == typeof(double)   && ValueType != CVarValueType.DoubleVal)    return false;

            return InternalWrite(ref value, value.GetType().Name.ToLower());
        }

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

        public override string ToString()
        {
            var sb = new StringBuilder();

            sb.Append("\t-- CVar -- \n");
            sb.Append(string.Format("Name: {0}\n", Name));
            sb.Append(string.Format("ValueType: {0}\n", ValueType.ToString()));
            sb.Append(string.Format("CanWrite: {0}\n", CanWrite));
            sb.Append(string.Format("Value: {0}\n", Read().ToString()));

            return sb.ToString();
        }
        public override int GetHashCode()
        {
            return Name.GetHashCode();
        }
    }
}
