#pragma once	

#include "sani/core/math/vector3.hpp"
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
		inline void applyRotationToTopLeftVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
		
		/// Applies rotation to given top right vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition loval vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToTopRightVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);

		/// Applies rotation to given bottom left vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition loval vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToBottomLeftVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);

		/// Applies rotation to given bottom right vertex position
		/// @param[in] globalPosition global position of the vertex
		/// @param[in] vertexPosition loval vertex position of the vertex
		/// @param[in] dx origin x
		/// @param[in] dy origin y
		/// @param[in] sin sin
		/// @param[in] cos cos
		inline void applyRotationToBottomRightVertex(sani::math::Vec3f& globalPosition, const sani::math::Vec3f& vertexPosition, const float32 dx, const float32 dy, const float32 sin, const float32 cos);
	}
}

#include "sani/graphics/inl/vertex_helper.inl"