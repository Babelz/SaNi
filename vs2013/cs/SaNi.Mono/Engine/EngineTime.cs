using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Engine
{
    public struct EngineTime
    {
        public readonly TimeSpan TotalTime;
        public readonly TimeSpan FrameTime;

        public EngineTime(float totalTime, float frameTime)
        {
            TotalTime = TimeSpan.FromMilliseconds(totalTime);
            FrameTime = TimeSpan.FromMilliseconds(frameTime);
        }
    }
}
