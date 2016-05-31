using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Sandbox
{
    public static class Keyboard
    {
        public enum Key
        {
            W = (int)'W',
            A = (int)'A',
            S = (int)'S',
            D = (int)'D',
            ESC = 27
        }

        public enum KeyStates
        {
            None = 0,
            Down,
            Toggled
        }

        [DllImport("user32.dll", CharSet = CharSet.Auto, ExactSpelling = true)]
        private static extern short GetKeyState(int keyCode);

        private static KeyStates GetKeyState(Key key)
        {
            var state = KeyStates.None;

            var retVal = GetKeyState((int)key);

            // If the high-order bit is 1, the key is down
            // otherwise, it is up.
            if ((retVal & 0x8000) == 0x8000) state |= KeyStates.Down;

            // If the low-order bit is 1, the key is toggled.
            if ((retVal & 1) == 1) state |= KeyStates.Toggled;

            return state;
        }

        public static bool IsKeyDown(Key key)
        {
            return KeyStates.Down == (GetKeyState(key) & KeyStates.Down);
        }

        public static bool IsKeyUp(Key key)
        {
            return !IsKeyDown(key);
        }

        public static bool IsKeyToggled(Key key)
        {
            return KeyStates.Toggled == (GetKeyState(key) & KeyStates.Toggled);
        }
    }
}
