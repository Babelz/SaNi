using SaNi.Mono.Resource;
using SaNi.Mono.Engine;
using SaNi.Mono.Graphics;
using SaNi.Mono.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Sandbox
{
    public sealed class EngineAsFramework : EngineService
    {
        #region Fields
        private Texture2D andy;
        #endregion

        public EngineAsFramework() 
            : base("engine as framework")
        {
            Console.WriteLine("CTRO CALLED");
            Console.WriteLine("NAME: " + Name);
            Console.WriteLine("ID: " + ID);
            Console.WriteLine("STATE: " + Enum.GetName(typeof(ServiceState), State));
        }

        private bool OnStart()
        {
            Console.WriteLine("Start called");
            Console.ForegroundColor = ConsoleColor.DarkYellow;
            Console.WriteLine("ERKKI O :D");
            Console.ResetColor();

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
            andy = ResourceManager.Load<Texture2D>("andy");

            Console.WriteLine("\nANDY:");
            Console.WriteLine("\tW: " + andy.Width);
            Console.WriteLine("\tH: " + andy.Height);
            Console.WriteLine("\tID: " + andy.ID);
        }
    }
}
