#pragma once

#define NEW_DYNAMIC_DEFAULT(type, ptr)	new (ptr) type()
#define NEW_DYNAMIC(type, ptr, ...)	    new (ptr) type(##__VA_ARGS__)