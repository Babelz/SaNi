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
        private Random rand;

        private List<Rectangle> bricks;

        private Ball ball;
        private Player player;
        #endregion

        public BreakoutGame()
            : base("breakout game")
        {
            rand = new Random();
        }

        private bool OnStart()
        {
            var backbufferWidth = (float)GraphicsDevice.BackbufferWidth();
            var backbufferHeight = (float)GraphicsDevice.BackbufferHeight();
            
            // Init area.
            var borderThickness = 32.0f;

            var area = new Rectf(borderThickness,
                                 borderThickness,
                                 backbufferWidth - borderThickness * 2.0f,
                                 backbufferHeight - borderThickness);

            // Create player.
            var playerSize = new Vector2(128.0f, 32.0f);

            var playerPosition = new Vector2(area.Right - area.width / 2.0f,
                                             area.Bottom - borderThickness * 4.0f);

            player = new Player(playerPosition, playerSize, area);
            player.Rect.Fill = Color.Green;

            // Create borders.
            var borderElements = new Rectangle[4];

            // Right.
            borderElements[0] = new Rectangle(new Vector2(backbufferWidth - borderThickness / 2.0f, backbufferHeight / 2.0f), 
                                              new Vector2(borderThickness, backbufferHeight));
            
            // Left.
            borderElements[1] = new Rectangle(new Vector2(borderThickness / 2.0f, backbufferHeight / 2.0f), 
                                              new Vector2(borderThickness, backbufferHeight));
            
            // Top.
            borderElements[2] = new Rectangle(new Vector2(backbufferWidth / 2.0f, borderThickness / 2.0f), 
                                              new Vector2(backbufferWidth - borderThickness, borderThickness));

            // Bottom.
            borderElements[3] = new Rectangle(new Vector2(backbufferWidth / 2.0f, backbufferHeight - borderThickness / 2.0f), 
                                              new Vector2(backbufferWidth - borderThickness, borderThickness));

            // Create ball.
            const float radius = 32.0f;

            var playerTransform = player.Rect.Transform;

            ball = new Ball(new Vector2(playerTransform.position.x + player.Rect.LocalBounds.width / 2.0f,
                                        playerTransform.position.y - player.Rect.LocalBounds.height * 2.0f), radius, 
                                        new Rectf[] { borderElements[0].GlobalBounds, borderElements[1].GlobalBounds, borderElements[2].GlobalBounds, borderElements[3].GlobalBounds });

            ball.Circle.Fill = Color.Green;
            ball.Circle.BorderFill = new Color(125, 125, 0, 255);

            // Create 8x8 grid of bricks.
            bricks = new List<Rectangle>();

            // Offset.
            const float rows     = 8.0f;
            const float columns  = 8.0f;
            const float boff     = 64.0f;

            // Start x and y.
            var bsx = area.Left + boff;
            var bsy = area.Top + boff;
            
            // Width and height.
            var bw = (area.width - boff * 2.0f) / columns;
            var bh = (area.height / 2.0f) / rows;

            for (var h = 0; h < 8; h++)
            {
                for (var w = 0; w < 8; w++)
                {
                    var x = bsx + w * bw;
                    var y = bsy + h * bh;

                    var brick = new Rectangle(x, y, bw, bh);
                    
                    var color = new Color((float)rand.NextDouble(),
                                          (float)rand.NextDouble(),
                                          (float)rand.NextDouble(),
                                          (float)rand.NextDouble());

                    var transform = brick.Transform;

                    transform.origin = Vector3.Zero;

                    brick.Transform = transform;
                    brick.Fill = color;

                    bricks.Add(brick);
                }
            }

            // Create layer and add elements.
            var layer = Layers.CreateDynamic("bottom");

            layer.Add(player.Rect);
            layer.Add(ball.Circle);

            foreach (var element in borderElements) layer.Add(element);
            foreach (var element in bricks)         layer.Add(element);

            return true;
        }

        private void OnUpdate(EngineTime time)
        {
            if (Keyboard.IsKeyDown(Keyboard.Key.ESC))
            {
                SaNiEngine.Exit();

                return;
            }

            // Windowed/fullscreen changes.
            //if (Keyboard.IsKeyDown(Keyboard.Key.Y)) GraphicsDevice.Fullscreen();
            //if (Keyboard.IsKeyDown(Keyboard.Key.U)) GraphicsDevice.Windowed();

            foreach (var brick in bricks)
            {
                brick.Fill = new Color((float)rand.NextDouble(),
                                       (float)rand.NextDouble(),
                                       (float)rand.NextDouble(),
                                       (float)rand.NextDouble());
            }

            player.Update(time);
            ball.Update(time, player.Rect.GlobalBounds);

            // Best collision check algorithm EU (bricks <-> ball)
            for (var i = 0; i < bricks.Count; i++)
            {
                var brick = bricks[i];

                if (brick.GlobalBounds.Intersects(ball.Circle.GlobalBounds))
                {
                    brick.Destroy();

                    bricks.Remove(brick);
                }
            }
        }
    }
}
