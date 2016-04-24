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

namespace SaNi.Mono.Sandbox
{
    public sealed class EngineAsFramework : EngineService
    {
        #region Fields
        private Rectangle r1;
        private Rectangle r2;
        private Rectangle r3;
        private Rectangle r4;
        #endregion

        public EngineAsFramework() 
            : base("engine as framework")
        {
        }

        private bool OnStart()
        {
            r1 = new Rectangle(32.0f, 32.0f, 32.0f, 32.0f);
            r2 = new Rectangle(32.0f, 32.0f, 32.0f, 32.0f);
            r3 = new Rectangle(32.0f, 32.0f, 32.0f, 32.0f);
            r4 = new Rectangle(32.0f, 32.0f, 32.0f, 32.0f);
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
            r1.Print();
            r2.Print();
            r3.Print();
            r4.Print();
            var c = r1.LocalBounds;
            c = r2.LocalBounds;
            c = r3.LocalBounds;
            c = r4.LocalBounds;
        }

        ~EngineAsFramework()
        {
            Console.WriteLine("easf dtor");
        }
    }
}
