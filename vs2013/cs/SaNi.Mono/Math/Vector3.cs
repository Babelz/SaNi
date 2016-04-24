using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    public struct Vector3
    {
        #region Fields
        public const int Components = 3;

        public float x;
        public float y;
        public float z;
        #endregion

        #region Properties
        public float LengthSquared
        {
            get 
            {
                return x * x + y * y + z * z;
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

        public static Vector3 Zero
        {
            get
            {
                return new Vector3(0.0f);
            }
        }
        public static Vector3 One
        {
            get
            {
                return new Vector3(1.0f);
            }
        }
        public static Vector3 UnitX
        {
            get
            {
                return new Vector3(1.0f, 0.0f);
            }
        }
        public static Vector3 UnitY
        {
            get
            {
                return new Vector3(0.0f, 1.0f);
            }
        }
        public static Vector3 UnitZ
        {
            get
            {
                return new Vector3(0.0f, 0.0f, 1.0f);
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
                else            return z;
            }
        }
        #endregion

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        public Vector3(float x, float y)
        {
            this.x = x;
            this.y = y;
            z = 0.0f;
        }
        public Vector3(float value)
        {
            x = value;
            y = value;
            z = value;
        }

        /*
            TODO: do performance tests with inline versions. 
         */

        public static Vector3 Normalize(Vector3 vector)
        {
            var length = vector.Length;

            return new Vector3(vector.x / length, vector.y / length, vector.z / length);
        }
        public static float Dot(Vector3 lhs, Vector3 rhs)
        {
            Vector3 temp = lhs * rhs;

            return temp.x + temp.y + temp.z;
        }

        public static bool operator ==(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
        }
        public static bool operator !=(Vector3 lhs, Vector3 rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator <(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z;
        }
        public static bool operator >(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z;
        }

        public static bool operator <=(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x <= rhs.x && lhs.y <= rhs.y && lhs.z <= rhs.z;
        }
        public static bool operator >=(Vector3 lhs, Vector3 rhs)
        {
            return lhs.x >= rhs.x && lhs.y >= rhs.y && lhs.z >= rhs.z;
        }
        
        public static Vector3 operator *(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
        }
        public static Vector3 operator +(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }
        public static Vector3 operator -(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }
        public static Vector3 operator /(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
        }

        public static Vector3 operator *(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
        }
        public static Vector3 operator /(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
        }

        public static Vector3 operator -(Vector3 vector)
        {
            return new Vector3(-vector.x, -vector.y, -vector.z);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;

            if (obj.GetType() == typeof(Vector3))
            {
                Vector3 other = (Vector3)obj;

                return this == other;
            }

            return false;
        }
        public override int GetHashCode()
        {
            return x.GetHashCode() + y.GetHashCode() + z.GetHashCode();
        }
    }
}
