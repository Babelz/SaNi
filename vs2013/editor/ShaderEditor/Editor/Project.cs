using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Editor
{
    internal sealed class Project
    {
        #region Properties
        public string SourcePath
        {
            get;
            set;
        }
        public bool Saved
        {
            get
            {
                return !string.IsNullOrEmpty(SourcePath);
            }
        }
        public bool ChangesSaved
        {
            get;
            set;
        }
        #endregion

        public Project()
        {
        }
    }
}
