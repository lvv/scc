				#ifndef  LVV_DEBUG_H
				#define  LVV_DEBUG_H

	#include <iostream>
	#include <vector>
	#include <deque>
	#include <stack>
	#include <set>

//////  TYPE2NAME

	#include <cxxabi.h>


	template <typename T>
const char* type2name() {
	const char* t_name = typeid(T).name();
	int status;
	return abi::__cxa_demangle(t_name, NULL, NULL, &status);
}

//////////////////////////////////////////////////////////////////////////////////////////  REF 2 NAME

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

//////////////////////////////////////////////////////////////////////////////////////////////  printT

#define printT(T)  std::cout << ref2name<T>::value << "  \t---   \t"  <<  type2name<T>()  <<  std::endl;
#define printToV(V)  printT(decltype(V));

////////////////////////////////////////////////////////////////////////////////////////////// Template Type Dumper

template<typename> void ttd();


//////////////////////////////////////////////////////////////////////////////////////////////  TRACE_OBJ

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
	to(to&& o)		: id(this->created) 	{ std::cout << "ctor (T&&)  "  << id << "(" << o.id << ")"<< std::endl; o.id = -o.id; }
	~to()						{ std::cout << "dtor       ~"  << id                      << std::endl; }
	to&  operator=(const to& o)			{ std::cout << "= cp        "  << id << " = " << o.id << std::endl;  return *this; }
	to&  operator=(to&& o)				{ std::cout << "= mv        "  << id << " = " << o.id << std::endl;   o.id = -o.id;  return *this; }
	int id = 0;
};

	std::ostream&
operator<<      (std::ostream& os, const to& o) { std::cout << "to{" << o.id << "}";  return os; };

//////////////////////////////////////////////////////////////////////////////////////////////// debug vars

std::vector<int>		__attribute__((unused)) 	v9      {0,1,2,3,4,5,6,7,8,9},  v0, v23{2,3};
std::deque<int>		__attribute__((unused)) 	d9      {0,1,2,3,4,5,6,7,8,9},  d0, d23{2,3};
std::stack<int>	__attribute__((unused))		st0;
std::set<int>	__attribute__((unused))		sk0;
int		__attribute__((unused))		a9[]    {0,1,2,3,4,5,6,7,8,9},  a23[]{2,3};
char		__attribute__((unused))		c9[100]     = "abcdefgh-123",   c23[]="bc",   c1='a',  c0='\0';
const char	__attribute__((unused))		cc9[100]    = "abcdefgh-123",  cc23[]="bc",  cc1='a', cc0='\0';
std::string	__attribute__((unused))		s9           ("abcdefgh-123"),  s0, s23  ("bc"),  s1="a";
std::vector<std::string>	__attribute__((unused))		vs9{"", "a", "bb", "ccc", "dddd"};

// rvalues
static std::vector<int>  mk_v9()	{ return  v9; };
static std::deque<int>   mk_d9()	{ return  d9; };
static std::vector<int>  mk_v23()	{ return  v23; };
static std::vector<int>  mk_v0()	{ return  v0; };


				#endif
