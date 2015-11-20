#pragma once	

#include "sani/forward_declare.hpp"
#include "sani/types.hpp"

namespace sani {

	namespace graphics {

		/*
			Contains helper functions used to mainupulate vertices.
		*/

		/// Applies rotation to given top left vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition loval vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToTopLeftVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		/// Applies rotation to given top right vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition loval vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToTopRightVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);

		/// Applies rotation to given bottom left vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition loval vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToBottomLeftVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);

		/// Applies rotation to given bottom right vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition loval vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToBottomRightVertex(sani::math::Vec3f* const globalPosition, const sani::math::Vec3f* const vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		/// Applies rotation to given vertex group that is handled as a triangle.
		inline void applyRotationToTriangle(sani::math::Vec3f* const globalPositions, const sani::math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		/// Applies rotation to given vertex group that is handled as a rectangle.
		inline void applyRotationToRectangle(sani::math::Vec3f* const globalPositions, const sani::math::Vec3f* const vertexPositions, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		//inline void recomputeRectangleBounds(const sani::math::Vec3f* const position, const sani::math::Vec3f* const scale, sani::math::Rectf& localBounds, sani::math::Rectf& globalBounds);
	}
}

#include "sani/graphics/inl/vertex_helper.inl"