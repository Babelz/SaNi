#include "sani/engine/mono/mono_include.hpp"
#include "sani/graphics/renderables/rectangle.hpp"
#include "sani/engine/services/renderable_manager.hpp"
#include "sani/engine/services/contracts/renderable_manager_contract.hpp"
#include "sani/core/memory/memory.hpp"
#include "sani/engine/mono/renderable_mono.hpp"
#include "sani/engine/mono/mono_provider.hpp"

#include "sani/engine/mono/transform_mono.hpp"
#include "sani/engine/mono/rectf_mono.hpp"
#include "sani/engine/mono/texture2d_mono.hpp"
#include "sani/engine/mono/color_mono.hpp"

#include "sani/core/math/rectangle.hpp"
#include "sani/core/math/vector2.hpp"
#include "sani/core/math/vector3.hpp"

#include <mono/metadata/appdomain.h>

#include <iostream>
#include <vector>

#include "sani/types.hpp"

namespace sani {

	namespace engine {

		// TODO: REWRITE EVERY FUNCTION TO USE MONO-OBJECT INSTEAD OF MONOSTRING.......

		MONO_MODULE_IMPL(rectangle)

		using namespace sani::engine::services;
		using namespace sani::graphics;

		static std::vector<Rectangle*>* elements				{ nullptr };

		const MonoClassDefinition ClassDef("SaNi.Mono.Graphics.Renderables", "Rectangle");

		static Rectangle* getInstance(MonoObject* instance) {
			const gint32 id = *MONO_UNBOX(MONO_PROVIDER->readField(instance, "id"), gint32);

			/*MonoObject* value = MONO_PROVIDER->invoke(instance, "GetID");
///*
			const gint32 id = *MONO_UNBOX(value, gint32);
*/

			//MonoClassDefinition fd("SaNi.Mono", "Foo");
			//MonoFunctionDefinition fctor(".ctor", FooCtor);

			//MONO_PROVIDER->addInternalCall(&fd, &fctor);
			//MonoObject* foo = MONO_PROVIDER->createObject(&fd);

			//auto a = mono_get_root_domain();
			//auto ia = mono_object_get_domain(instance);
			//auto ba = mono_object_get_domain(foo);

			//MonoObject* value = MONO_PROVIDER->readField(instance, "id");

			//const uint32 id = *MONO_UNBOX(value, int32);

			return elements->operator[](0);
		}

		static MonoObject* GetTransform(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);

			MonoObject* transform = mono::transform::create(rectangle->transform.position, 
														    rectangle->transform.scale, 
														    rectangle->transform.origin, 
														    rectangle->transform.rotation);
			
			return transform;
		}
		static void SetTransform(MonoObject* instance, MonoObject* value) {
			Rectangle* const rectangle = getInstance(instance);

			const math::Vec3f position = mono::transform::getPosition(value);
			const math::Vec3f scale    = mono::transform::getScale(value);
			const math::Vec3f origin   = mono::transform::getOrigin(value);
			const float32 rotation	   = mono::transform::getRotation(value);

			rectangle->transform.position	= position;
			rectangle->transform.scale		= scale;
			rectangle->transform.origin		= origin;
			rectangle->transform.rotation	= rotation;

			recomputeVertices(*rectangle);
			recomputeBounds(*rectangle);
		}

		static MonoObject* GetLocalBounds(MonoObject* instance) {
			auto a = mono_domain_get();
			auto b = mono_object_get_domain(instance);

			Rectangle* const rectangle = getInstance(instance);

			//if (rectangle == nullptr) return nullptr;

			math::Rect32f localBounds = rectangle->localBounds;

			MonoObject* rectf = mono::rectf::create(localBounds.x, 
												    localBounds.y, 
												    localBounds.w, 
  												    localBounds.h);

			return rectf;
		}
		static void SetLocalBounds(MonoObject* instance, MonoObject* value) {
			Rectangle* const rectangle = getInstance(instance);
			
			mono::rectf::copyData(value, &rectangle->localBounds);

			recomputeBounds(*rectangle);
		}

		static MonoObject* GetGlobalBounds(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);

			math::Rect32f globalBounds = rectangle->globalBounds;

			MonoObject* rectf = mono::rectf::create(globalBounds.x,
												    globalBounds.y, 
													globalBounds.w,
													globalBounds.h);

