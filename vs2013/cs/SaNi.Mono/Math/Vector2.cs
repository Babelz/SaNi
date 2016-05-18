using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector2
    {
        #region Fields
        public const int Components = 2;

        public float x;
        public float y;
        #endregion

        #region Properties
        public float LengthSquared
        {
            get 
            {
                return x * x + y * y;
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

        public static Vector2 Zero
        {
            get
            {
                return new Vector2(0.0f);
            }
        }
        public static Vector2 One
        {
            get
            {
                return new Vector2(1.0f);
            }
        }
        public static Vector2 UnitX
        {
            get
            {
                return new Vector2(1.0f, 0.0f);
            }
        }
        public static Vector2 UnitY
        {
            get
            {
                return new Vector2(0.0f, 1.0f);
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
                else            return y;
            }
        }
        #endregion

        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }
        public Vector2(float value)
        {
            x = value;
            y = value;
        }

        /*
            TODO: do performance tests with inline versions. 
         */

        public static Vector2 Normalize(Vector2 vector)
        {
            var length = vector.Length;

            return new Vector2(vector.x / length, vector.y / length);
        }
        public static float Dot(Vector2 lhs, Vector2 rhs)
        {
            Vector2 temp = lhs * rhs;

            return temp.x + temp.y;
        }

        public static bool operator ==(Vector2 lhs, Vector2 rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }
        public static bool operator !=(Vector2 lhs, Vector2 rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator <(Vector2 lhs, Vector2 rhs)
        {
            return lhs.x < rhs.x && lhs.y < rhs.y;
        }
        public static bool operator >(Vector2 lhs, Vector2 rhs)
        {
            return lhs.x > rhs.x && lhs.y > rhs.y;
        }

        public static bool operator <=(Vector2 lhs, Vector2 rhs)
        {
            return lhs.x <= rhs.x && lhs.y <= rhs.y;
        }
        public static bool operator >=(Vector2 lhs, Vector2 rhs)
        {
            return lhs.x >= rhs.x && lhs.y >= rhs.y;
        }
        
        public static Vector2 operator *(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x * rhs.x, lhs.y * rhs.y);
        }
        public static Vector2 operator +(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
        }
        public static Vector2 operator -(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
        }
        public static Vector2 operator /(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.x / rhs.x, lhs.y / rhs.y);
        }

        public static Vector2 operator *(Vector2 lhs, float rhs)
        {
            return new Vector2(lhs.x * rhs, lhs.y * rhs);
        }
        public static Vector2 operator /(Vector2 lhs, float rhs)
        {
            return new Vector2(lhs.x / rhs, lhs.y / rhs);
        }

        public static Vector2 operator -(Vector2 vector)
        {
            return new Vector2(-vector.x, -vector.y);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;

            if (obj.GetType() == typeof(Vector2))
            {
                Vector2 other = (Vector2)obj;

                return this == other;
            }

            return false;
        }
        public override int GetHashCode()
        {
            return x.GetHashCode() + y.GetHashCode();
        }
        public override string ToString()
        {
            return string.Format("x: {0} - y: {1}", x, y);
        }
    }
}