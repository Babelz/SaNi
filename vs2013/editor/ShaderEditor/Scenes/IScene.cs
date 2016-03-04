using ShaderEditor.Rendering;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Scenes
{
    internal interface IScene
    {
        void Draw(SpriteBatch spriteBatch, float delta);
    }
}
