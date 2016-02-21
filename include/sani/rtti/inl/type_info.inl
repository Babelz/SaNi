namespace sani {
	namespace rtti {
		template <class T>
		TypeID TypeInfo<T>::id = Type::Invalid;

		template <class T>
		bool TypeInfo<T>::defined = false;

		template <class T>
		void TypeInfo<T>::registerType(TypeID _id, TypeData& data, bool beingDefined) {
			// its already defined
			if (_id == Type::Invalid) return;

			id = _id;
			defined = true;
			typedef std::decay<T> Decayed;
			data.isClass = std::is_class<Decayed::type>::value;
			data.isPointer = std::is_pointer<T>::value;

			if (beingDefined) {
				addDefaultConstructor(data);
			}
		}


		template<typename T>
		template<typename U>
		void TypeInfo<T>::addDefaultConstructor(
			TypeData &data,
			typename std::enable_if<
			!std::is_trivially_default_constructible<U>::value
			>::type*
			) {}

		template<typename T>
		template<typename U>
		void TypeInfo<T>::addDefaultConstructor(
			TypeData &data,
			typename std::enable_if<
			std::is_trivially_default_constructible<U>::value
			>::type*
			) {
			data.addConstructor<T>([](Arguments&) { return T(); }, false);
			data.addConstructor<T>([](Arguments&) { return new T(); }, true);
		}

	}
}