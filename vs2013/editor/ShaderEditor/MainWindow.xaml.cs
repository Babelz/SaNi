using ShaderEditor.GL;
using ShaderEditor.Languages;
using Syncfusion.Windows.Edit;
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

            OpenGLControl glControl = new OpenGLControl();
            glControl.OpenGLInitialized += glControl_OpenGLInitialized;
            glControl.OpenGLRender += glControl_OpenGLRender;
            glHost.Child = glControl;

            glControl.InitializeOpenGL();
            glControl.StartRendering();

            editControl.DocumentLanguage = Syncfusion.Windows.Edit.Languages.Custom;

            GLSLDesktopLanguage language = new GLSLDesktopLanguage(editControl);
            language.Lexem = Resources["GLSLDesktopLexems"] as LexemCollection;
            language.Formats = Resources["GLSLDesktopFormats"] as FormatsCollection;

            editControl.CustomLanguage = language;
        }

        private void glControl_OpenGLRender(object sender, EventArgs e)
        {
            OpenGLControl glControl = sender as OpenGLControl;

            OpenGL.GLClearColor(0.0f, 1.0f, 0.0f, 0.25f);
            
            OpenGL.GLClear(GLEnums.ColorBufferBit);
        }

        private void glControl_OpenGLInitialized(object sender, EventArgs e)
        {
        }
    }
}
