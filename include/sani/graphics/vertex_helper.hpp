#pragma once	

#include "sani/graphics/vertex_position_color_texture.hpp"
#include "sani/core/math/vector3.hpp"
#include "sani/core/math/vector2.hpp"
#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		/*
			Contains helper functions used to manipulate vertices.
		*/

		/// Applies rotation to given top left vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition local vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToTopLeftVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		/// Applies rotation to given top right vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition local vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToTopRightVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);

		/// Applies rotation to given bottom left vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition local vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToBottomLeftVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);

		/// Applies rotation to given bottom right vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition local vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToBottomRightVertex(math::Vec3f* const globalPosition, const math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		/// Applies rotation to given vertex group that is handled as a triangle.
		inline void applyRotationToTriangle(math::Vec3f* const globalPositions, const math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		/// Applies rotation to given vertex group that is handled as a rectangle.
		inline void applyRotationToRectangle(math::Vec3f* const globalPositions, const math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos);

		inline void computeTopLeftTextureCoordinate(VertexPositionColorTexture* const vertex, const math::Rect32f& textureSource, const float32 textureWidth, const float32 textureHeight);

		inline void computeTopRightTextureCoordinate(VertexPositionColorTexture* const vertex, const math::Rect32f& textureSource, const float32 textureWidth, const float32 textureHeight);
		
		inline void computeBottomLeftTextureCoordinate(VertexPositionColorTexture* const vertex, const math::Rect32f& textureSource, const float32 textureWidth, const float32 textureHeight);
		
		inline void computeBottomRightTextureCoordinate(VertexPositionColorTexture* const vertex, const math::Rect32f& textureSource, const float32 textureWidth, const float32 textureHeight);
		
		/// Recomputes texture coordinates for given rectangle element.
		/// uvs should be ordered as follows:
		/// top left, top right, bottom left and bottom right positions.
		inline void computeRectangleTextureCoordinates(VertexPositionColorTexture** const vertices, const math::Rect32f& textureSource, const float32 textureWidth, const float32 textureHeight);
		
		/// Recompute texture coordinates for given triangle element.
		/// uvs should be ordered as follows:
		/// top, left and right.
		inline void computeTriangleTextureCoordinates(VertexPositionColorTexture** const vertices, const math::Rect32f& textureSource, const float32 textureWidth, const float32 textureHeight);
		
		inline void applyDefaultRectangleTextureCoordinates(VertexPositionColorTexture** const vertices);
		
		inline void applyCircleTextureCoordinates(VertexPositionColorTexture* const vertices, const float32 rotation, const float32 radius, const math::Rect32f& textureSource, const float32 textureWidth, const float32 textureHeight, const uint32 count);
	}
}

#include "sani/graphics/inl/vertex_helper.inl"