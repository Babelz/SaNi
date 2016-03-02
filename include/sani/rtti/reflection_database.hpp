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
			
			static ReflectionDatabase& getInstance() {
				static ReflectionDatabase instance;
				return instance;
			}
		};
	}
}

