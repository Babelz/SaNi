using SaNi.Mono.Engine;
using SaNi.Mono.Graphics.Renderables;
using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Sandbox.Demos.Breakout
{
    public sealed class Ball
    {
        #region Fields
        private readonly Rectf[] walls;
        #endregion

        #region Properties
        public Circle Circle
        {
            get;
            private set;
        }
        public Vector3 Velocity
        {
            get;
            set;
        }
        public Vector3 Direction
        {
            get;
            set;
        }
        #endregion

        public Ball(Vector2 position, float radius, Rectf[] walls)
        {
            Circle = new Circle(position, radius);

            Velocity = new Vector3(1.0f);
            Direction = new Vector3(-0.85f);

            this.walls = walls;
        }

        private void ChangeHorizontalDirection()
        {
            var direction = Direction;

            direction.x = -direction.x;

            Direction = direction;

            var transform = Circle.Transform;

            transform.position.x += direction.x * 2.0f;

            Circle.Transform = transform;
        }
        private void ChangeVerticalDirection()
        {
            var direction = Direction;

            direction.y = -direction.y;

            Direction = direction;

            var transform = Circle.Transform;

            transform.position.y += direction.y * 2.0f;

            Circle.Transform = transform;
        }

        private void Move(float delta, Rectf playerRect)
        {
            var Right   = walls[0];
            var Left    = walls[1];
            var Top     = walls[2];
            var Bottom  = walls[3];

            if (Circle.GlobalBounds.Intersects(playerRect))
            {
                if (Circle.GlobalBounds.Left < playerRect.Right || Circle.GlobalBounds.Right > playerRect.Left) ChangeHorizontalDirection();
                if (Circle.GlobalBounds.Top < playerRect.Bottom || Circle.GlobalBounds.Bottom > playerRect.Top) ChangeVerticalDirection();
            }
            
            if (Circle.GlobalBounds.Left < Left.Right || Circle.GlobalBounds.Right > Right.Left) ChangeHorizontalDirection();
            if (Circle.GlobalBounds.Top < Top.Bottom || Circle.GlobalBounds.Bottom > Bottom.Top) ChangeVerticalDirection();
            
            var transform = Circle.Transform;

            transform.position.x += delta * Velocity.x * Direction.x;
            transform.position.y += delta * Velocity.y * Direction.y;

            Circle.Transform = transform;
        }

        public void Update(EngineTime time, Rectf playerRect)
        {
            var delta = (float)time.FrameTime.TotalMilliseconds;

            Move(delta, playerRect);
        }
    }
}
