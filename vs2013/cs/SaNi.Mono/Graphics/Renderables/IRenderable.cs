using SaNi.Mono.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    /// <summary>
    /// Interface for everything that can be rendered
    /// using the engines internal rendering system.
    /// </summary>
    public interface IRenderable
    {
        #region Properties
        Transform Transform
        {
            get;
            set;
        }
        /// <summary>
        /// Local bounds of the renderable, not affected
        /// by any transformations.
        /// </summary>
        Rectf LocalBounds
        {
            get;
            set;
        }
        /// <summary>
        /// Global bounds of the renderable, affected
        /// by scale and position.
        /// </summary>
        Rectf GlobalBounds
        {
            get;
        }
        /// <summary>
        /// Texture source of the renderable.
        /// </summary>
        Rectf TextureSource
        {
            get;
            set;
        }
        /// <summary>
        /// Texture the renderable is presenting.
        /// This value can be null for some renderables.
        /// </summary>
        Texture2D Texture
        {
            get;
            set;
        }
        /// <summary>
        /// Identifier of the renderable. ID is generated during the 
        /// runtime and it is used by the engines internals.
        /// </summary>
        int ID
        {
            get;
        }
        bool Visible
        {
            get;
            set;
        }
        #endregion

        void Destroy();
    }
}
