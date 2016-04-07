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
        }

        private bool OnStart()
        {
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
            Console.WriteLine("Teminate called");
        }
        private void OnUpdate(EngineTime time) 
        {
            Console.WriteLine("Update called");
        }
    }
}
