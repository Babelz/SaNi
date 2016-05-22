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
    public sealed class ParticleGenerator
    {
        #region Fields
        Vector2 spawnLocationMinOffset      = Vector2.Zero;
        Vector2 spawnLocationMaxOffset      = Vector2.Zero;

        Vector2 startVelocity               = Vector2.Zero;
        Vector2 velocityVariance            = Vector2.Zero;

        Vector2 baseAcceleration            = Vector2.Zero;
        Vector2 accelerationVariance        = Vector2.Zero;

        Vector2 startSize                   = new Vector2(32.0f, 32.0f);

        Vector2 baseScale                   = new Vector2(1.0f, 1.0f);
        Vector2 scaleVariance               = Vector2.Zero;

        Vector2 baseScaleAcceleration       = Vector2.Zero;
        Vector2 scaleAccelerationVariance   = Vector2.Zero;

        Vector2 baseScaleVelocity           = Vector2.Zero;
        Vector2 scaleVelocityVariance       = Vector2.Zero;

        Color color;
        Color colorVariance;

        GeneratorFlags flags;

        float baseAngularVelocity;
        float angularVelocityVariance;

        float baseAngularAcceleration;
        float angularAccelerationVariance;

        float baseDecayTime;
        float decayTimeVariance;

        uint firstAttributeListIndex;
        uint lastAttributeListIndex;

        uint framesToFade;
        uint framesToFadeVariance;
        #endregion

        public ParticleGenerator()
        {
        }
    }
}
