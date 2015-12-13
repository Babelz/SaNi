#include "sani\core\events.hpp"

using namespace sani;

// Test class for testing events.
class EventMath {
public:
	SANI_DECLARE_EVENT(onAdd, void(int));
	SANI_DECLARE_EVENT(onSub, void(int));
	SANI_DECLARE_EVENT(onOper, void(void));

	EventMath() {
		SANI_INIT_EVENT(onAdd, void(int));
		SANI_INIT_EVENT(onSub, void(int));
		SANI_INIT_EVENT(onOper, void(void));
	}

	void add(int a, int b) {
		const int result = a + b;

		SANI_TRIGGER_EVENT(onAdd, void(int), result);
		SANI_TRIGGER_VOID_EVENT(onOper, void(void));
	}
	void sub(int a, int b) {
		const int result = a - b;

		SANI_TRIGGER_EVENT(onSub, void(int), result);
		SANI_TRIGGER_VOID_EVENT(onOper, void(void));
	}

	~EventMath() = default;
};