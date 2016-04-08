using SaNi.Mono.Engine;
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

            Suspend();

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

            Start();
        }
        private void OnTerminated()
        {
            Console.WriteLine("Teminate called");
        }
        private void OnUpdate(EngineTime time) 
        {
            Console.WriteLine("Update called");
        }
    }
}
