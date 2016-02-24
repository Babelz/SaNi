using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SyntaxDefinitionBuilder.Avalon
{
    public static class AvalonCommon
    {
        #region Avalon strings

        /// <summary>
        /// Avalon XMLNS.
        /// </summary>
        public static string AvalonXMLNS = "http://icsharpcode.net/sharpdevelop/syntaxdefinition/2008";

        /// <summary>
        /// Format used to create XSHD file headers.
        /// {0} = language name
        /// {1} = xmlns
        /// </summary>
        public static string XSHDFileRoot = "<SyntaxDefinition name=\"{0}\" xmlns=\"{1}\">";

        /// <summary>
        /// Closing tag for the file header (root), does not require formatting.
        /// </summary>
        public static string XSHDFileRootEnding = "</SyntaxDefinition>";

        /// <summary>
        /// Rule set root. No formatting required.
        /// </summary>
        public static string XSHDRuleSetRoot = "<RuleSet>";

        /// <summary>
        /// Rule set closing tag, no formatting required.
        /// </summary>
        public static string XSHDRuleSetEnding = "</RuleSet>";

        /// <summary>
        /// Format to create color definitions inside the rule set.
        /// {0} = name
        /// {1} = foreground (color)
        /// </summary>
        public static string XSHDColorDefinition = "<Color name=\"{0}\" foreground=\"{1}\"/>";

        /// <summary>
        /// Defines root for keyword definitions.
        /// {0} = font weight
        /// {1} = foreground (color)
        /// </summary>
        public static string XSHDKeywords = "<Keywords fontWeight=\"{0}\" foreground=\"{1}\">";

        /// <summary>
        /// Closing tag for keywords.
        /// </summary>
        public static string XSHDKeywordsEnd = "</Keywords>";

        /// <summary>
        /// Defines XSHD keyword.
        /// {0} = keyword
        /// </summary>
        public static string XSHDKeyword = "<Word>{0}</Word>";

        /// <summary>
        /// Defines single line XSHD span with color name and begin argument.
        /// {0} = color name
        /// {1} = begin token
        /// </summary>
        public static string XSHDSingleLineSpan = "<Span color=\"{0}\" begin=\"{1}\"/>";

        /// <summary>
        /// Defines multi line XSHD span with color name, begin and end argument.
        /// {0} = color name
        /// {1} = begin token
        /// {2] = end token
        /// </summary>
        public static string XSHDMultilineSpan = "<Span color=\"{0}\" begin=\"{1}\" end=\"{2}\" multiline=\"true\"/>";

        #endregion
    }
}
