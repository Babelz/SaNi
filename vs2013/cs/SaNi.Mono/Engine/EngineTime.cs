using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Engine
{
    public struct EngineTime
    {
        public readonly float TotalTime;
        public readonly float FrameTime;

        public EngineTime(float totalTime, float frameTime)
        {
            TotalTime = totalTime;
            FrameTime = frameTime;
        }
    }
}
