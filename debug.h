				#ifndef  LVV_DEBUG_H
				#define  LVV_DEBUG_H

#include <cxxabi.h>
	template <typename T>
const char* type2name() {
	const char* t_name = typeid(T).name();
	int status;
	return abi::__cxa_demangle(t_name, NULL, NULL, &status);
}
				#endif
