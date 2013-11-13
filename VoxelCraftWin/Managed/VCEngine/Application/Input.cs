using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace VCEngine
{
    
    public static class Input
    {
        #region Keys
        public struct Keys
        {
            public const int Escape = 256;
            public const int Enter = 257;
            public const int Tab = 258;
            public const int Backspace = 259;
            public const int Insert = 260;
            public const int Delete = 261;
            public const int Right = 262;
            public const int Left = 263;
            public const int Down = 264;
            public const int Up = 265;
            public const int PageUp = 266;
            public const int PageDown = 267;
            public const int Home = 268;
            public const int End = 269;
            public const int CapsLock = 280;
            public const int ScrollLock = 281;
            public const int NumLock = 282;
            public const int PrintScreen = 283;
            public const int Pause = 284;
            public const int F1 = 290;
            public const int F2 = 291;
            public const int F3 = 292;
            public const int F4 = 293;
            public const int F5 = 294;
            public const int F6 = 295;
            public const int F7 = 296;
            public const int F8 = 297;
            public const int F9 = 298;
            public const int F10 = 299;
            public const int F11 = 300;
            public const int F12 = 301;
            public const int F13 = 302;
            public const int F14 = 303;
            public const int F15 = 304;
            public const int F16 = 305;
            public const int F17 = 306;
            public const int F18 = 307;
            public const int F19 = 308;
            public const int F20 = 309;
            public const int F21 = 310;
            public const int F22 = 311;
            public const int F23 = 312;
            public const int F24 = 313;
            public const int F25 = 314;
            public const int Kp0 = 320;
            public const int Kp1 = 321;
            public const int Kp2 = 322;
            public const int Kp3 = 323;
            public const int Kp4 = 324;
            public const int Kp5 = 325;
            public const int Kp6 = 326;
            public const int Kp7 = 327;
            public const int Kp8 = 328;
            public const int Kp9 = 329;
            public const int KpDecimal = 330;
            public const int KpDivide = 331;
            public const int KpMultiply = 332;
            public const int KpSubtract = 333;
            public const int KpAdd = 334;
            public const int KpEnter = 335;
            public const int KpEqual = 336;
            public const int LeftShift = 340;
            public const int LeftControl = 341;
            public const int LeftAlt = 342;
            public const int LeftSuper = 343;
            public const int RightShift = 344;
            public const int RightControl = 345;
            public const int RightAlt = 346;
            public const int RightSuper = 347;
            public const int Menu = 348;
        }
        #endregion

        public static bool IsSuppressingUpdate;
        public static Vector2 DeltaLook 
        { 
            get 
            {
                if (IsSuppressingUpdate)
                    return new Vector2(0.0f, 0.0f);

                return new Vector2(GlfwInputState.MouseLocation.X, GlfwInputState.MouseLocation.Y);
            } 
        }
        public static Vector2 Strafe
        {
            get
            {
                if (IsSuppressingUpdate)
                    return new Vector2(0.0f, 0.0f);

                Vector2 strafeVec = new Vector2(0.0f, 0.0f);

                if (GlfwInputState.KeyStates['W'].State != TriState.None) strafeVec.X += 1.0f;
                if (GlfwInputState.KeyStates['S'].State != TriState.None) strafeVec.X += -1.0f;

                if (GlfwInputState.KeyStates['A'].State != TriState.None) strafeVec.Y += 1.0f;
                if (GlfwInputState.KeyStates['D'].State != TriState.None) strafeVec.Y += -1.0f;

                if (strafeVec.X > 0.1f || strafeVec.X < -0.1f || strafeVec.Y > 0.1f || strafeVec.Y < -0.1f )
                    strafeVec.Normalize();

                return strafeVec;
            }
        }

        public static TriState GetKey(int keyCode)
        {
            if (IsSuppressingUpdate)
                return TriState.None;

            return GlfwInputState.KeyStates[keyCode].State;
        }

        public static TriState GetMouse(int button)
        {
            if (IsSuppressingUpdate)
                return TriState.None;

            return GlfwInputState.MouseStates[button].State;
        }
    }
}
