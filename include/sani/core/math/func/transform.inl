#pragma once

#include "transform.hpp"
namespace sani {
	namespace math {
		template <typename T>
		Matrix4<T> translate(Matrix4<T> const& mat, Vector3<T> const& vec) {
			/*
			For programming purposes, OpenGL matrices are 16-value arrays with base vectors laid out contiguously in memory. 
			The translation components occupy the 13th, 14th, and 15th elements of the 16-element matrix
			TODO: DirectX has the same memory layout?
			*/
			Matrix4<T> result;
			result[3] = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3];
			return result;
		}
	}
}

