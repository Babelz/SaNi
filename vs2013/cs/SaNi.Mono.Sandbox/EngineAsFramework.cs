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

            // Create 3 rectangles.
            //for (var i = 0; i < 3; i++) layer.Add(new Rectangle(i * 128.0f + 32.0f, 400.0f, 32.0f, 32.0f));

            // Create triangles.
            for (var i = 0; i < 3; i++)
            {
                var triangle = new Triangle(Vector2.Zero, new Vector2(32.0f)) { BorderThickness = 16.0f };

                var transform = triangle.Transform;
                transform.position.x = 200.0f + 128.0f * i;
                transform.position.y = 200.0f;
                triangle.Transform = transform;

                layer.Add(triangle);
            }
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

        private void OnUpdate(EngineTime time)
        {
            foreach (var triangle in layer.Elements.Where(l => l.GetType() == typeof(Triangle)))
            {
                var transform = triangle.Transform;
                transform.rotation += 0.001f;
                triangle.Transform = transform;
            }

            foreach (var rectangle in layer.Elements.Where(l => l.GetType() == typeof(Rectangle)))
            {
                var transform = rectangle.Transform;
                transform.rotation -= 0.001f;
                rectangle.Transform = transform;
            }
        }
    }
}
