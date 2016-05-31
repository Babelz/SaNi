using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.Mono.Configuration
{
    public static class EngineCVars
    {
        #region Fields
        public static readonly string WindowWidth           = "window_width";
        public static readonly string WindowHeight          = "window_height";

        public static readonly string BackBufferWidth       = "backbuffer_width";
        public static readonly string BackBufferHeight      = "backbuffer_height";

        public static readonly string StretchBackbuffer     = "stretch_backbuffer";

        public static readonly string UserServices          = "user_services";

        public static readonly string MonoAssemblyName      = "mono_assembly_name";
        public static readonly string MonoDependencies      = "mono_dependencies";
        public static readonly string MonoAssembliesPath    = "mono_assemblies_path";
        public static readonly string MonoLibrariesPath     = "mono_libraries_path";
        public static readonly string MonoConfigPath        = "mono_config_path";

        public static readonly string ConsoleAtStartup      = "sys_console_at_startup";
        public static readonly string ConsoleVisible        = "sys_console_visible";
        public static readonly string ConsoleWidth          = "sys_console_width";
        public static readonly string ConsoleHeight         = "sys_console_height";
        #endregion
    }
}
