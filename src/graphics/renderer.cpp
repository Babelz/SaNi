#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		#define INITIAL_VERTICES_COUNT 32768
		#define REQUIRE_STATE(requiredState) if (state != requiredState) throw std::runtime_error("can't call function " + String(__FUNCTION__) + " in current state");

		// For starters, reserve 128kb worth of vertex memory (32768 float32 elements).
		// Keep the buffer usage as dynamic (memory as the limit).

		Renderer::Renderer(GraphicsDevice& graphicsDevice) : graphicsDevice(graphicsDevice),
															 vertices(INITIAL_VERTICES_COUNT, BufferSizing::Dynamic),
															 state(RenderState::Waiting),
															 vertexBuffer(0) {
		}

		void Renderer::generateRenderSetups() {
			renderSetups = new RenderSetup*[RENDER_STATES_COUNT];
			
			renderSetups[RenderState::Waiting]		  = nullptr;												// Waiting render state.
			renderSetups[RenderState::UserPrimitives] = new UserPrimitiveRenderSetup(&graphicsDevice);		    // User primitive render state.
			renderSetups[RenderState::Primitives]	  =	nullptr;												// Primitives render state.
			renderSetups[RenderState::Textures]		  = nullptr;												// Textures render state.
			renderSetups[RenderState::Text]			  = nullptr;												// Text render state.
			renderSetups[RenderState::RichText]		  = nullptr;												// Rich text render state.
		}
		void Renderer::generateBuffers() {
			graphicsDevice.generateBuffer(vertexBuffer);
			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice.setBufferData(BufferType::ArrayBuffer,
										 vertices.getSize() * sizeof(float32),
										 vertices.head(),
										 BufferUsage::Stream);
		}

		void Renderer::swapRenderSetup() {
			const uint32 index = static_cast<uint32>(state);

			renderSetup = renderSetups[index];
		}
		
		void Renderer::beginRendering(const RenderState state, const math::Mat4f& transform) {
			if (this->state != RenderState::Waiting) throw std::runtime_error("end rendering must be called before begin");

			this->state = state;
			this->transform = transform;
			
			vertices.resetBufferPointer();
			
			// Rebind buffer if it's size has changed.
			if (verticesSize != vertices.getSize()) {
				graphicsDevice.setBufferData(BufferType::ArrayBuffer,
											 vertices.getSize() * sizeof(float32),
											 vertices.head(),
											 BufferUsage::Stream);

				verticesSize = vertices.getSize();
			}
		}
		void Renderer::endRendering(const RenderState state) {
			if (state == RenderState::Waiting) throw std::runtime_error("begin rendering must be called before end");

			this->state = RenderState::Waiting;
			
			renderSetup->clear();
		}
		vitt
		void Renderer::presentUserPrimitives() {
			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);
			
			graphicsDevice.setBufferSubData(BufferType::ArrayBuffer,
											0,
											vertices.getBufferPointerLocation() * sizeof(float32),
											vertices.head());

			UserPrimitiveRenderSetup* renderSetup = static_cast<UserPrimitiveRenderSetup*>(this->renderSetup);

			graphicsDevice.drawArrays(renderSetup->getRenderMode(), 0, vertices.getBufferPointerLocation() / renderSetup->getVertices());
		}

		bool Renderer::initialize() {
			generateRenderSetups();
			generateBuffers();

			return graphicsDevice.hasErrors();
		}

		void Renderer::beginRenderingUserPrimitives(const math::Mat4f& transform, const uint32 vertices, const RenderMode renderMode) {
			beginRendering(RenderState::UserPrimitives, transform);

			swapRenderSetup();

			UserPrimitiveRenderSetup* renderSetup = static_cast<UserPrimitiveRenderSetup*>(this->renderSetup);
			renderSetup->setRenderMode(renderMode);
			renderSetup->setVertices(vertices);
			renderSetup->use();
		}
		void Renderer::renderUserPrimitives(Buffer<float32>& vertices) {
			REQUIRE_STATE(RenderState::UserPrimitives);

			UserPrimitiveRenderSetup* renderSetup = static_cast<UserPrimitiveRenderSetup*>(this->renderSetup);
			if ((vertices.getBufferPointerLocation() % renderSetup->getVertices()) != 0) throw std::runtime_error("too few or too many vertices");

			// Copy data.
			this->vertices.copy(vertices);
		}

		//void Renderer::beginRenderingPredefinedPrimitives(const math::Mat4f& transform);
		//void Renderer::beginRenderingTextures(const math::Mat4f& transform);
		//void Renderer::beginRenderingText(const math::Mat4f& transform);
		//void Renderer::beginRenderingRichText(const math::Mat4f& transform);

		void Renderer::endRendering() {
			switch (state) {
			case sani::graphics::UserPrimitives:
				presentUserPrimitives();
				break;
			case sani::graphics::Primitives:
			case sani::graphics::Textures:
			case sani::graphics::Text:
			case sani::graphics::RichText:
			default:
				throw std::runtime_error("invalid or unsupported state");
			}

			endRendering(state);
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RENDER_STATES_COUNT; i++) delete renderSetups[i];
			
			delete[]renderSetups;
		}
	}
}