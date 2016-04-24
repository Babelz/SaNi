using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    public struct Transform
    {
        #region Properties
        public Vector3 position;
        public Vector3 scale;
        public Vector3 origin;

        public float rotation;
        #endregion
        
        public Transform(float px, float py, float pz, float sx, float sy, float sz, float ox, float oy, float oz, float r)
        {
            position    = new Vector3(px, py, pz);
            origin      = new Vector3(ox, oy, oz);
            scale       = new Vector3(sx, sy, sz);
            rotation    = r;
        }
        public Transform(Vector3 position, Vector3 scale, Vector3 origin, float rotation)
        {
            this.position   = position;
            this.scale      = scale;
            this.origin     = origin;
            this.rotation   = rotation;
        }
        public Transform(Vector3 position, Vector3 scale, Vector3 origin)
            : this(position, scale, origin, 0.0f)
        {
        }
        public Transform(Vector3 position, Vector3 scale)
            : this(position, scale, Vector3.Zero, 0.0f)
        {
        }
        public Transform(Vector3 position)
            : this(position, Vector3.Zero, Vector3.Zero, 0.0f)
        {
        }

        public static Transform Empty()
        {
            return new Transform(Vector3.Zero, Vector3.Zero, Vector3.Zero, 0.0f);
        }
    }
}
