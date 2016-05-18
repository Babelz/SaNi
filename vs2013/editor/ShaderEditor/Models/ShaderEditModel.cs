using ICSharpCode.AvalonEdit.Document;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShaderEditor.Models
{
    public sealed class ShaderEditModel : INotifyPropertyChanged
    {
        #region Fields
        private TextDocument vertexSource;
        private TextDocument fragmentSource;
        #endregion

        #region Events
        public event PropertyChangedEventHandler PropertyChanged;
        #endregion

        #region Properties
        public TextDocument VertexSource
        {
            get
            {
                return vertexSource;
            }
            set
            {
                vertexSource = value;

                OnPropertyChanged("VertexSource");
            }
        }
        public TextDocument FragmentSource
        {
            get
            {
                return fragmentSource;
            }
            set
            {
                fragmentSource = value;

                OnPropertyChanged("FragmentSource");
            }
        }
        #endregion

        public ShaderEditModel()
        {
            vertexSource = new TextDocument();
            fragmentSource = new TextDocument();
        }

        private void OnPropertyChanged(string name)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(name));
        }
    }
}
