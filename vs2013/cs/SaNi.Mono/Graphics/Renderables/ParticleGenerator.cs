using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    [StructLayout(LayoutKind.Sequential)]
    public struct ParticleGenerator
    {
        #region Fields
        public Color color;
        public Color colorVariance;

        public Vector2 spawnLocationMinOffset      ; //= Vector2.Zero;
        public Vector2 spawnLocationMaxOffset      ; //= Vector2.Zero;

        public Vector2 startVelocity               ; //= Vector2.Zero;
        public Vector2 velocityVariance            ; //= Vector2.Zero;

        public Vector2 baseAcceleration            ; //= Vector2.Zero;
        public Vector2 accelerationVariance        ; //= Vector2.Zero;

        public Vector2 startSize                   ; //= new Vector2(32.0f, 32.0f);

        public Vector2 baseScale                   ; //= new Vector2(1.0f, 1.0f);
        public Vector2 scaleVariance               ; //= Vector2.Zero;

        public Vector2 baseScaleAcceleration       ; //= Vector2.Zero;
        public Vector2 scaleAccelerationVariance   ; //= Vector2.Zero;

        public Vector2 baseScaleVelocity           ; //= Vector2.Zero;
        public Vector2 scaleVelocityVariance       ; //= Vector2.Zero;

        public float baseAngularVelocity;
        public float angularVelocityVariance;

        public float baseAngularAcceleration;
        public float angularAccelerationVariance;

        public float baseDecayTime;
        public float decayTimeVariance;

        public uint firstAttributeListIndex ; //= 0;
        public uint lastAttributeListIndex  ; //= 0;

        public uint framesToFade;
        public uint framesToFadeVariance;

        public GeneratorFlags flags;
        #endregion

        public static ParticleGenerator Empty()
        {
            ParticleGenerator generator = new ParticleGenerator();

            generator.startSize     = new Vector2(32.0f);
            generator.baseScale     = new Vector2(1.0f);
            generator.color         = Color.White;

            return generator;
        }
    }
}
