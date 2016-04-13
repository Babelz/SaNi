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
        public float R;
        public float G;
        public float B;
        public float A;
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
            R = (float)(r / 255.0f);
            G = (float)(g / 255.0f);
            B = (float)(b / 255.0f);
            A = (float)(a / 255.0f);
        }
        public Color(float r, float g, float b, float a)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }
        public Color(string hex)
        {
            if (hex.StartsWith("#")) hex = hex.Substring(1);

            if (hex.Length != 6) throw new Exception("Invalid color");

            var r = byte.Parse(hex.Substring(0, 2), System.Globalization.NumberStyles.HexNumber);
            var g = byte.Parse(hex.Substring(2, 2), System.Globalization.NumberStyles.HexNumber);
            var b = byte.Parse(hex.Substring(4, 2), System.Globalization.NumberStyles.HexNumber);
            var a = byte.Parse(hex.Substring(6, 2), System.Globalization.NumberStyles.HexNumber);

            R = (float)(r / 255);
            G = (float)(g / 255);
            B = (float)(b / 255);
            A = (float)(a / 255);
        }

        public static Color operator +(Color lhs, Color rhs)
        {
            return new Color(lhs.R + rhs.R, lhs.G + rhs.G, lhs.B + rhs.B, lhs.A + rhs.A);
        }
        public static Color operator -(Color lhs, Color rhs)
        {
            return new Color(lhs.R - rhs.R, lhs.G - rhs.G, lhs.B - rhs.B, lhs.A - rhs.A);
        }
        public static Color operator *(Color lhs, Color rhs)
        {
            return new Color(lhs.R * rhs.R, lhs.G * rhs.G, lhs.B * rhs.B, lhs.A * rhs.A);
        }
        public static Color operator *(Color lhs, float rhs)
        {
            return new Color(lhs.R * rhs, lhs.G * rhs, lhs.B * rhs, lhs.A * rhs);
        }
    }
}
