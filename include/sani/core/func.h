#define SANI_ACTION(signature)							std::function<signature>
#define SANI_FUNC_CALLER(signature, callback)	        std::function<std::function<signature>>