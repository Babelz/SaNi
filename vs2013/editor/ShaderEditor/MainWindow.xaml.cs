using ICSharpCode.AvalonEdit;
using ICSharpCode.AvalonEdit.Editing;
using ICSharpCode.AvalonEdit.Highlighting;
using ICSharpCode.AvalonEdit.Highlighting.Xshd;
using ShaderEditor.GL;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Text;
using System.Text.RegularExpressions;
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
using System.Xml;

namespace ShaderEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region GLSL versions
        private static readonly string GLSLDesktop = "GLSL Desktop";
        #endregion

        public MainWindow()
        {
            InitializeComponent();

            textEditor.TextArea.Caret.CaretBrush = new SolidColorBrush(Colors.Yellow);

            var glControl = new OpenGLControl();
            glControl.OpenGLInitialized += glControl_OpenGLInitialized;
            glControl.OpenGLRender += glControl_OpenGLRender;
            glHost.Child = glControl;

            glControl.InitializeOpenGL();
            glControl.StartRendering();
        }

        #region GLControl events
        private void glControl_OpenGLRender(object sender, EventArgs e)
        {
            var glControl = sender as OpenGLControl;

            OpenGL.GLClearColor(0.0f, 1.0f, 0.0f, 0.25f);
            
            OpenGL.GLClear(GLEnums.ColorBufferBit);
        }

        private void glControl_OpenGLInitialized(object sender, EventArgs e)
        {
            using (var reader = new XmlTextReader("languages\\" + GLSLDesktop + ".xshd"))
            {
                textEditor.SyntaxHighlighting = HighlightingLoader.Load(reader, HighlightingManager.Instance);
            }
        }
        #endregion

        #region Shader menu event handlers
        private void shaderMenuNew_Click(object sender, RoutedEventArgs e)
        {
            // TODO: new "project".
        }
        private void shaderMenuLoad_Click(object sender, RoutedEventArgs e)
        {
            // TODO: load existing shader source.
        }
        private void shaderMenuSave_Click(object sender, RoutedEventArgs e)
        {
            // TODO: save existing shader source.
        }
        private void shaderMenuSaveAs_Click(object sender, RoutedEventArgs e)
        {
            // TODO: save existing shader source as.
        }
        private void shaderMenuExitEditor_Click(object sender, RoutedEventArgs e)
        {
            // TODO: exit the program.
        }
        #endregion

        #region Settings menu event handlers
        private void settingsMenuTextEditor_Click(object sender, RoutedEventArgs e)
        {
        }
        private void settingsMenuPreview_Click(object sender, RoutedEventArgs e)
        {
        }
        #endregion

        #region About menu event handlers
        private void menuAbout_Click(object sender, RoutedEventArgs e)
        {

        }
        #endregion
    }
}
