using SaNi.Mono.Resource;
using SaNi.Mono.Engine;
using SaNi.Mono.Graphics;
using SaNi.Mono.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SaNi.Mono.Graphics.Renderables;
using SaNi.Mono.Math;

namespace SaNi.Mono.Sandbox
{
    public sealed class EngineAsFramework : EngineService
    {
        #region Fields
        private Circle c;

        private Layer layer;
        #endregion

        public EngineAsFramework() 
            : base("engine as framework")
        {
        }

        private bool OnStart()
        {
            // Create layer that can hold our renderable elements.
            layer = Layers.CreateDynamic("base");

            var andy = ResourceManager.Load<Texture2D>("andy");

            var autoscales = new Sprite(300.0f, 300.0f, andy);
            layer.Add(autoscales);

            c = new Circle(400.0f, 400.0f, 256.0f);
            c.Fill = Color.White;
            //c.Texture = ResourceManager.Load<Texture2D>("andy");
            c.BorderThickness = 32.0f;
            layer.Add(c);

            // Create triangles.
            for (var i = 0; i < 2; i++)
            {
                var triangle = new Triangle(Vector2.Zero, new Vector2(128.0f));
                triangle.BorderThickness = 8.0f;
                triangle.BorderFill = Color.Blue;
                triangle.Fill = Color.White;
                triangle.Texture = andy;

                var transform = triangle.Transform;
                transform.position.x = 200.0f + 128.0f * i;
                transform.position.y = 200.0f;
                triangle.Transform = transform;

                layer.Add(triangle);
            }

            // Test sprite..
            var manscales = new Sprite(new Vector2(300.0f), new Vector2(128.0f), andy);
            layer.Add(manscales);

            // Create 3 rectangles.
            for (var i = 0; i < 3; i++) layer.Add(new Rectangle(100 + 48.0f * i, 100, 32.0f, 32.0f) { BorderThickness = 8.0f });

            // Create particle emitter.
            ParticleGenerator gen = ParticleGenerator.Empty();

            gen.flags |= GeneratorFlags.VaryingVelocity;
            gen.flags |= GeneratorFlags.VaryingDecayTime;
            gen.flags |= GeneratorFlags.VaryingSpawnLocation;
            gen.flags |= GeneratorFlags.VaryingAngularVelocity;
            gen.flags |= GeneratorFlags.VaryingScale;
            gen.flags |= GeneratorFlags.UseScaleVelocity;

            gen.startVelocity = new Vector2(-0.325f, -0.25f);
            gen.velocityVariance = new Vector2(0.625f, 0.25f);

            gen.baseDecayTime = 550.0f;
            gen.decayTimeVariance = 350.0f;

            gen.spawnLocationMinOffset = new Vector2(-32.0f, 0.0f);
            gen.spawnLocationMaxOffset = new Vector2(32.0f, 0.0f);

            gen.baseAngularVelocity = 0.001f;
            gen.angularVelocityVariance = 0.01f;

            gen.baseScale = new Vector2(1.0f, 1.0f);
            gen.scaleVariance = new Vector2(0.5f, 0.5f);

            gen.baseScaleVelocity = new Vector2(0.001f, 0.001f);
            gen.scaleVelocityVariance = new Vector2(0.005f, 0.005f);

            gen.framesToFade = 16;
            gen.framesToFadeVariance = 4;

            // TODO: paska osuu tuulettimeen
            var x = 1280.0f / 2.0f;
            var y = 600.0f;

            ParticleEmitter emitter = new ParticleEmitter(gen, andy, new Vector2(x, y), 1024);
            layer.Add(emitter);

            return true;
        }
        private bool OnResume()
        {
            return true;
        }
        private void OnSuspended()
        {
        }
        private void OnTerminated()
        {
        }

        private static Random rand = new Random();

        private void OnUpdate(EngineTime time)
        {
            foreach (var rectangle in layer.Elements.Where(l => l.GetType() == typeof(Rectangle)))
            {
                var transform = rectangle.Transform;
                transform.rotation -= 0.001f;
                var bounds = rectangle.LocalBounds;

                rectangle.LocalBounds = bounds;
                rectangle.Transform = transform;
            }

            foreach (var triangle in layer.Elements.Where(l => l.GetType() == typeof(Triangle)))
            {
                var transform = triangle.Transform;
                transform.rotation += 0.001f;
                var bounds = triangle.LocalBounds;

                triangle.LocalBounds = bounds;
                triangle.Transform = transform;
            }

            c.Radius = (float)rand.NextDouble() * 64.0f;
        }
    }
}
