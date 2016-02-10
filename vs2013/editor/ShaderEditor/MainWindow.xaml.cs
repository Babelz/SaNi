using ShaderEditor.GL;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ShaderEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            OpenGLControl glControl = new OpenGLControl();
            glControl.OpenGLInitialized += glControl_OpenGLInitialized;
            glControl.OpenGLRender += glControl_OpenGLRender;
            glHost.Child = glControl;

            glControl.InitializeOpenGL();
            glControl.StartRendering();
        }

        private void glControl_OpenGLRender(object sender, EventArgs e)
        {
            OpenGLControl glControl = sender as OpenGLControl;

            OpenGL.GLClearColor(0.0f, 0.20f, 0.0f, 1.0f);
            
            OpenGL.GLClear(GL_ENUMS.GL_COLOR_BUFFER_BIT);
        }

        private void glControl_OpenGLInitialized(object sender, EventArgs e)
        {
        }
    }
}
