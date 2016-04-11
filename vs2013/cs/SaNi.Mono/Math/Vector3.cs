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

        public float X;
        public float Y;
        public float Z;
        #endregion

        #region Properties
        public float LengthSquared
        {
            get 
            {
                return X * X + Y * Y + Z * Z;
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

                if (index == 0) return X;
                if (index == 1) return Y;
                else            return Z;
            }
        }
        #endregion

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }
        public Vector3(float x, float y)
        {
            X = x;
            Y = y;
            Z = 0.0f;
        }
        public Vector3(float value)
        {
            X = value;
            Y = value;
            Z = value;
        }

        /*
            TODO: do performance tests with inline versions. 
         */

        public static Vector3 Normalize(Vector3 vector)
        {
            var length = vector.Length;

            return new Vector3(vector.X / length, vector.Y / length, vector.Z / length);
        }
        public static float Dot(Vector3 lhs, Vector3 rhs)
        {
            Vector3 temp = lhs * rhs;

            return temp.X + temp.Y + temp.Z;
        }

        public static bool operator ==(Vector3 lhs, Vector3 rhs)
        {
            return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
        }
        public static bool operator !=(Vector3 lhs, Vector3 rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator <(Vector3 lhs, Vector3 rhs)
        {
            return lhs.X < rhs.X && lhs.Y < rhs.Y && lhs.Z < rhs.Z;
        }
        public static bool operator >(Vector3 lhs, Vector3 rhs)
        {
            return lhs.X > rhs.X && lhs.Y > rhs.Y && lhs.Z > rhs.Z;
        }

        public static bool operator <=(Vector3 lhs, Vector3 rhs)
        {
            return lhs.X <= rhs.X && lhs.Y <= rhs.Y && lhs.Z <= rhs.Z;
        }
        public static bool operator >=(Vector3 lhs, Vector3 rhs)
        {
            return lhs.X >= rhs.X && lhs.Y >= rhs.Y && lhs.Z >= rhs.Z;
        }
        
        public static Vector3 operator *(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z);
        }
        public static Vector3 operator +(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z);
        }
        public static Vector3 operator -(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z);
        }
        public static Vector3 operator /(Vector3 lhs, Vector3 rhs)
        {
            return new Vector3(lhs.X / rhs.X, lhs.Y / rhs.Y, lhs.Z / rhs.Z);
        }

        public static Vector3 operator *(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs);
        }
        public static Vector3 operator /(Vector3 lhs, float rhs)
        {
            return new Vector3(lhs.X / rhs, lhs.Y / rhs, lhs.Z / rhs);
        }

        public static Vector3 operator -(Vector3 vector)
        {
            return new Vector3(-vector.X, -vector.Y, -vector.Z);
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
            return X.GetHashCode() + Y.GetHashCode() + Z.GetHashCode();
        }
    }
}
