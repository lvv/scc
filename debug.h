				#ifndef  LVV_DEBUG_H
				#define  LVV_DEBUG_H

#include <cxxabi.h>


	template <typename T>
const char* type2name() {
	const char* t_name = typeid(T).name();
	int status;
	return abi::__cxa_demangle(t_name, NULL, NULL, &status);
}

#include <iostream>

struct  trace_obj {
	trace_obj()			{ std::cout << "ctor\n"; }
	trace_obj(const trace_obj& o)	{ std::cout << "copy ctor\n"; }
	trace_obj(trace_obj&& o)	{ std::cout << "move ctor\n"; }
	~trace_obj()			{ std::cout << "dtor\n"; }
	trace_obj&  operator=(const trace_obj& o)	{ std::cout << "copy assignment\n";  return *this; }
	trace_obj&  operator=(trace_obj&& o)		{ std::cout << "move assignment\n";  return *this; }

};


template<typename> void template_type_dumper();

template <typename T>	struct ref2name             { static const char* name() { return  "T"         ;}} ; 
template <typename T>	struct ref2name <const T>   { static const char* name() { return  "const T"   ;}} ; 
template <typename T>	struct ref2name <T&>        { static const char* name() { return  "T&"        ;}} ; 
template <typename T>	struct ref2name <const T&>  { static const char* name() { return  "const T&"  ;}} ; 
template <typename T>	struct ref2name <T&&>       { static const char* name() { return  "T&&"       ;}} ; 
template <typename T>	struct ref2name <const T&&> { static const char* name() { return  "const T&&" ;}} ; 


				#endif
