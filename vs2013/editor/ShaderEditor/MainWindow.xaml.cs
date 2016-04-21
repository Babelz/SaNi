using ICSharpCode.AvalonEdit;
using ICSharpCode.AvalonEdit.Document;
using ICSharpCode.AvalonEdit.Editing;
using ICSharpCode.AvalonEdit.Highlighting;
using ICSharpCode.AvalonEdit.Highlighting.Xshd;
using ShaderEditor.Drawing;
using ShaderEditor.Models;
using ShaderEditor.Scenes;
using ShaderEditor.Scenes.OpenGL;
using ShaderEditor.Shaders;
using ShaderEditor.Shaders.OpenGL;
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
        #region Constants
        private const int RecompilationDelayMillis = 1250;
        #endregion

        #region GLSL versions
        private static readonly string GLSLDesktop = "GLSL Desktop";
        #endregion

        #region Fields
        private readonly Stopwatch renderTimeMeasurer;
        private readonly OpenTK.GLControl glControl;

        private float total;

        // Current scene.
        private IScene scene;
        // Current effect.
        private IEffect effect;

        private EffectCompilers compilers;

        private SourceEditTimer sourceEditTimer;
        private System.Threading.Timer recompileTimer;

        private ShadingLanguages targetLanguage;

        private ShaderEditModel shaderEditModel;
        #endregion

        public MainWindow()
        {
            InitializeComponent();

            textEditor.TextArea.Caret.CaretBrush = new SolidColorBrush(Colors.Yellow);

            glControl = new OpenTK.GLControl(new OpenTK.Graphics.GraphicsMode(32, 24, 8, 4));
            glControl.Load      += glControl_Load;
            glControl.Paint     += glControl_Paint;

            glHost.Child = glControl;

            renderTimeMeasurer = Stopwatch.StartNew();

            sourceEditTimer = new SourceEditTimer(RecompilationDelayMillis);
            
            compilers = new EffectCompilers();

            targetLanguage = ShadingLanguages.GLSL;
        }

        #region GLControl event handlers
        private void glControl_Load(object sender, EventArgs e)
        {
            // Load syntax.
            using (var reader = new XmlTextReader("languages\\" + GLSLDesktop + ".xshd"))
            {
                textEditor.SyntaxHighlighting = HighlightingLoader.Load(reader, HighlightingManager.Instance);
            }

            // Load the default scene.
            // TODO: start args.
            scene = new GLPlaneScene(glControl);
            scene.Texture = Texture2D.LoadFromFile("Textures\\sani.png");
        }
        private void glControl_Paint(object sender, PaintEventArgs e)
        {
            var delta = (float)renderTimeMeasurer.Elapsed.TotalMilliseconds;

            total += delta;

            scene.Draw(delta, total);

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

        #region Text editor event handlers
        private void textEditor_TextChanged(object sender, EventArgs e)
        {
            sourceEditTimer.StartMeasuring();

            if (recompileTimer == null)
            {
                recompileTimer = new System.Threading.Timer(CheckIfShouldRecompileShaders, null, 0, RecompilationDelayMillis);
            }
        }
        #endregion

        #region Main window event handlers
        private void mainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            // TODO: for testing.
            // Load default effect.
            
            var vertexSource = DefaultShaderSources.DefaultVertexShaderSource();
            var fragmentSource = DefaultShaderSources.DefaultFragmentShaderSource();

            RecompileShaders(vertexSource, fragmentSource);

            // Setup model.
            shaderEditModel = new ShaderEditModel();
            shaderEditModel.VertexSource = new TextDocument(vertexSource);
            shaderEditModel.FragmentSource = new TextDocument(fragmentSource);
            textEditor.DataContext = shaderEditModel;

            var binding = new System.Windows.Data.Binding("FragmentSource");
            binding.Source = shaderEditModel;
            textEditor.SetBinding(TextEditor.DocumentProperty, binding);

            scene.Effect = effect;
        }
        #endregion

        // Callback so we can recompile shaders when enough time has passed
        // since last edit.
        private void CheckIfShouldRecompileShaders(object state)
        {
            if (!sourceEditTimer.ShouldRecompile) return;

            mainWindow.Dispatcher.Invoke(() =>
            {
                RecompileShaders(shaderEditModel.VertexSource.Text, shaderEditModel.FragmentSource.Text);

                recompileTimer = null;
            });
        }
        private void RecompileShaders(string vertexSource, string fragmentSource)
        {
            effect = compilers.Compile(targetLanguage, vertexSource, fragmentSource);

            if (compilers.HasErrors(targetLanguage))
            {
                var vertexError = string.Empty;
                var fragmentError = string.Empty;

                compilers.GetLastErrors(targetLanguage, ref vertexError, ref fragmentError);

                // TODO: present errors.
            }

            scene.Effect = effect;
        }
    }
}
