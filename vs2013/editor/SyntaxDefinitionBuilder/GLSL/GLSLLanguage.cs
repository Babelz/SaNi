using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SyntaxDefinitionBuilder.GLSL
{
    public static class GLSLLanguage
    {
        // GLSL 4.5 spec at:
        // https://www.opengl.org/registry/doc/GLSLangSpec.4.50.diff.pdf
        // GLSL Desktop refers to GLSL 4.5 spec.

        #region GLSL Strings

        public static readonly string DesktopKeywords =
            @"const coherent volatile restrict readonly writeonly
              layout
              flat smooth noperspective
              break continue do for while switch case default
              if else
              subroutine
              invariant precise
              discard return layout
              lowp mediump highp precision
              true false
              struct";

        public static readonly string DesktopStorageQualifiers =
            @"const in out attribute uniform varying
              buffer shared centroid sample patch
              location
              inout";

        public static readonly string DesktopTypes =
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

        public static readonly string SingleLineComment        = @"//";
        public static readonly string MultiLineCommentBegin    = @"/\*";
        public static readonly string MultiLineCommentEnd      = @"\*/";

        #endregion
    }
}
