using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Services
{
    public enum ServiceState
    {
        /// Service has not been initialized yet.
        Uninitialized,

        /// Service is being suspended for a given amount of time.
        Suspended,

        /// Service has been terminated and it should be disposed.
        Terminated,

        /// Service is running.
        Running
    }
}
