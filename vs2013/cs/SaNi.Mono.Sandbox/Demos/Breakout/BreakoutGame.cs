using SaNi.Mono.Engine;
using SaNi.Mono.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Sandbox.Demos.Breakout
{
    /*
        Use services as "game" to get internal engine hooks such as 
        start and update.
        
        Normally services would be used for things such as counting
        the score, to define rules for the game etc.
    */

    public sealed class BreakoutGame : EngineService
    {
        #region Fields
        private Player player;
        #endregion

        public BreakoutGame()
            : base("breakout game")
        {
        }

        private void OnStart() 
        {
            // Init player.
        }

        private void OnUpdate(EngineTime time)
        {
        }
    }
}
