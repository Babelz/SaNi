using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    public struct Vector2
    {
        #region Fields
        public const int Components = 2;

        public float X;
        public float Y;
        #endregion

        #region Properties
        public float LengthSquared
        {
            get 
            {
                return X * X + Y * Y;
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

                if (index == 0) return X;
                else            return Y;
            }
        }
        #endregion

        public Vector2(float x, float y)
        {
            X = x;
            Y = y;
        }
        public Vector2(float value)
        {
            X = value;
            Y = value;
        }

        /*
            TODO: do performance tests with inline versions. 
         */

        public static Vector2 Normalize(Vector2 vector)
        {
            var length = vector.Length;

            return new Vector2(vector.X / length, vector.Y / length);
        }
        public static float Dot(Vector2 lhs, Vector2 rhs)
        {
            Vector2 temp = lhs * rhs;

            return temp.X + temp.Y;
        }

        public static bool operator ==(Vector2 lhs, Vector2 rhs)
        {
            return lhs.X == rhs.X && lhs.Y == rhs.Y;
        }
        public static bool operator !=(Vector2 lhs, Vector2 rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator <(Vector2 lhs, Vector2 rhs)
        {
            return lhs.X < rhs.X && lhs.Y < rhs.Y;
        }
        public static bool operator >(Vector2 lhs, Vector2 rhs)
        {
            return lhs.X > rhs.X && lhs.Y > rhs.Y;
        }

        public static bool operator <=(Vector2 lhs, Vector2 rhs)
        {
            return lhs.X <= rhs.X && lhs.Y <= rhs.Y;
        }
        public static bool operator >=(Vector2 lhs, Vector2 rhs)
        {
            return lhs.X >= rhs.X && lhs.Y >= rhs.Y;
        }
        
        public static Vector2 operator *(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.X * rhs.X, lhs.Y * rhs.Y);
        }
        public static Vector2 operator +(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.X + rhs.X, lhs.Y + rhs.Y);
        }
        public static Vector2 operator -(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.X - rhs.X, lhs.Y - rhs.Y);
        }
        public static Vector2 operator /(Vector2 lhs, Vector2 rhs)
        {
            return new Vector2(lhs.X / rhs.X, lhs.Y / rhs.Y);
        }

        public static Vector2 operator *(Vector2 lhs, float rhs)
        {
            return new Vector2(lhs.X * rhs, lhs.Y * rhs);
        }
        public static Vector2 operator /(Vector2 lhs, float rhs)
        {
            return new Vector2(lhs.X / rhs, lhs.Y / rhs);
        }

        public static Vector2 operator -(Vector2 vector)
        {
            return new Vector2(-vector.X, -vector.Y);
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
            return X.GetHashCode() + Y.GetHashCode();
        }
    }
}