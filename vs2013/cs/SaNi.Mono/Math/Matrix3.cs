using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Math
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Matrix3
    {
        #region Fields
        public const int Rows = 3;

        public Vector3 Row1;
        public Vector3 Row2;
        public Vector3 Row3;
        #endregion

        #region Indexer
        public Vector3 this[int index]
        {
            get
            {
                Debug.Assert(index < Rows);

                if (index == 0) return Row1;
                if (index == 1) return Row2;
                else return Row1;
            }
        }
        #endregion

        public Matrix3(Vector3 row1, Vector3 row2, Vector3 row3)
        {
            Row1 = row1;
            Row2 = row2;
            Row3 = row3;
        }
        public Matrix3(Vector3 values)
        {
            Row1 = values;
            Row2 = values;
            Row3 = values;
        }

        public static bool operator ==(Matrix3 lhs, Matrix3 rhs)
        {
            for (int i = 0; i < Matrix3.Rows; i++) if (lhs[i] != rhs[i]) return false;

            return true;
        }

        public static bool operator !=(Matrix3 lhs, Matrix3 rhs)
        {
            return !(lhs == rhs);
        }

        public static Matrix3 operator +(Matrix3 lhs, Matrix3 rhs) 
        {
            return new Matrix3(lhs.Row1 + rhs.Row1,
                               lhs.Row2 + rhs.Row2,
                               lhs.Row3 + rhs.Row3);
        }

        public static Matrix3 operator -(Matrix3 lhs, Matrix3 rhs)
        {
            return new Matrix3(lhs.Row1 - rhs.Row1,
                               lhs.Row2 - rhs.Row2,
                               lhs.Row3 - rhs.Row3); 
        }

        public static Matrix3 operator *(Matrix3 lhs, Matrix3 rhs)
        {
            return new Matrix3(lhs.Row1 * rhs.Row1,
                               lhs.Row2 * rhs.Row2,
                               lhs.Row3 * rhs.Row3);
        }

        public static Matrix3 operator *(Matrix3 lhs, float rhs)
        {
            return new Matrix3(lhs.Row1 * rhs,
                               lhs.Row2 * rhs,
                               lhs.Row3 * rhs);
        }

        public static Matrix3 operator /(Matrix3 lhs, float rhs)
        {
            return new Matrix3(lhs.Row1 / rhs,
                               lhs.Row2 / rhs,
                               lhs.Row3 / rhs);
        }

        public override bool Equals(object obj)
        {
            if (obj == null) return false;

            if (obj.GetType() == typeof(Matrix3))
            {
                Matrix3 other = (Matrix3)obj;

                return this == other;
            }

            return false;
        }

        public override int GetHashCode()
        {
            return Row1.GetHashCode() + Row2.GetHashCode() + Row3.GetHashCode();
        }
    }
}
