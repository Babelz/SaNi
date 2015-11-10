#include "sani/platform/graphics/graphics_precompiled.hpp"
#include "sani/platform/graphics/graphics_device.hpp"
#include "sani/graphics/setups/render_setups.hpp"
#include "sani/graphics/renderer.hpp"

namespace sani {

	namespace graphics {

		#define INITIAL_BUFFER_ELEMENTS_COUNT 32768
		#define REQUIRE_STATE(requiredState) if (state != requiredState) throw std::runtime_error("can't call function " + String(__FUNCTION__) + " in current state");

		// For starters, reserve 128kb worth of vertex memory (32768 float32 elements).
		// Keep the buffer usage as dynamic (memory as the limit).

		Renderer::Renderer(GraphicsDevice& graphicsDevice) : graphicsDevice(graphicsDevice),
															 vertices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
															 indices(INITIAL_BUFFER_ELEMENTS_COUNT, BufferSizing::Dynamic),
															 verticesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
															 indicesSize(INITIAL_BUFFER_ELEMENTS_COUNT),
															 renderState(RenderState::Waiting),
															 vertexBuffer(0),
															 indexBuffer(0) {
		}

		void Renderer::generateRenderSetups() {
			renderSetups = new RenderSetup*[RENDER_STATES_COUNT];
			
			renderSetups[RenderState::Waiting]			= nullptr;												
			renderSetups[RenderState::Polygons]			= new PolygonRenderSetup(&graphicsDevice); 		
			renderSetups[RenderState::TexturedPolygons]	= new TexturedPolygonRenderSetup(&graphicsDevice);												
			renderSetups[RenderState::Text]				= new TexturedPolygonRenderSetup(&graphicsDevice);												
		}
		void Renderer::generateBuffers() {
			graphicsDevice.generateBuffer(vertexBuffer);
			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

			graphicsDevice.generateBuffer(indexBuffer);
			graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

			graphicsDevice.setBufferData(BufferType::ArrayBuffer,
										 vertices.getSize() * sizeof(float32),
										 vertices.data(),
										 BufferUsage::Stream);


			graphicsDevice.setBufferData(BufferType::ElementArrayBuffer,
										 indices.getSize() * sizeof(uint32),
										 indices.data(),
										 BufferUsage::Stream);
		}

		void Renderer::updateVertexBufferSize() {
			// Rebind buffer if it's size has changed.
			if (verticesSize != vertices.getSize()) {
				graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);

				graphicsDevice.setBufferData(BufferType::ArrayBuffer,
											 vertices.getSize() * sizeof(float32),
											 vertices.data(),
											 BufferUsage::Stream);

				verticesSize = vertices.getSize();
			}
		}
		void Renderer::updateIndexBufferSize() {
			if (indicesSize != indices.getSize()) {
				graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

				graphicsDevice.setBufferData(BufferType::ElementArrayBuffer,
											 indices.getSize() * sizeof(uint32),
											 indices.data(),
											 BufferUsage::Stream);

				indicesSize = indices.getSize();
			}
		}

		void Renderer::swapRenderSetup() {
			const uint32 index = static_cast<uint32>(renderState);

			renderSetup = renderSetups[index];
		}
		
		void Renderer::prepareRendering(const RenderState renderState, const math::Mat4f& transform, const VertexMode vertexMode) {
			if (this->renderState != RenderState::Waiting) throw std::runtime_error("end rendering must be called before begin");

			this->renderState = renderState;
			this->transform = transform;
			this->vertexMode = vertexMode;
			
			vertices.resetBufferPointer();
			indices.resetBufferPointer();
		}
		void Renderer::prepareRenderingPolygons(const RenderMode renderMode, const uint32 vertexElementsCount) {
			swapRenderSetup();

			renderSetup->setRenderMode(renderMode);
			renderSetup->setVertexElementsCount(vertexElementsCount);
		}
		void Renderer::prepareRenderingPolygons(const RenderMode renderMode, const uint32 texture, const uint32 vertexElementsCount) {
			prepareRenderingPolygons(renderMode, vertexElementsCount);
			
			TexturedPolygonRenderSetup* const polygonRenderSetup = static_cast<TexturedPolygonRenderSetup*>(renderSetup);
			polygonRenderSetup->setTexture(texture);
		}

		void Renderer::endRendering(const RenderState renderState) {
			if (renderState == RenderState::Waiting) throw std::runtime_error("begin rendering must be called before end");

			this->renderState = RenderState::Waiting;
			
			renderSetup->clear();
		}

