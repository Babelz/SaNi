using SaNi.Mono.Configuration;
using SaNi.Mono.Engine;
using SaNi.Mono.Graphics;
using SaNi.Mono.Graphics.Renderables;
using SaNi.Mono.Math;
using SaNi.Mono.Services;
using System;
using System.Collections.Generic;
using System.Diagnostics;
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
        private List<Rectangle> bricks;

        private Player player;
        #endregion

        public BreakoutGame()
            : base("breakout game")
        {
        }

        private bool OnStart()
        {
            // Get cvars we need for init.
            //var cvars = CVars.GetCVars();

            //var cvarWindowWidth = cvars.FirstOrDefault(c => c.Name == EngineCVars.WindowWidth);
            //var cvarWindowHeight = cvars.FirstOrDefault(c => c.Name == EngineCVars.WindowHeight);

            var windowWidth = 1270;
            var windowHeight = 680;

            //Console.WriteLine(cvarWindowWidth == null);
            //Console.WriteLine(cvarWindowHeight == null);

            //if (cvarWindowWidth != null) windowWidth = (int)cvarWindowWidth.Read();
            //if (cvarWindowHeight != null) windowHeight = (int)cvarWindowHeight.Read();

            // Init area.
            var borderThickness = 32.0f;

            var area = new Rectf(borderThickness,
                                 borderThickness,
                                 windowWidth - borderThickness * 2.0f,
                                 windowHeight - borderThickness);

            // Create player.
            var playerSize = new Vector2(128.0f, 32.0f);

            var playerPosition = new Vector2(area.Right - area.width / 2.0f,
                                             area.Bottom - borderThickness * 4.0f);

            player = new Player(playerPosition, playerSize, area);
            player.Rect.Fill = Color.Green;

            // Create borders.
            var borderElements = new Rectangle[4];

            // Left.
            borderElements[0] = new Rectangle(new Vector2(windowWidth - borderThickness / 2.0f, windowHeight / 2.0f), new Vector2(borderThickness, windowHeight));
            
            // Right.
            borderElements[1] = new Rectangle(new Vector2(borderThickness / 2.0f, windowHeight / 2.0f), new Vector2(borderThickness, windowHeight));
            
            // Top.
            borderElements[2] = new Rectangle(new Vector2(windowWidth / 2.0f, borderThickness / 2.0f), new Vector2(windowWidth - borderThickness, borderThickness));

            // Bottom.
            borderElements[3] = new Rectangle(new Vector2(windowWidth / 2.0f, windowHeight - borderThickness / 2.0f), new Vector2(windowWidth - borderThickness, borderThickness));

            // Create bricks.
            bricks = new List<Rectangle>();

            // Create layer and add elements.
            var layer = Layers.CreateDynamic("bottom");

            layer.Add(player.Rect);

            foreach (var element in borderElements) layer.Add(element);

            return true;
        }

        private void OnUpdate(EngineTime time)
        {
            player.Update(time);
        }
    }
}
