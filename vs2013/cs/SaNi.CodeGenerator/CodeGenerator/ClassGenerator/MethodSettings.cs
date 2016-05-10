using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SaNi.CodeGenerator.ClassGenerator
{
    [Flags()]
    public enum MethodSettings : byte
    {
        Private         = 1,
        
        Public          = 2,
        
        Protected        = 4,
        
        Abstract        = 8,
        
        InternalCall    = 16,
        
        Static          = 32,

        Inline          = 64
    }

    public static class MethodSettingsHelper
    {
        public static string GetAttributes(MethodSettings settings)
        {
            if ((settings & MethodSettings.InternalCall) == MethodSettings.InternalCall)    return "[MethodImpl(MethodImplOptions.InternalCall)]";
            if ((settings & MethodSettings.Inline) == MethodSettings.Inline)                return "[MethodImpl(MethodImplOptions.AggressiveInlining)]";

            return string.Empty;
        }
        public static string GetAccessModifier(MethodSettings settings)
        {
            if ((settings & MethodSettings.Private) == MethodSettings.Private)     return "private";
            if ((settings & MethodSettings.Public) == MethodSettings.Public)       return "public";
            if ((settings & MethodSettings.Protected) == MethodSettings.Protected) return "protected";

            throw new InvalidOperationException("invalid value");
        }
        public static string GetMethodBody(MethodSettings settings)
        {
            if ((settings & MethodSettings.Abstract) == MethodSettings.Abstract)            return ";";
            if ((settings & MethodSettings.InternalCall) == MethodSettings.InternalCall)    return ";";
            else                                                                            return "\n{\n}";
        
            throw new InvalidOperationException("invalid value");
        }
        public static string GetKeywords(MethodSettings settings)
        {
            var keywords = string.Empty;

            if ((settings & MethodSettings.InternalCall) == MethodSettings.InternalCall)    keywords += "extern";
            if ((settings & MethodSettings.Abstract) == MethodSettings.Abstract)            keywords += " abstract";
            if ((settings & MethodSettings.Static) == MethodSettings.Static)                keywords += " static";

            return keywords.Trim();
        }

        public static bool HasOneAccessModifierToggled(MethodSettings settings)
        {
            var count = 0;

            count += settings.HasFlag(MethodSettings.Private)   ? 1 : 0;
            count += settings.HasFlag(MethodSettings.Public)    ? 1 : 0;
            count += settings.HasFlag(MethodSettings.Protected) ? 1 : 0;

            return count == 1;
        }
        public static bool IsInternalCall(MethodSettings settings)
        {
            return settings.HasFlag(MethodSettings.InternalCall);
        }
        public static bool IsStatic(MethodSettings settings)
        {
            return settings.HasFlag(MethodSettings.Static);
        }
        public static bool IsAbstract(MethodSettings settings)
        {
            return settings.HasFlag(MethodSettings.Abstract);
        }
    }
}
