#include "sani/engine/services/user_service.hpp"

#include "sani/engine/mono/mono_runtime.hpp"
#include "sani/engine/mono/mono_provider.hpp"
#include "sani/engine/mono/mono_define.hpp"

#include "sani/engine/mono/glib_types.hpp"

#include "sani/platform/time/engine_time.hpp"

namespace sani {

	namespace engine {

		namespace services {

			HookFlags operator &(HookFlags lhs, const HookFlags rhs) {
				lhs &= rhs;

				return lhs;
			}
			HookFlags& operator &=(HookFlags& lhs, const HookFlags rhs) {
				const auto ilhs = static_cast<uint32>(lhs);
				const auto irhs = static_cast<uint32>(rhs);
				
				lhs = static_cast<HookFlags>(ilhs & irhs);

				return lhs;
			}

			HookFlags operator |(HookFlags lhs, const HookFlags rhs) {
				lhs |= rhs;

				return lhs;
			}
			HookFlags& operator |=(HookFlags& lhs, const HookFlags rhs) {
				const auto ilhs = static_cast<uint32>(lhs);
				const auto irhs = static_cast<uint32>(rhs);

				lhs = static_cast<HookFlags>(ilhs | irhs);

				return lhs;
			}

			
			UserService::UserService(MonoObject* const instance, MonoString* const name, SaNiEngine* const engine) 
				: EngineService(mono_string_to_utf8(name), engine), instance(instance) {
			}

			bool UserService::onStart() {
				if (static_cast<uint32>((flags & HookFlags::OnStart))) {
					MonoObject* results = MONO_PROVIDER->invoke(instance, "OnStart");

					bool* val = static_cast<bool*>(mono_object_unbox(results));

					return *val;
				}

				// No hook.
				return true;
			}
			bool UserService::onResume() {
				if (static_cast<uint32>((flags & HookFlags::OnResume))) {
					MonoObject* results = MONO_PROVIDER->invoke(instance, "OnResume");
					
					bool* val = static_cast<bool*>(mono_object_unbox(results));
					
					return *val;
				}

				// No hook.
				return true;
			}
			void UserService::onSuspend() {
				if (static_cast<uint32>((flags & HookFlags::OnSuspended))) {
					MONO_PROVIDER->invoke(instance, "OnSuspended");
				}
			}
			void UserService::onTerminate() {
				if (static_cast<uint32>((flags & HookFlags::OnTerminated))) {
					MONO_PROVIDER->invoke(instance, "OnTerminated");
				}
			}

			MonoObject* const UserService::getMonoInstance() const {
				return instance;
			}
			void UserService::setMonoHooks(const HookFlags flags) {
				this->flags = flags;
			}

			void UserService::update(const EngineTime& time) {
				if (static_cast<uint32>((flags & HookFlags::OnUpdate))) {
					const MonoClassDefinition classDef("SaNi.Mono.Engine", "EngineTime");
					
					gfloat totalTime = static_cast<gfloat>(time.getTotalTime());
					gfloat frameTime = static_cast<gfloat>(time.getFrameTime());
				
					void* args[2];
					args[0] = &totalTime;
					args[1] = &frameTime;

					const uint32 argc = 2;

					MonoObject* engineTime = MONO_PROVIDER->createObject(&classDef, args, argc);

					void* updateargs[1];
					updateargs[0] = engineTime;

					const uint32 updateargc = 1;

					MONO_PROVIDER->invoke(instance, "OnUpdate", updateargs, updateargc);
				}
			}
		}
	}
}