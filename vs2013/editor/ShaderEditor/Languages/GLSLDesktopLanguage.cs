using Syncfusion.Windows.Edit;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace ShaderEditor.Languages
{
    internal sealed class GLSLDesktopLanguage : ProceduralLanguageBase
    {
        public GLSLDesktopLanguage(EditControl control)
            : base(control)
        {
            Name                    = "GLSL Desktop";
            FileExtension           = "glsl";
            ApplyColoring           = true;
            SupportsOutlining       = false;
            SupportsIntellisense    = true;
        }
    }
}
