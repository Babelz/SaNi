using ShaderEditor.Rendering;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Scenes
{
    internal sealed class SpriteScene : IScene
    {
        #region Fields
        private Sprite sprite;
        #endregion

        #region Properties
        public Sprite Sprite
        {
            get;
            private set;
        }
        #endregion

        public SpriteScene()
        {
            sprite = new Sprite();

            var texture = Texture2D.LoadFromDisk("Textures\\sani.png");
            
            sprite.Texture = texture;
            sprite.Position = new OpenTK.Vector3(300.0f, 300.0f, 0.0f);
            sprite.Bounds = new OpenTK.Vector2(texture.Width, texture.Height);
            sprite.Color = new OpenTK.Vector4(1.0f, 0.0f, 0.0f, 1.0f);
            
            sprite.ResetTextureSource();
        }

        public void Draw(SpriteBatch spriteBatch, float delta)
        {
            sprite.Update();

            spriteBatch.Draw(sprite);
        }
    }
}
