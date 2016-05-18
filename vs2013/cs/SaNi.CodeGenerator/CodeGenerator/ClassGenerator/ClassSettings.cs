using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    [Flags()]
    public enum ClassSettings : int
    {
        None        = 0,

        Public      = 1,

        Internal    = 2,

        Private     = 4,

        Abstract    = 8,

        Sealed      = 16,

        Static      = 32,

        Ctor        = 64,

        Dtor        = 128
    }

    public static class ClassSettingsHelper
    {
        public static bool HasOneAccessModifierToggled(ClassSettings settings)
        {
            var count = 0;

            count += settings.HasFlag(ClassSettings.Private)  ? 1 : 0;
            count += settings.HasFlag(ClassSettings.Public)   ? 1 : 0;
            count += settings.HasFlag(ClassSettings.Internal) ? 1 : 0;

            return count == 1;
        }

        public static bool IsAbstract(ClassSettings settings)
        {
            return settings.HasFlag(ClassSettings.Abstract);
        }
        public static bool IsSealed(ClassSettings settings)
        {
            return settings.HasFlag(ClassSettings.Sealed);
        }

        public static string GetKeywords(ClassSettings settings)
        {
            var keywords = string.Empty;

            if ((settings & ClassSettings.Public) == ClassSettings.Public)      keywords += "public";
            if ((settings & ClassSettings.Private) == ClassSettings.Private)    keywords += "private";
            if ((settings & ClassSettings.Internal) == ClassSettings.Internal)  keywords += "internal";
            if ((settings & ClassSettings.Sealed) == ClassSettings.Sealed)      keywords += " sealed";
            if ((settings & ClassSettings.Static) == ClassSettings.Static)      keywords += " static";
            if ((settings & ClassSettings.Abstract) == ClassSettings.Abstract)  keywords += " abstract";
            
            return keywords.Trim();
        }

        public static bool ShouldGenerateCtor(ClassSettings settings)
        {
            return settings.HasFlag(ClassSettings.Ctor);
        }
        public static bool ShouldGenerateDtor(ClassSettings settings)
        {
            return settings.HasFlag(ClassSettings.Dtor);
        }
    }
}
