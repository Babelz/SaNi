#pragma once

#include "sani/graphics/renderables/particle.hpp"
#include "sani/core/math/trigonometric.hpp"
#include "sani/graphics/vertex_helper.hpp"

namespace sani {

	namespace graphics {

		void recomputeVertices(Particle& particle) {
			const float32 sin = math::sin(particle.transform.rotation);
			const float32 cos = math::cos(particle.transform.rotation);

			const float32 dx = -particle.transform.origin.x * particle.transform.scale.x;
			const float32 dy = -particle.transform.origin.y * particle.transform.scale.y;

			math::Vec3f particleGlobalPositions[] {
				particle.transform.position,
					particle.transform.position,
					particle.transform.position,
					particle.transform.position
			};

			math::Vec3f particleVertexPositions[] {
				math::Vec3f(0.0f, 0.0f, 0.0f),																	// Top left
					math::Vec3f(particle.localBounds.w, 0.0f, 0.0f) * particle.transform.scale,						// Top right
					math::Vec3f(0.0f, particle.localBounds.h, 0.0f) * particle.transform.scale,						// Bottom left
					math::Vec3f(particle.localBounds.w, particle.localBounds.h, 0.0f) * particle.transform.scale	// Bottom right
			};

			applyRotationToRectangle(particleGlobalPositions, particleVertexPositions, dx, dy, sin, cos);

			particle.vertices[0].vertexPositionColor.position = particleGlobalPositions[0];
			particle.vertices[1].vertexPositionColor.position = particleGlobalPositions[1];
			particle.vertices[2].vertexPositionColor.position = particleGlobalPositions[2];
			particle.vertices[3].vertexPositionColor.position = particleGlobalPositions[3];
		}

		void recomputeBounds(Particle& particle) {
			const math::Vec3f& position = particle.transform.position;
			const math::Vec3f& scale = particle.transform.scale;

			particle.globalBounds.x = position.x;
			particle.globalBounds.y = position.y;
			particle.globalBounds.w = particle.localBounds.w * scale.x;
			particle.globalBounds.h = particle.localBounds.h * scale.y;
		}
	}
}