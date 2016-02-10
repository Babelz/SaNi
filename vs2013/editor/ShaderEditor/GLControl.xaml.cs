using ShaderEditor.GL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ShaderEditor
{
    /// <summary>
    /// Interaction logic for GLControl.xaml
    /// </summary>
    public partial class GLControl : UserControl
    {
        #region Private GLForm class
        private sealed class GLForm : System.Windows.Forms.Form
        {
            #region Fields
            private readonly System.Windows.Forms.Timer renderTimer;
            #endregion

            #region Properties
            public uint DeviceContextLocation
            {
                get;
                set;
            }
            #endregion

            public GLForm()
                : base()
            {
                renderTimer = new System.Windows.Forms.Timer();
                renderTimer.Interval = 16;
                renderTimer.Tick += renderTimer_Tick;
                renderTimer.Start();
            }

            private void renderTimer_Tick(object sender, EventArgs e)
            {
                Refresh();
            }

            protected override void OnPaintBackground(System.Windows.Forms.PaintEventArgs e)
            {
            }

            [System.Security.Permissions.PermissionSet(System.Security.Permissions.SecurityAction.Demand, Name="FullTrust")]
            protected override void WndProc(ref System.Windows.Forms.Message m)
            {
                if (m.Msg == 0x14) // Filter out the WM_ERASEBACKGROUND
                {
                    return;
                }

                base.WndProc(ref m);
            }

            protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
            {
                OpenGL.GLClearColor(1.0f, 0.0f, 0.0f, 1.0f);

                OpenGL.SwapBuffers(DeviceContextLocation);

                OpenGL.GLClear(GL_ENUMS.GL_COLOR_BUFFER_BIT | GL_ENUMS.GL_DEPTH_BUFFER_BIT);
            }
        }
        #endregion

        #region Fields
        private GLForm glForm;
        #endregion

        public GLControl()
        {
            InitializeComponent();

            InitializeForm();
        }

        #region Form event handlers
        private void form_Load(object sender, EventArgs e)
        {
            // Create context when form is being loaded.
            IntPtr handle = glForm.Handle;
            
            OpenGL.CreateContext(handle);

            // Capture location.
            glForm.DeviceContextLocation = (uint)OpenGL.GetDC(glForm.Handle);

            glForm.Load -= form_Load;
        }
        #endregion

        #region GLControl event handlers
        private void glControl_SizeChanged(object sender, SizeChangedEventArgs e)
        {
            // Resize the form.
            glForm.Size = new System.Drawing.Size((int)ActualWidth, (int)ActualHeight);
            
            // Update viewport.
            OpenGL.GLViewport(0, 0, (uint)glForm.Width, (uint)glForm.Height);
        }
        #endregion

        private void InitializeForm()
        {
            glForm = new GLForm();
            glForm.TopLevel = false;
            glForm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            glForm.Load += form_Load;

            // Set child for the host.
            formHost.Child = glForm;
        }
    }
}
