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
        #region Fields
        private readonly uint ptr;
        #endregion

        #region Properties
        public string Name
        {
            get
            {
                return InternalGetName();
            }
        }
        public int ID
        {
            get
            {
                return InternalGetID();
            }
        }
        public ServiceState State
        {
            get
            {
                return (ServiceState)InternalGetState();
            }
        }
        #endregion

        public EngineService(string name)
        {
            Instantiate(name, ref ptr);
        }

        // Method hooks the service can use are:
        //  void OnStart()
        //  void OnResume()
        //  void OnSuspended()
        //  void OnTerminated()
        //  void OnUpdate(EngineTime time)

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(string name, ref uint ptr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern string InternalGetName();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetID();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern int InternalGetState();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Start();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Suspend();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Terminate();
    }
}
