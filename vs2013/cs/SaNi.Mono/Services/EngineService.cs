using SaNi.Mono.Engine;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Services
{
    /// <summary>
    /// Base class of all engine services.
    /// </summary>
    public abstract class EngineService
    {
        #region Properties
        public string Name
        {
            get;
            private set;
        }
        public int ID
        {
            get;
            private set;
        }
        public ServiceState State
        {
            get;
            private set;
        }
        #endregion

        protected EngineService(string name)
        {
            var id = 0;

            InternalCreateService(name, ref id);

            Name = name;
            ID = id;
        }

        // Method hooks the service can contain are:
        //  bool OnStart()
        //  bool OnResume()
        //  void OnSuspended()
        //  void OnTerminated()
        //  void OnUpdate(EngineTime time)

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void InternalCreateService(string name, ref int id);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Start();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Suspend();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Terminate();
    }
}
