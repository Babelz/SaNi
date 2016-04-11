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

        public float X;
        public float Y;
        public float Z;
        public float W;
        #endregion

        #region Properties
        public float LengthSquared
        {
            get 
            {
                return X * X + Y * Y + Z * Z + W * W;
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

                if (index == 0) return X;
                if (index == 1) return Y;
                if (index == 2) return Z;
                else            return W;
            }
        }
        #endregion

        public Vector4(float x, float y, float z, float w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
        }
        public Vector4(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
            W = 0.0f;
        }
        public Vector4(float x, float y)
        {
            X = x;
            Y = y;
            Z = 0.0f;
            W = 0.0f;
        }
        public Vector4(float value)
        {
            X = value;
            Y = value;
            Z = value;
            W = value;
        }

        /*
            TODO: do performance tests with inline versions. 
         */

        public static Vector4 Normalize(Vector4 vector)
        {
            var length = vector.Length;

            return new Vector4(vector.X / length, vector.Y / length, vector.Z / length, vector.W / length);
        }
        public static float Dot(Vector4 lhs, Vector4 rhs)
        {
            Vector4 temp = lhs * rhs;

            return temp.X + temp.Y + temp.Z + temp.W;
        }

        public static bool operator ==(Vector4 lhs, Vector4 rhs)
        {
            return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z && lhs.W == rhs.W;
        }
        public static bool operator !=(Vector4 lhs, Vector4 rhs)
        {
            return !(lhs == rhs);
        }

        public static bool operator <(Vector4 lhs, Vector4 rhs)
        {
            return lhs.X < rhs.X && lhs.Y < rhs.Y && lhs.Z < rhs.Z && lhs.W < rhs.W;
        }
        public static bool operator >(Vector4 lhs, Vector4 rhs)
        {
            return lhs.X > rhs.X && lhs.Y > rhs.Y && lhs.Z > rhs.Z && lhs.W > rhs.W;
        }

        public static bool operator <=(Vector4 lhs, Vector4 rhs)
        {
            return lhs.X <= rhs.X && lhs.Y <= rhs.Y && lhs.Z <= rhs.Z && lhs.W <= rhs.W;
        }
        public static bool operator >=(Vector4 lhs, Vector4 rhs)
        {
            return lhs.X >= rhs.X && lhs.Y >= rhs.Y && lhs.Z >= rhs.Z && lhs.W >= rhs.W;
        }
        
        public static Vector4 operator *(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.X * rhs.X, lhs.Y * rhs.Y, lhs.Z * rhs.Z, lhs.W * rhs.W);
        }
        public static Vector4 operator +(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.X + rhs.X, lhs.Y + rhs.Y, lhs.Z + rhs.Z, lhs.W + rhs.W);
        }
        public static Vector4 operator -(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.X - rhs.X, lhs.Y - rhs.Y, lhs.Z - rhs.Z, lhs.W - rhs.W);
        }
        public static Vector4 operator /(Vector4 lhs, Vector4 rhs)
        {
            return new Vector4(lhs.X / rhs.X, lhs.Y / rhs.Y, lhs.Z / rhs.Z, lhs.W / rhs.W);
        }

        public static Vector4 operator *(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.X * rhs, lhs.Y * rhs, lhs.Z * rhs, lhs.W * rhs);
        }
        public static Vector4 operator /(Vector4 lhs, float rhs)
        {
            return new Vector4(lhs.X / rhs, lhs.Y / rhs, lhs.Z / rhs, lhs.W / rhs);
        }

        public static Vector4 operator -(Vector4 vector)
        {
            return new Vector4(-vector.X, -vector.Y, -vector.Z, -vector.W);
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
            return X.GetHashCode() + Y.GetHashCode() + Z.GetHashCode() + W.GetHashCode();
        }
    }
}
