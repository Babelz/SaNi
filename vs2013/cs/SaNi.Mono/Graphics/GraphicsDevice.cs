using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Graphics
{
    /// <summary>
    /// Reflects the engines internal graphics device implementation.
    /// 
    /// TODO: static or instances? wrap completely and document.
    /// </summary>
    public static class GraphicsDevice
    {
        public static class Samples
        {
            /// <summary>
            /// 8 samples, best quality.
            /// </summary>
            public const int BestQuality        = 8;

            /// <summary>
            /// 4 samples, balanced between quality and performance.
            /// </summary>
            public const int Balanced           = 4;

            /// <summary>
            /// 0 samples, worst quality, best performance.
            /// </summary>
            public const int BestPerformance    = 0;
        }

        /// <summary>
        /// Returns the current viewport of the device.
        /// </summary>
        /// <returns>current viewport</returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Viewport GetViewport();
        /// <summary>
        /// Sets the current viewport of the device.
        /// </summary>
        /// <param name="viewport">new value</param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetViewport(Viewport viewport);

        /// <summary>
        /// Sets the back buffer size of the device.
        /// </summary>
        /// <param name="width">new width</param>
        /// <param name="height">new height</param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetBackbufferSize(uint width, uint height);
        /// <summary>
        /// Returns the width of the back buffer.
        /// </summary>
        /// <returns>back buffer width</returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint BackbufferWidth();
        /// <summary>
        /// Returns the height of the back buffer.
        /// </summary>
        /// <returns>back buffer height</returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint BackbufferHeight();

        /// <summary>
        /// Sets the samples count. Min 0, max 8. Use samples classes
        /// predefined sample values if you don't know which amount to use.
        /// </summary>
        /// <param name="samples">count of samples</param>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void SetSamplesCount(int samples);
        /// <summary>
        /// Returns the current count of samples.
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int SamplesCount();

        /// <summary>
        /// Applies new back buffer size and samples count
        /// if they get changed.
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void ApplyBackbufferChanges();

        /// <summary>
        /// Returns true if the device is using fullscreen rendering.
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool IsFullscreen();

        /// <summary>
        /// Attempts to use fullscreen rendering. Has
        /// no effect if we already are in fullscreen state.
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Fullscreen();
        /// <summary>
        /// Attempts to use windowed rendering. Has no
        /// effect if we already are in windowed state.
        /// </summary>
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Windowed();
    }
}