			return rectf;
		}

		static MonoObject* GetTextureSource(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);

			math::Rect32f textureSource = rectangle->textureSource;

			MonoObject* rectf = mono::rectf::create(textureSource.x,
												    textureSource.y, 
													textureSource.w,
													textureSource.h);
			return rectf;
		}
		static void SetTextureSource(MonoObject* instance, MonoObject* value) {
			Rectangle* const rectangle = getInstance(instance);

			mono::rectf::copyData(value, &rectangle->textureSource);

			updateRenderData(*rectangle);
		}

		static MonoObject* GetTexture2D(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);
			
			if (rectangle->texture == nullptr) return nullptr;

			else return texture2dmonomodule::getManagedPtr(rectangle->texture->getID());
		}
		static void SetTexture2D(MonoObject* instance, MonoObject* value) {
			Rectangle* const rectangle = getInstance(instance);

			if (value == nullptr) rectangle->texture = nullptr;
			else				  rectangle->texture = texture2dmonomodule::getNativePtr(value);

			updateRenderData(*rectangle);
		}

		static gboolean GetVisible(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);

			return rectangle->visible;
		}
		static void SetVisible(MonoObject* instance, gboolean value) {
			Rectangle* const rectangle = getInstance(instance);

			rectangle->visible = value ? true : false;
		}
		
		static gfloat GetBorderThickness(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);

			return rectangle->borderThickness;
		}
		static void SetBorderThickness(MonoObject* instance, gfloat value) {
			Rectangle* const rectangle = getInstance(instance);

			rectangle->borderThickness = value;

			recomputeVertices(*rectangle);
		}

		static MonoObject* GetFill(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);
			
			MonoObject* color = mono::color::create(rectangle->fill.r, rectangle->fill.g, rectangle->fill.b, rectangle->fill.a);

			return color;
		}
		static void SetFill(MonoObject* instance, MonoObject* value) {
			Rectangle* const rectangle = getInstance(instance);
			
			mono::color::copyData(value, &rectangle->fill);
			
			recomputeVertices(*rectangle);
		}

		static MonoObject* GetBorderFill(MonoObject* instance) {
			Rectangle* const rectangle = getInstance(instance);

			MonoObject* color = mono::color::create(rectangle->borderFill.r, rectangle->borderFill.g, rectangle->borderFill.b, rectangle->borderFill.a);

			return color;
		}
		static void SetBorderFill(MonoObject* instance, MonoObject* value) {
			Rectangle* const rectangle = getInstance(instance);

			mono::color::copyData(value, &rectangle->borderFill);

			recomputeVertices(*rectangle);
		}

		static void Release(MonoObject* instance, gint32 id) {
			auto* deleteElement = engine->createEmptyMessage<messages::DocumentMessage>();
			deleteElement->setData(elements->operator[](id));

			renderablemanager::deleteElement(deleteElement, ElementType::Rectangle);
			engine->routeMessage(deleteElement);
			
			engine->releaseMessage(deleteElement);
		}

		static MonoObject* Instantiate(gfloat x, gfloat y, gfloat width, gfloat height) {
			auto* createRectangle = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::createElement(createRectangle, ElementType::Rectangle);
			engine->routeMessage(createRectangle);

			auto* rectangle = static_cast<Rectangle*>(createRectangle->getData());

			NEW_DYNAMIC(Rectangle, rectangle, x, y, width, height);

			engine->releaseMessage(createRectangle);

			gint32 id = gint32(rectangle->id);

			const uint32 argc = 1;
			void* args[argc];
			args[0] = &id;

			MonoObject* instance = MONO_PROVIDER->createObject(&ClassDef, args, argc);

			MonoObject* o = mono::color::create(1.0f, 1.0f, 1.0f, 1.0f);
			
			return instance;
		}

		static void getElements() {
			auto* getElements = engine->createEmptyMessage<messages::DocumentMessage>();
			renderablemanager::getElements(getElements, ElementType::Rectangle);
			engine->routeMessage(getElements);

			elements = static_cast<std::vector<Rectangle*>*>(getElements->getData());
			
			engine->releaseMessage(getElements);
		}

		static void ASD(MonoObject* instance) {
			auto a = mono_domain_get();
			auto b = mono_object_get_domain(instance);

			volatile int j = 0;
		}

		bool initialize() {
			getElements();

			mono::RenderableSuperDef superDef("Rectangle", "SaNi.Mono.Graphics.Renderables");
			//superDef.transform.get = GetTransform;
			//superDef.transform.set = SetTransform;

			////superDef.localBounds.get = GetLocalBounds;
			////superDef.localBounds.set = SetLocalBounds;

			//superDef.globalBounds.get = GetGlobalBounds;
			//
			//superDef.textureSource.get = GetTextureSource;
			//superDef.textureSource.set = SetTextureSource;

			//superDef.texture2D.get = GetTexture2D;
			//superDef.texture2D.set = SetTexture2D;

			//superDef.visible.get = GetVisible;
			//superDef.visible.set = SetVisible;

 		//	mono::registerRenderableMembers(superDef);
			
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, Instantiate, Instantiate);
			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, ASD, ASD);

			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, GetLocalBounds, GetLocalBounds);
			MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, SetLocalBounds, SetLocalBounds);

			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, get_Visible, GetVisible);
			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, set_Visible, SetVisible);

			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, get_Fill, GetFill);
			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, set_Fill, SetFill);

			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, get_BorderFill, GetBorderFill);
			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, set_BorderFill, SetBorderFill);

			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, get_BorderThickness, GetBorderThickness);
			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, set_BorderThickness, SetBorderThickness);

			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, Instantiate, Instantiate);
			//MONO_REGISTER_KNOWN_FUNCTION(SaNi.Mono.Graphics.Renderables, Rectangle, Release, Release);

			return true;
		}

		MONO_MODULE_IMPL_END
	}
}