using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor
{
    public sealed class InitializationEventArgs : EventArgs
    {
        public static readonly new InitializationEventArgs Empty = new InitializationEventArgs();

        public InitializationEventArgs()
            : base()
        {
        }
    }

    public sealed class RenderingEventArgs : EventArgs
    {
        public static readonly new RenderingEventArgs Empty = new RenderingEventArgs();

        public RenderingEventArgs()
            : base()
        {
        }
    }
}
