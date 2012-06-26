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
template <typename T>	struct ref2name <volatile T>   { static constexpr const char* value =  "volatile T"   ;} ; 
template <typename T>	struct ref2name <volatile const T>   { static constexpr const char* value =  "volatile const T"   ;} ; 

template <typename T>	struct ref2name <      T&>  { static constexpr const char* value =  "T&"        ;} ; 
template <typename T>	struct ref2name <const T&>  { static constexpr const char* value =  "const T&"  ;} ; 
template <typename T>	struct ref2name <volatile T&>  { static constexpr const char* value =  "volatile T&"  ;} ; 
template <typename T>	struct ref2name <volatile const  T&>  { static constexpr const char* value =  "volatile const  T&"  ;} ; 

template <typename T>	struct ref2name <      T&&> { static constexpr const char* value =  "T&&"       ;} ; 
template <typename T>	struct ref2name <const T&&> { static constexpr const char* value =  "const T&&" ;} ; 
template <typename T>	struct ref2name <volatile T&&> { static constexpr const char* value =  "volatile T&&" ;} ; 
template <typename T>	struct ref2name <volatile const T&&> { static constexpr const char* value =  "volatile const T&&" ;} ; 

//////  printT

#define printT(T)  std::cout << ref2name<T>::value << "  \t---   \t"  <<  type2name<T>()  <<  std::endl;
#define printToV(V)  printT(decltype(V));

////// Template Type Dumper

template<typename> void ttd();

//////  TRACE_OBJ

		template <typename T>
	struct counter {
		static int    created,   alive;
		counter()  {++created; ++alive; }
		~counter() {           --alive; }
	};
	template <typename T> int counter<T>::created (0);
	template <typename T> int counter<T>::alive   (0);


struct  to : counter<to> {
	to() 			: id(this->created)	{ std::cout << "ctor ()    *"  << id << std::endl; }
	to(const to& o)		: id(this->created)	{ std::cout << "ctor (cT&)  "  << id << "(" << o.id << ")"<< std::endl; }
	to(to&& o)		: id(this->created) 	{ std::cout << "ctor (T&&)  "  << id << "(" << o.id << ")"<< std::endl; }
	~to()						{ std::cout << "dtor       ~"  << id                  << std::endl; }
	to&  operator=(const to& o)			{ std::cout << "= cp        "  << id << " = " << o.id << std::endl;  return *this; }
	to&  operator=(to&& o)				{ std::cout << "= mv        "  << id << " = " << o.id << std::endl;  return *this; }
	int id = 0;
};



				#endif
