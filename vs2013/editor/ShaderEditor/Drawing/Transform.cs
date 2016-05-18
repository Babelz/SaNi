using OpenTK;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Drawing
{
    public sealed class Transform
    {
        #region Properties
        public Vector2 position;
        public Vector2 scale;
        public Vector2 size;
        public Vector2 origin;

        public float rotation;
        #endregion

        public Transform()
        {
        }
    }
}
