using SyntaxDefinitionBuilder.Avalon;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SyntaxDefinitionBuilder.GLSL
{
    public sealed class GLSLDesktopBuilder
    {
        public GLSLDesktopBuilder()
        {
        }

        private void GenerateColors(List<string> lines)
        {
            lines.Add(string.Format(AvalonCommon.XSHDColorDefinition, "Comment", "Green"));
        }

        private void GenerateKeywords(List<string> lines, string weight, string color, string source)
        {
            lines.Add(string.Format(AvalonCommon.XSHDKeywords, weight, color));

            var tokens = source.Split(new [] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

            for (int i = 0; i < tokens.Length; i++)
            {
                var line = tokens[i];

                line = line.Trim();

                lines.Add(string.Format(Avalon.AvalonCommon.XSHDKeyword, line));
            }

            lines.Add(AvalonCommon.XSHDKeywordsEnd);
        }
        
        private void GenerateStorageQualifiers(List<string> lines)
        {
            GenerateKeywords(lines, "bold", "Purple", GLSLLanguage.DesktopStorageQualifiers);
        }
        private void GenerateBuiltInTypes(List<string> lines)
        {
            GenerateKeywords(lines, "bold", "Orange", GLSLLanguage.DesktopTypes);
        }
        private void GenerateLanguageKeywords(List<string> lines)
        {
            GenerateKeywords(lines, "bold", "MintCream", GLSLLanguage.DesktopTypes);
        }

        private void GenerateKeywords(List<string> lines)
        {
            // Handle storq, types and real keywords as keywords.
            GenerateStorageQualifiers(lines);
            GenerateBuiltInTypes(lines);
            GenerateLanguageKeywords(lines);
        }
        private void GenerateRules(List<string> lines)
        {
            lines.Add(string.Format(AvalonCommon.XSHDSingleLineSpan, "Comment", GLSLLanguage.SingleLineComment));
            lines.Add(string.Format(AvalonCommon.XSHDMultilineSpan, "Comment", GLSLLanguage.MultiLineCommentBegin, GLSLLanguage.MultiLineCommentEnd));
        }

        private void GenerateRuleSet(List<string> lines)
        {
            lines.Add(AvalonCommon.XSHDRuleSetRoot);

            GenerateRules(lines);
            GenerateKeywords(lines);

            lines.Add(AvalonCommon.XSHDRuleSetEnding);
        }

        private void AddRoot(List<string> lines)
        {
            lines.Insert(0, string.Format(Avalon.AvalonCommon.XSHDFileRoot, "GLSL", Avalon.AvalonCommon.AvalonXMLNS));
        }
        private void AddRootClosingTag(List<string> lines)
        {
            lines.Insert(lines.Count, Avalon.AvalonCommon.XSHDFileRootEnding);
        }

        public List<string> BuildSyntaxDefinition()
        {
            var lines = new List<string>();

            GenerateColors(lines);
            GenerateRuleSet(lines);

            AddRoot(lines);
            AddRootClosingTag(lines);

            return lines;
        }
    }
}
