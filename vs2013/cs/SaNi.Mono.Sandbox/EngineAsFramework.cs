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
        private Rectangle r1;
        #endregion

        public EngineAsFramework() 
            : base("engine as framework")
        {
        }

        private bool OnStart()
        {
            r1 = new Rectangle(32.0f, 32.0f, 256.0f, 256.0f);
            
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
        private void OnUpdate(EngineTime time)
        {
        }
    }
}
