				#ifndef  LVV_DEBUG_H
				#define  LVV_DEBUG_H

	#include <iostream>

//////  TYPE2NAME

	#include <cxxabi.h>


	template <typename T>
const char* type2name() {
	const char* t_name = typeid(T).name();
	int status;
	return abi::__cxa_demangle(t_name, NULL, NULL, &status);
}

//////  REF2NAME

template <typename T>	struct ref2name             { static constexpr const char* value =  "T"         ;} ; 
template <typename T>	struct ref2name <const T>   { static constexpr const char* value =  "const T"   ;} ; 
template <typename T>	struct ref2name <      T&>  { static constexpr const char* value =  "T&"        ;} ; 
template <typename T>	struct ref2name <const T&>  { static constexpr const char* value =  "const T&"  ;} ; 
template <typename T>	struct ref2name <      T&&> { static constexpr const char* value =  "T&&"       ;} ; 
template <typename T>	struct ref2name <const T&&> { static constexpr const char* value =  "const T&&" ;} ; 

//////  printT

#define printT(T)  std::cout << ref2name<T>::value << "  \t---   \t"  <<  type2name<T>()  <<  std::endl;
#define printToV(V)  printT(decltype(V));

//////

template<typename> void template_type_dumper();

//////  TRACE_OBJ


struct  trace_obj {
	trace_obj()			{ std::cout << "ctor\n"; }
	trace_obj(const trace_obj& o)	{ std::cout << "copy ctor\n"; }
	trace_obj(trace_obj&& o)	{ std::cout << "move ctor\n"; }
	~trace_obj()			{ std::cout << "dtor\n"; }
	trace_obj&  operator=(const trace_obj& o)	{ std::cout << "copy assignment\n";  return *this; }
	trace_obj&  operator=(trace_obj&& o)		{ std::cout << "move assignment\n";  return *this; }

};



				#endif
