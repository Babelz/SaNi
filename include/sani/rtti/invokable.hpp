#pragma once

#include "sani/types.hpp"
#include <vector>
#include "sani/rtti/type.hpp"

namespace sani {
	namespace rtti {
		/// Used as key to map ctors, methods
		using Signature = std::vector<Type>;
		/// Class that represents invokable instance
		class Invokable {
		public:
			/// Creates new invokable obj
			Invokable(const String8& name);
			/// Gets the name of the invokable
			const String8 getName() const;
			/// Gets the signature of invokable
			const Signature& getSignature() const;

			template <typename ...Args>
			static Signature createSignature();
		protected:
			String8 name;
			Signature signature;
		};
	}
}

#include "inl/invokable.inl"
