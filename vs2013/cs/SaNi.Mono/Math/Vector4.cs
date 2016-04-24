using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    public struct Vector4
    {
        #region Fields
        public const int Components = 4;

        public float x;
        public float y;
        public float z;
        public float w;
        #endregion

        #region Properties
        public float LengthSquared
        {
            get 
            {
                return x * x + y * y + z * z + w * w;
            }
        }
        public float Length
        {
            get
            {
                return (float)System.Math.Sqrt(LengthSquared);
            }
        }
        public bool Normalized
        {
            get
            {
                return (int)LengthSquared == 1;
            }
        }

        public static Vector4 Zero
        {
            get
            {
                return new Vector4(0.0f);
            }
        }
        public static Vector4 One
        {
            get
            {
                return new Vector4(1.0f);
            }
        }
        public static Vector4 UnitX
        {
            get
            {
                return new Vector4(1.0f, 0.0f);
            }
        }
        public static Vector4 UnitY
        {
            get
            {
                return new Vector4(0.0f, 1.0f);
            }
        }
        public static Vector4 UnitZ
        {
            get
            {
                return new Vector4(0.0f, 0.0f, 1.0f);
            }
        }
        public static Vector4 UnitW
        {
            get
            {
                return new Vector4(0.0f, 0.0f, 0.0f, 1.0f);
            }
        }
        #endregion

        #region Indexer
        public float this[int index]
        {
            get
            {
                Debug.Assert(index < Components);

                if (index == 0) return x;
                if (index == 1) return y;
                if (index == 2) return z;
                else            return w;
            }
        }
        #endregion

        public Vector4(float x, float y, float z, float w)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }
        public Vector4(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
            w = 0.0f;
        }
        public Vector4(float x, float y)
        {
            this.x = x;
            this.y = y;
            z = 0.0f;
            w = 0.0f;
        }
        public Vector4(float value)
        {
            x = value;
            y = value;
            z = value;
            w = value;
        }

        /*
            TODO: do performance tests with inline versions. 
         */

        public static Vector4 Normalize(Vector4 vector)
        {
            var length = vector.Length;

            return new Vector4(vector.x / length, vector.y / length, vector.z / length, vector.w / length);
        }
        public static float Dot(Vector4 lhs, Vector4 rhs)
        {
            Vector4 temp = lhs * rhs;

            return temp.x + temp.y + temp.z + temp.w;
        }

        public static bool operator ==(Vector4 lhs, Vector4 rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
        }
        public static bool operator !=(Vector4 lhs, Vector4 rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator <(Vector4 lhs, Vector4 rhs)
        {
            return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w;
        }
        public static bool operator >(Vector4 lhs, Vector4 rhs)
        {
            return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w;
        }

        public static bool operator <=(Vector4 lhs, Vector4 rhs)
        {
            return lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z && lhs.w <= rhs.w;
        }
        public static bool operator >=(Vector4 lhs, Vector4 rhs)
        {
            return lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z && lhs.w >= rhs.w;
        }
        
        public static Vector4 operator *(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
        }
        public static Vector4 operator +(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
        }
        public static Vector4 operator -(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        }
        public static Vector4 operator /(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
        }

        public static Vector4 operator *(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
        }
        public static Vector4 operator /(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
        }

        public static Vector4 operator -(Vector4 vector)
        {
            return new Vector4(-vector.x, -vector.y, -vector.z, -vector.w);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;

            if (obj.GetType() == typeof(Vector4))
            {
                Vector4 other = (Vector4)obj;

                return this == other;
            }

            return false;
        }
        public override int GetHashCode()
        {
            return x.GetHashCode() + y.GetHashCode() + z.GetHashCode() + w.GetHashCode();
        }
    }
}
