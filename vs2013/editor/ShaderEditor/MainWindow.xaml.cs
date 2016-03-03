using ICSharpCode.AvalonEdit;
using ICSharpCode.AvalonEdit.Editing;
using ICSharpCode.AvalonEdit.Highlighting;
using ICSharpCode.AvalonEdit.Highlighting.Xshd;
using OpenTK.Graphics.OpenGL4;
using ShaderEditor.Rendering;
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
        private readonly OpenTK.GLControl glControl;

        private readonly SpriteBatch spriteBatch;
        private readonly Viewport viewport;

        private IScene[] scenes;
        private Camera2D camera;
        private Effect effect;
        #endregion

        public MainWindow()
        {
            InitializeComponent();

            textEditor.TextArea.Caret.CaretBrush = new SolidColorBrush(Colors.Yellow);

            glControl = new OpenTK.GLControl(new OpenTK.Graphics.GraphicsMode(32, 24, 8, 4), 3, 0, OpenTK.Graphics.GraphicsContextFlags.Default);
            glControl.Resize    += glControl_Resize;
            glControl.Load      += glControl_Load;
            glControl.Paint     += glControl_Paint;

            glHost.Child = glControl;

            viewport = new Viewport(0, 0, glControl.Width, glControl.Height);
            camera = new Camera2D(viewport);

            spriteBatch = new SpriteBatch();
        }

        void Application_Idle(object sender, EventArgs e)
        {
            throw new NotImplementedException();
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
            scenes = new IScene[] 
            {
                new SpriteScene(),
                null
            };

            spriteBatch.Initialize();
        }
        private void glControl_Resize(object sender, EventArgs e)
        {
            viewport.Width = glControl.Width;
            viewport.Height = glControl.Height;

            GL.Viewport(viewport.X, viewport.Y, viewport.Width, viewport.Height);
        }
        private void glControl_Paint(object sender, PaintEventArgs e)
        {
            GL.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            
            GL.Clear(ClearBufferMask.ColorBufferBit);

            DrawScene();

            glControl.SwapBuffers();
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

        private void DrawScene()
        {
            var transform = camera.Transform();

            effect.Bind();

            effect.SetUniformValue("time", 0.0f, typeof(float));
            effect.SetUniformValue("transform", transform, typeof(OpenTK.Matrix4));

            spriteBatch.Begin();

            scenes[0].Draw(spriteBatch, 0.0f);

            spriteBatch.End();

            effect.Unbind();
        }
    }
}
