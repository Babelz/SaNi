using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ShadingLanguageParser
{
    internal sealed class Program
    {
        // GLSL 4.5 spec at:
        // https://www.opengl.org/registry/doc/GLSLangSpec.4.50.diff.pdf

        #region Static fields
        private static readonly string GLSLDesktopKeywords =
            @"attribute const uniform varying buffer shared
              coherent volatile restrict readonly writeonly
              layout
              flat smooth noperspective
              patch sample
              break continue do for while switch case default
              if else
              subroutine
              invariant precise
              discard return
              lowp mediump highp precision
              true false
              struct";

        private static readonly string GLSLDesktopStorageQualifiers =
            @"const in out attribute uniform varying
              buffer shared centroid sample patch
              inout";

        private static readonly string GLSLDesktopTypes =
            @"uint uvec2 uvec3 uvec4 atomic_uint
              mat2 mat3 mat4 dmat2 dmat3 dmat4
              mat2x2 mat2x3 mat2x4 dmat2x2 dmat2x3 dmat2x4
              mat3x2 mat3x3 mat3x4 dmat3x2 dmat3x3 dmat3x4
              mat4x2 mat4x3 mat4x4 dmat4x2 dmat4x3 dmat4x4
              vec2 vec3 vec4 ivec2 ivec3 ivec4 bvec2 bvec3 bvec4 dvec2 dvec3 dvec4
              float double int void bool
              sampler1D sampler2D sampler3D samplerCube
              sampler1DShadow sampler2DShadow samplerCubeShadow
              sampler1DArray sampler2DArray
              sampler1DArrayShadow sampler2DArrayShadow
              isampler1D isampler2D isampler3D isamplerCube
              isampler1DArray isampler2DArray
              usampler1D usampler2D usampler3D usamplerCube
              usampler1DArray usampler2DArray
              sampler2DRect sampler2DRectShadow isampler2DRect usampler2DRect
              samplerBuffer isamplerBuffer usamplerBuffer
              sampler2DMS isampler2DMS usampler2DMS
              sampler2DMSArray isampler2DMSArray usampler2DMSArray
              samplerCubeArray samplerCubeArrayShadow isamplerCubeArray usamplerCubeArray
              image1D iimage1D uimage1D
              image2D iimage2D uimage2D
              image3D iimage3D uimage3D
              image2DRect iimage2DRect uimage2DRect
              imageCube iimageCube uimageCube
              imageBuffer iimageBuffer uimageBuffer
              image1DArray iimage1DArray uimage1DArray
              image2DArray iimage2DArray uimage2DArray
              imageCubeArray iimageCubeArray uimageCubeArray
              image2DMS iimage2DMS uimage2DMS
              image2DMSArray iimage2DMSArray uimage2DMSArray";

        private static readonly string SingleLineComment        = @"//";
        private static readonly string MultiLineCommentBegin    = "/*";
        private static readonly string MultiLineCommentEnd      = "*/";
        #endregion

        #region Static helper strings
        private static readonly string XMLNS            = "http://schemas.microsoft.com/winfx/2006/xaml/presentation";
        private static readonly string XMLNSX           = "http://schemas.microsoft.com/winfx/2006/xaml";
        private static readonly string SysFusionXMLSN   = "http://schemas.syncfusion.com/wpf";

        private static readonly string LexemFormat = "<syncfusion:Lexem StartText=\"{0}\" ContainsEndText=\"{1}\" IsMultiline=\"{2}\" LexemType=\"{3}\"  FormatName=\"{4}\"/>";

        private static readonly string ResourceDictionaryFormat =
            "<ResourceDictionary xmlns=\"{0}\"\r\n" +
                    "xmlns:x=\"{1}\"\r\n" +
                    "xmlns:syncfusion=\"{2}\">\r\n" +
                "<syncfusion:FormatsCollection x:Key=\"{3}\">\r\n" +
                        "{4}" +
                "</syncfusion:FormatsCollection>\r\n" +
                "<syncfusion:LexemCollection x:Key=\"{5}\">\r\n" +
                        "{6}\r\n" +
                "</syncfusion:LexemCollection>\r\n" +
            "</ResourceDictionary>";
        #endregion

        private static void Main(string[] args)
        {
            // Build GLSL 2.1 and GLSL 4.5 language specifications 
            // to match the XML format required.
            var result = BuildGLSLForDesktop();
            
            File.WriteAllText(@"C:\Users\NikoSal\Source\Repos\SaNi-Mastah\vs2013\editor\ShaderEditor\out_paska.txt", result);
        }

        private static string[] SplitAndPreprocess(string str)
        {
            var lines = str.Split(new string[] { " " }, StringSplitOptions.RemoveEmptyEntries);

            for (var i = 0; i < lines.Length; i++)
            {
                var line = lines[i];

                line = line.Replace('\r', ' ');
                line = line.Replace('\n', ' ');
                line = line.Trim();

                lines[i] = line;
            }

            return lines;
        }
        private static void CollapseTo(string[] from, ref string to)
        {
            foreach (var str in from) to += str + "\r\n";
        }
        private static string FormatLexem(string token, string strBoolContainsEnd, string strBoolIsMultiline, string lexemType, string formatName)
        {
            return string.Format(LexemFormat, token, strBoolContainsEnd, strBoolIsMultiline, lexemType, formatName);
        } 

        #region GLSL
        private static string BuildGLSLForDesktop()
        {
            var storageQualifiers   = CreateGLSLDesktopStorageQualifiers();
            var keywords            = CreateDesktopGLSLKeywords();
            var types               = CreateDesktopGLSLTypes();
            var formats             = CreateGLSLFormats();
            var comments            = CreateGLSLComments();

            var collapsedLexems     = string.Empty;

            CollapseTo(storageQualifiers, ref collapsedLexems);
            CollapseTo(keywords, ref collapsedLexems);
            CollapseTo(types, ref collapsedLexems);
            CollapseTo(comments, ref collapsedLexems);

            var collapsedFormats    = string.Empty;

            CollapseTo(formats, ref collapsedFormats);

            var formatsKey          = "GLSLDesktopFormats";
            var lexemsKey           = "GLSLDesktopLexems";

            return string.Format(ResourceDictionaryFormat, XMLNS, XMLNSX, SysFusionXMLSN, formatsKey, collapsedFormats, lexemsKey, collapsedLexems);
        }

        private static string[] CreateGLSLFormats()
        {
            return new[]
            {
                    "<syncfusion:EditFormats Foreground=\"Green\" FormatName=\"CommentFormat\"/>\r\n",
                    "<syncfusion:EditFormats Foreground=\"Green\" FormatName=\"MultilineCommentFormat\"/>\r\n",
                    "<syncfusion:EditFormats Foreground=\"Blue\" FormatName=\"KeywordFormat\"/>\r\n",
                    "<syncfusion:EditFormats Foreground=\"Orange\" FormatName=\"TypeFormat\"/>\r\n",
                    "<syncfusion:EditFormats Foreground=\"Red\" FormatName=\"StorageQualifierFormat\"/>\r\n"
            };
        }
        private static string[] CreateDesktopGLSLTypes()
        {
            var lines = SplitAndPreprocess(GLSLDesktopTypes);

            ConvertToXML(lines, "Keyword", "TypeFormat");

            return lines;
        }
        private static string[] CreateDesktopGLSLKeywords()
        {
            var lines = SplitAndPreprocess(GLSLDesktopKeywords);
            
            ConvertToXML(lines, "Keyword", "KeywordFormat");

            return lines;
        }
        private static string[] CreateGLSLComments()
        {
            return new[]
            {
                "<syncfusion:Lexem StartText=\"//\" EndText=\"\\r\\n\" IsMultiline=\"False\" ContainsEndText=\"True\" LexemType=\"Comment\" FormatName=\"CommentFormat\"/>",
                "<syncfusion:Lexem StartText=\"/*\" EndText=\"*/\" IsMultiline=\"True\" ContainsEndText=\"True\" LexemType=\"Comment\" FormatName=\"CommentFormat\"/>"
            };
        }
        private static string[] CreateGLSLDesktopStorageQualifiers()
        {
            var lines = SplitAndPreprocess(GLSLDesktopStorageQualifiers);

            ConvertToXML(lines, "Keyword", "StorageQualifierFormat");

            return lines;
        }

        private static void ConvertToXML(string[] lines, string lexemType, string formatName)
        {
            for (var i = 0; i < lines.Length; i++)
            {
                string line = lines[i];

                line = FormatLexem(line, "False", "False", lexemType, formatName) + "\r\n";

                lines[i] = line;
            }
        }
        #endregion
    }
}