		void Renderer::presentPolygons() {
			updateVertexBufferSize();
			updateIndexBufferSize();

			graphicsDevice.bindBuffer(vertexBuffer, BufferType::ArrayBuffer);
			
			graphicsDevice.setBufferSubData(BufferType::ArrayBuffer,
											0,
											vertices.getElementsCount() * sizeof(float32),
											vertices.data());

			if (vertexMode == VertexMode::NoIndexing) {
				graphicsDevice.drawArrays(renderSetup->getRenderMode(), 0, vertices.getElementsCount() / renderSetup->getVertexElementsCount());
			} else {
				graphicsDevice.bindBuffer(indexBuffer, BufferType::ElementArrayBuffer);

				graphicsDevice.setBufferSubData(BufferType::ElementArrayBuffer,
												0,
												indices.getElementsCount() * sizeof(uint32),
												indices.data());

				graphicsDevice.drawElements(renderSetup->getRenderMode(), PrimitiveType::UInt, indices.getElementsCount(), 0);
			}
		}
		void Renderer::presentIndexedPolygons() {
			throw std::runtime_error("not implemented");
		}

		bool Renderer::initialize() {
			generateRenderSetups();
			generateBuffers();

			return graphicsDevice.hasErrors();
		}

		void Renderer::beginRenderingPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 vertexElementsCount, const RenderMode renderMode) {
			SANI_ASSERT(vertexElementsCount != 0);

			prepareRendering(RenderState::TexturedPolygons, transform, VertexMode::NoIndexing);
			prepareRenderingPolygons(renderMode, texture, vertexElementsCount);
			
			renderSetup->use();
		}
		void Renderer::beginRenderingPolygons(const math::Mat4f& transform, const uint32 vertexElementsCount, const RenderMode renderMode) {
			SANI_ASSERT(vertexElementsCount != 0);
			
			prepareRendering(RenderState::Polygons, transform, VertexMode::NoIndexing);
			prepareRenderingPolygons(renderMode, vertexElementsCount);

			renderSetup->use();
		}
		
		void Renderer::beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 texture, const uint32 vertexElementsCount, const RenderMode renderMode) {
			SANI_ASSERT(vertexElementsCount != 0);

			prepareRendering(RenderState::TexturedPolygons, transform, VertexMode::Indexed);
			prepareRenderingPolygons(renderMode, texture, vertexElementsCount);

			renderSetup->use();
		}
		void Renderer::beginRenderingIndexedPolygons(const math::Mat4f& transform, const uint32 vertexElementsCount, const RenderMode renderMode) {
			SANI_ASSERT(vertexElementsCount != 0);

			prepareRendering(RenderState::Polygons, transform, VertexMode::Indexed);
			prepareRenderingPolygons(renderMode, vertexElementsCount);

			renderSetup->use();
		}
		
		/*
			TODO: RENAME STUFF FUCK SAKES!
		*/

		void Renderer::renderPolygons(const float32* vertices, const uint32 vertexElementsCount) {
			SANI_ASSERT((vertexElementsCount % renderSetup->getVertexElementsCount()) == 0);

			this->vertices.push(vertices, vertexElementsCount);

			// TODO: change to debug asserts?
			if (vertexMode == VertexMode::Indexed) throw std::runtime_error("invalid call, was not expecting indexed elements");
		}

		void Renderer::renderPolygons(const float32* vertices, const uint32 vertexElementsCount, const uint32 offset) {
			SANI_ASSERT((vertexElementsCount % renderSetup->getVertexElementsCount()) == 0);

			for (uint32 i = offset; i < offset + vertexElementsCount; i++) this->vertices.push(vertices[i]);

			// TODO: change to debug asserts?
			if (vertexMode == VertexMode::Indexed) throw std::runtime_error("invalid call, was not expecting indexed elements");
		}

		void Renderer::renderIndexedPolygons(const float32* vertices, const uint32* indices, const uint32 verticesCount, const uint32 indicesCount, const uint32 indexObjects) {
			SANI_ASSERT((verticesCount % renderSetup->getVertexElementsCount()) == 0);

			const uint32 vertexCount = this->vertices.getElementsCount() / renderSetup->getVertexElementsCount();

			for (uint32 i = 0; i < indicesCount; i++) this->indices.push(indices[i] + vertexCount);

			this->vertices.push(vertices, verticesCount);

			// TODO: change to debug asserts?
			if (vertexMode == VertexMode::NoIndexing) throw std::runtime_error("invalid call, was expecting indexed elements");
		}

		void Renderer::flush() {
			switch (renderState) {
			case sani::graphics::RenderState::Polygons:
				presentPolygons();
				break;
			case sani::graphics::RenderState::TexturedPolygons:
			case sani::graphics::RenderState::Waiting:
			case sani::graphics::RenderState::Text:
			default:
				throw std::runtime_error("invalid or unsupported state");
			}

			vertices.resetBufferPointer();
			indices.resetBufferPointer();
		}

		void Renderer::endRendering() {
			flush();

			endRendering(renderState);
		}

		Renderer::~Renderer() {
			for (uint32 i = 0; i < RENDER_STATES_COUNT; i++) delete renderSetups[i];
			
			delete[]renderSetups;
		}
	}
}