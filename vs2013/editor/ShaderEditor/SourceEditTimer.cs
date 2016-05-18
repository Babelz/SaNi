using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor
{
    public sealed class SourceEditTimer
    {
        #region Fields
        private readonly int recompileAfterMillis;

        private readonly Stopwatch timer;
        #endregion

        #region Properties
        public bool ShouldRecompile
        {
            get;
            private set;
        }
        #endregion

        public SourceEditTimer(int recompileAfterMillis)
        {
            this.recompileAfterMillis = recompileAfterMillis;

            timer = new Stopwatch();
        }

        public void StartMeasuring()
        {
            if (!timer.IsRunning)
            {
                timer.Start();
            }
            else if (timer.ElapsedMilliseconds >= recompileAfterMillis)
            {
                ShouldRecompile = true;
                timer.Restart();
            }

            timer.Restart();
        }

        public void StopMeasuring()
        {
            timer.Reset();
        }
    }
}
