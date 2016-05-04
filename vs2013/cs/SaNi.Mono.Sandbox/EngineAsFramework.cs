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
            var r1 = new Rectangle(32.0f, 32.0f, 256.0f, 256.0f);
            
            layer = Layers.CreateDynamic("base");

            layer.Add(r1);

            Console.WriteLine(layer.Name);

            Console.WriteLine("Start called");
            return true;
        }
        private bool OnResume()
        {
            Console.WriteLine("Resume called");
            return true;
        }
        private void OnSuspended()
        {
            Console.WriteLine("Suspend called");
        }
        private void OnTerminated()
        {
            Console.WriteLine("Terminate called");
        }

        Random r = new Random();

        private void OnUpdate(EngineTime time)
        {

            var r1 = layer.Elements.First();

            var transform = r1.Transform;
            transform.scale = new Vector3((float)r.NextDouble(), (float)r.NextDouble(), 0.0f);
            transform.position.x = 256.0f;
            transform.position.y = 256.0f;

            transform.rotation += 0.01f * (float)time.FrameTime.TotalMilliseconds;
            
            r1.Transform = transform;
        }
    }
}
