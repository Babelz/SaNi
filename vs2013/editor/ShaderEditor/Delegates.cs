using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor
{
    internal delegate void InitializeEventHandler(object sender, InitializationEventArgs e);
    internal delegate void RenderEventHandler(object sender, RenderingEventArgs e);
}
