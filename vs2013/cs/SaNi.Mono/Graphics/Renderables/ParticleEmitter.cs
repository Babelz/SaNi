using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public sealed class ParticleEmitter : IRenderable
    {   
        // TODO:
        //      - particle iterator
        //      - emit function
        //      - attrib list

        #region Fields
        private ParticleGenerator generator;

        private Transform transform;
        
        private Rectf localBounds;
        private Rectf globalbounds;
        private Rectf textureSource;

        private Texture2D texture;
        
        private Color color;

        private readonly int id;
        private readonly uint ptr;

        private uint layer;

        private bool destroyed;
        #endregion

        #region Properties
        public Transform Transform
        {
            get
            {
                GetTransform(ref transform);

                return transform;
            }
            set
            {
                SetTransform(value);
            }
        }
        public Rectf LocalBounds
        {
            get
            {
                GetLocalBounds(ref localBounds);

                return localBounds;
            }
            set
            {
                SetLocalBounds(value);
            }
        }
        public Rectf GlobalBounds
        {
            get
            {
                GetGlobalBounds(ref globalbounds);

                return globalbounds;
            }
        }
        public Rectf TextureSource
        {
            get
            {
                GetTextureSource(ref textureSource);

                return textureSource;
            }
            set
            {
                SetTextureSource(textureSource);
            }
        }
        public Texture2D Texture
        {
            get
            {
                GetTexture(ref texture);

                return texture;
            }
            set
            {
                SetTexture(value);
            }
        }
        public int ID
        {
            get
            {
                return id;
            }
        }
        public bool Visible
        {
            get
            {
                var value = false;

                GetVisible(ref value);

                return value;
            }
            set
            {
                SetVisible(value);
            }
        }
        public Color Color
        {
            get
            {
                GetColor(ref color);

                return color;
            }
            set
            {
                SetColor(value);
            }
        }

        public int MaxParticles
        {
            get
            {
                var value = 0;

                GetMaxParticles(ref value);

                return value;
            }
        }
        public EmitFunction EmitFunction
        {
            get
            {
                var value = EmitFunction.Continuous;

                GetEmitFunction(ref value);

                return value;
            }
            set
            {
                SetEmitFunction(value);
            }
        }
        public ParticleGenerator Generator
        {
            get
            {
                GetGenerator(ref generator);

                return generator;
            }
            set
            {
                SetGenerator(generator);
            }
        }
        #endregion

        public ParticleEmitter(ParticleGenerator generator, Texture2D texture, float x, float y, float width, float height, uint maxParticles)
        {
            this.generator  = generator;
            
            transform       = Transform.Empty();

            localBounds     = Rectf.Empty();
            globalbounds    = Rectf.Empty();
            textureSource   = Rectf.Empty();

            color           = Color.White;

            Instantiate(x, y, width, height, texture, generator, maxParticles, ref id, ref ptr);
        }
        public ParticleEmitter(ParticleGenerator generator, Texture2D texture, Vector2 position, Vector2 size, uint maxParticles)
            : this(generator, texture, position.x, position.y, size.x, size.y, maxParticles)
        {
        }
        public ParticleEmitter(ParticleGenerator generator, Texture2D texture, Vector2 position, uint maxParticles)
            : this(generator, texture, position, Vector2.Zero, maxParticles)
        {
        }
        public ParticleEmitter(ParticleGenerator generator, Texture2D texture, uint maxParticles)
            : this(generator, texture, Vector2.Zero, Vector2.Zero, maxParticles)
        {
        }
   
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Instantiate(float x, float y, float width, float height, Texture2D texture, ParticleGenerator generator, uint maxParticles, ref int id, ref uint ptr);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void Release();

        #region Internal get/set methods
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTransform(ref Transform value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTransform(Transform value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetGlobalBounds(ref Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetLocalBounds(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetLocalBounds(Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTextureSource(ref Rectf value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTextureSource(Rectf value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetTexture(ref Texture2D value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetTexture(Texture2D value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetVisible(ref bool value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetVisible(bool value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetColor(ref Color value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetColor(Color value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetEmitFunction(ref EmitFunction value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetEmitFunction(EmitFunction value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetGenerator(ref ParticleGenerator value);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void SetGenerator(ParticleGenerator value);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void GetMaxParticles(ref int value);
        #endregion

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern Particle[] GetParticles();

        [MethodImpl(MethodImplOptions.InternalCall)]
        public extern void Reset();

        public IEnumerable<Particle> Particles()
        {
            return GetParticles();
        }

        public void Destroy()
        {
            if (destroyed) return;

            Release();

            GC.SuppressFinalize(this);

            destroyed = true;
        }
    }
}
