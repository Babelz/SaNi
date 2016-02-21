#pragma once

#include "sani/rtti/invokable.hpp"
#include "sani/rtti/object.hpp"
#include "sani/rtti/argument_config.hpp"
#include <functional>
namespace sani {
	namespace rtti {
		class Constructor : public Invokable {
		public:
			// TODO args
			using CreateInstance = std::function<Object(Arguments&)>;

			/// Creates invalid constructor
			Constructor();
			/// Creates valid invokable constructor
			/// @param type The type of the class where this constructor belongs
			/// @param signature The constructors signature
			/// @param instanceFunc Function to create instance using this ctor
			/// @param isDynamic is this constructor dynamic
			Constructor(Type type, Signature signature, CreateInstance instanceFunc, bool isDynamic);

			/// Is this constructor invokable?
			bool isValid() const;

			/// Does this constructor use new?
			bool isDynamic() const;

			/// Gets the class type of this constructor
			Type getType() const;

			/// Invokes the constructor
			Object invoke(Arguments& args) const;

			/// Returns invalid constructor
			static const Constructor& invalid(void);
		private:
			bool _isDynamic;
			Type type;
			CreateInstance createInstance;
		};
	}
}

