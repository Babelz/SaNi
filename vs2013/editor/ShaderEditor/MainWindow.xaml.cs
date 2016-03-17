using ICSharpCode.AvalonEdit;
using ICSharpCode.AvalonEdit.Editing;
using ICSharpCode.AvalonEdit.Highlighting;
using ICSharpCode.AvalonEdit.Highlighting.Xshd;
using OpenTK.Graphics.OpenGL;
using ShaderEditor.Scenes;
using ShaderEditor.Shaders;
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

        #region Fields
        private readonly Stopwatch renderTimeMeasurer;
        private readonly OpenTK.GLControl glControl;

        private Scene[] scenes;
        private Effect effect;
        #endregion

        public MainWindow()
        {
            InitializeComponent();

            textEditor.TextArea.Caret.CaretBrush = new SolidColorBrush(Colors.Yellow);

            glControl = new OpenTK.GLControl(new OpenTK.Graphics.GraphicsMode(32, 24, 8, 4));
            glControl.Resize    += glControl_Resize;
            glControl.Load      += glControl_Load;
            glControl.Paint     += glControl_Paint;

            glHost.Child = glControl;

            renderTimeMeasurer = Stopwatch.StartNew();
        }

        #region GLControl event handlers
        private void glControl_Load(object sender, EventArgs e)
        {
            // Load syntax.
            using (var reader = new XmlTextReader("languages\\" + GLSLDesktop + ".xshd"))
            {
                textEditor.SyntaxHighlighting = HighlightingLoader.Load(reader, HighlightingManager.Instance);
            }

            // Generate scenes.
            scenes = new Scene[] 
            {
                new SpriteScene(),
                null
            };
        }
        private void glControl_Resize(object sender, EventArgs e)
        {
            scenes[0].Resize(glControl.Width, glControl.Height);
        }
        private void glControl_Paint(object sender, PaintEventArgs e)
        {
            var delta = (float)renderTimeMeasurer.ElapsedMilliseconds;

            scenes[0].Draw(delta);

            renderTimeMeasurer.Restart();

            glControl.Invalidate();
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

        #region Main window event handlers
        private void mainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            // TODO: for testing.
            // Load default effect.
            effect = new Effect(DefaultShaderSources.DefaultVertexShaderSource(),
                                DefaultShaderSources.DefaultFragmentShaderSource());

            if (!effect.Compile())
            {
                if (!string.IsNullOrEmpty(effect.LastFragmentError)) System.Windows.MessageBox.Show(effect.LastFragmentError);
                if (!string.IsNullOrEmpty(effect.LastVertexError)) System.Windows.MessageBox.Show(effect.LastVertexError);
            }
        }
        #endregion
    }
}
