#include <functional>

template <typename T>
using FunctionCaller = std::function < std::function<T> > ;

template <typename T>
using Action = std::function < T > ;