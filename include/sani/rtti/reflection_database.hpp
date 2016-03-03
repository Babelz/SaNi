#pragma once

namespace sani {
	namespace rtti {
		class ReflectionDatabase {
		private:
			template <class T>
			void registerReflection() {
				T::RTTI_Init();
			}
			ReflectionDatabase();
			~ReflectionDatabase() = default;
		public:
			ReflectionDatabase& operator=(const ReflectionDatabase&) = delete;
			ReflectionDatabase& operator=(ReflectionDatabase&&) = delete;
			ReflectionDatabase(ReflectionDatabase&&) = delete;

			static ReflectionDatabase& getInstance() {
				static ReflectionDatabase instance;
				return instance;
			}
		};
	}
}

