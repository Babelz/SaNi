using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public struct Color
    {
        #region Fields
        public float r;
        public float g;
        public float b;
        public float a;
        #endregion

        #region Predefined colors
        public static Color Black
        {
            get { return new Color(0, 0, 0, 255); }
        }
        public static Color White
        {
            get { return new Color(255, 255, 255, 255); }
        }
        public static Color Red
        {
            get { return new Color(255, 0, 0, 255); }
        }
        public static Color Green
        {
            get { return new Color(0, 255, 0, 255); }
        }
        public static Color Blue
        {
            get { return new Color(0, 0, 255, 255); }
        }
        #endregion

        public Color(byte r, byte g, byte b, byte a)
        {
            this.r = (float)(r / 255.0f);
            this.g = (float)(g / 255.0f);
            this.b = (float)(b / 255.0f);
            this.a = (float)(a / 255.0f);
        }
        public Color(float r, float g, float b, float a)
        {
            this.r = r;
            this.g = g;
            this.b = b;
            this.a = a;
        }
        public Color(string hex)
        {
            if (hex.StartsWith("#")) hex = hex.Substring(1);

            if (hex.Length != 6) throw new Exception("Invalid color");

            var r = byte.Parse(hex.Substring(0, 2), System.Globalization.NumberStyles.HexNumber);
            var g = byte.Parse(hex.Substring(2, 2), System.Globalization.NumberStyles.HexNumber);
            var b = byte.Parse(hex.Substring(4, 2), System.Globalization.NumberStyles.HexNumber);
            var a = byte.Parse(hex.Substring(6, 2), System.Globalization.NumberStyles.HexNumber);

            this.r = (float)(r / 255);
            this.g = (float)(g / 255);
            this.b = (float)(b / 255);
            this.a = (float)(a / 255);
        }

        public static Color operator +(Color lhs, Color rhs)
        {
            return new Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a);
        }
        public static Color operator -(Color lhs, Color rhs)
        {
            return new Color(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a);
        }
        public static Color operator *(Color lhs, Color rhs)
        {
            return new Color(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a);
        }
        public static Color operator *(Color lhs, float rhs)
        {
            return new Color(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs, lhs.a * rhs);
        }
    }
}
