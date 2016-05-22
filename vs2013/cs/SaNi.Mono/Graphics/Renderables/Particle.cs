using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class Particle
    {
        #region Fields
        /// <summary>
        /// Handle to unmanaged.
        /// </summary>
        private uint ptr;
        #endregion

        #region Properties
        public Sprite Sprite
        {
            get
            {
                Sprite sprite = null;

                return GetSprite(ref sprite);
            }
        }

        public Vector2 Acceleration
        {
            get
            {
                var value = Vector2.Zero;

                GetAcceleration(ref value);

                return value;
            }
            set
            {
                SetAcceleraion(value);
            }
        }
        public Vector2 Velocity
        {
            get
            {
                var value = Vector2.Zero;

                GetVelocity(ref value);

                return value;
            }
            set
            {
                SetVelocity(value);
            }
        }

        public float DecayTime
        {
            get
            {
                var value = 0.0f;

                GetDecayTime(ref value);

                return value;
            }
            set
            {
                SetDecayTime(value);
            }
        }

        public float ElapsedTime
        {
            get
            {
                var value = 0.0f;

                GetDecayTime(ref value);

                return value;
            }
            set
            {
                SetDecayTime(value);
            }
        }
        public float AngularAcceleration
        {
            get
            {
                var value = 0.0f;

                GetDecayTime(ref value);

                return value;
            }
            set
            {
                SetDecayTime(value);
            }
        }
        public float AngularVelocity
        {
            get
            {
                var value = 0.0f;

                GetDecayTime(ref value);

                return value;
            }
            set
            {
                SetDecayTime(value);
            }
        }

        public Vector2 ScaleAcceleration
        {
            get
            {
                var value = Vector2.Zero;

                GetScaleAcceleration(ref value);

                return value;
            }
            set
            {
                SetScaleAcceleration(value);
            }
        }

        public Vector2 ScaleVelocity
        {
            get
            {
                var value = Vector2.Zero;

                SetScaleVelocity(ref value);

                return value;
            }
            set
            {
                GetScaleVelocity(value);
            }
        }

        public uint Frames
        {
            get
            {
                var value = 0u;

                GetFrames(ref value);

                return value;
            }
        }
        public uint FramesBeforeFade
        {
            get
            {
                var value = 0u;

                GetFramesBeforeFade(ref value);

                return value;
            }
            set
            {
                SetFramesBeforeFade(value);
            }
        }

        public float FadeDelta
        {
            get
            {
                var value = 0.0f;

                GetFadeDelta(ref value);

                return value;
            }
            set
            {
                SetFadeDelta(value);
            }
        }
        #endregion

        private Particle(uint ptr)
        {
            this.ptr = ptr;
        }

        #region Internal get/set methods
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern Sprite GetSprite(ref Sprite sprite);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetAcceleraion(Vector2 value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetAcceleration(ref Vector2 value);
            
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVelocity(Vector2 value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetVelocity(ref Vector2 value);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetDecayTime(float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetDecayTime(ref float value);
            
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetScaleAcceleration(Vector2 value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetScaleAcceleration(ref Vector2 value);
            
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetScaleVelocity(Vector2 value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetScaleVelocity(ref Vector2 value);
        
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetFrames(ref uint value);
            
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetFramesBeforeFade(uint value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetFramesBeforeFade(ref uint value);
            
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetFadeDelta(float value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetFadeDelta(ref float value);
        #endregion
    }
}
