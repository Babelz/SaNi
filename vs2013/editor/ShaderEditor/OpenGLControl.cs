using ShaderEditor.GL;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ShaderEditor
{
    internal sealed class OpenGLControl : UserControl
    {
        #region Const fields
        public int MaxFps = 0;
        #endregion

        #region Fields
        private readonly Stopwatch renderTimeMeasurer;
        private readonly Timer renderTimer;

        private int preferedFPS;
        private double frameTime;
        #endregion 

        #region Properties
        /// <summary>
        /// Sets the prefered FPS. Setting the value to 0 or 
        /// using the MaxFPS const causes the control
        /// to render with no FPS limit.
        /// </summary>
        public int PreferedFPS
        {
            get
            {
                return preferedFPS;
            }
            set
            {
                this.preferedFPS = value;

                SetupRenderingTimer();
            }
        }
        /// <summary>
        /// Returns the last frames FPS.
        /// </summary>
        public int FPS
        {
            get
            {
                return (int)(1000.0 / frameTime);
            }
        }
        #endregion

        #region Events
        public event InitializeEventHandler OpenGLInitialized;
        public event RenderEventHandler OpenGLRender;
        #endregion

        public OpenGLControl()
            : base()
        {
            DoubleBuffered = false;

            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.UserPaint, true);

            renderTimeMeasurer = new Stopwatch();
            renderTimer = new Timer();

            PreferedFPS = 60;
        }

        #region Event handler
        private void renderTimer_Tick(object sender, EventArgs e)
        {
            Invalidate();
        }
        #endregion

        private void Render(Graphics graphics)
        {
            renderTimeMeasurer.Restart();

            // Allow user to draw using OpenGL.
            if (OpenGLRender != null) OpenGLRender(this, RenderingEventArgs.Empty);

            // Draw.
            var handleDeviceContext = graphics.GetHdc();

            OpenGL.SwapBuffers((uint)handleDeviceContext);

            graphics.ReleaseHdc(handleDeviceContext);

            renderTimeMeasurer.Stop();

            frameTime = renderTimeMeasurer.Elapsed.TotalMilliseconds;
        }

        private void SetupRenderingTimer()
        {
            var interval = (int)(1000.0 / (double)PreferedFPS);
            interval = interval == 0 ? 1 : interval;

            renderTimer.Interval = interval;

            if (!renderTimer.Enabled)
            {
                renderTimer.Tick += renderTimer_Tick;
                renderTimer.Enabled = true;

                renderTimer.Start();
            }
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            Render(e.Graphics);
        }
        protected override void OnPaintBackground(PaintEventArgs e)
        {
            // Do an empty override as this causes flickering...
        }
        protected override void OnSizeChanged(EventArgs e)
        {
            base.OnSizeChanged(e);

            OpenGL.GLViewport(0, 0, (uint)Width, (uint)Height);

            Invalidate();
        }

        public void InitializeOpenGL()
        {
            var handle = this.Handle;

            OpenGL.CreateContext(handle);
            OpenGL.GLEnable(GLEnums.Blend);
            OpenGL.GLEnable(GLEnums.Alpha);
            OpenGL.GLBlendFunc(GLEnums.SrcAlpha, GLEnums.OneMinusSrcAlpha);
            
            if (OpenGLInitialized != null) OpenGLInitialized(this, InitializationEventArgs.Empty);
        }
        public void StartRendering()
        {
            SetupRenderingTimer();
        }
    }
}
