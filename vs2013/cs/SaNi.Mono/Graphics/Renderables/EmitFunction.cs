using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics.Renderables
{
    public enum EmitFunction : int
    {
        /// Emitting particles is stopped when the emitter
		/// is destroyed or when user stops it.
		Continuous = 0,

		/// Emitter will emit particles once and 
		// requires a user called reset.
		Once
    }
}
