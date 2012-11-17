				#ifndef  STO_DEBUG_H
				#define  STO_DEBUG_H

				#include <iostream>
				#include <vector>
				#include <deque>
				#include <stack>
				#include <set>
				#include <map>
				#include <tuple>
				#include <list>
				#include <forward_list>

				#include <cxxabi.h>

				#include "scc/simple.h"



				namespace sto {

//////////////////////////////////////////////////////////////////////////////////////////////  PTYPE / PVTYPE

////  TYPE2NAME

	template <typename T>
const char* type2name() {
	const char* t_name = typeid(T).name();
	int status;
	return abi::__cxa_demangle(t_name, NULL, NULL, &status);
}

/////  REF 2 NAME

template <typename T>	struct ref2name                      { static constexpr const char* value =  "";};
template <typename T>	struct ref2name <const T>            { static constexpr const char* value =  "const";};
template <typename T>	struct ref2name <volatile T>         { static constexpr const char* value =  "volatile";};
template <typename T>	struct ref2name <volatile const T>   { static constexpr const char* value =  "volatile const";};

template <typename T>	struct ref2name <T&>                 { static constexpr const char* value =  "&";};
template <typename T>	struct ref2name <const T&>           { static constexpr const char* value =  "const &";};
template <typename T>	struct ref2name <volatile T&>        { static constexpr const char* value =  "volatile &";};
template <typename T>	struct ref2name <volatile const  T&> { static constexpr const char* value =  "volatile const &";};

template <typename T>	struct ref2name <T&&>                { static constexpr const char* value =  "&&";};
template <typename T>	struct ref2name <const T&&>          { static constexpr const char* value =  "const &&";};
template <typename T>	struct ref2name <volatile T&&>       { static constexpr const char* value =  "volatile &&";};
template <typename T>	struct ref2name <volatile const T&&> { static constexpr const char* value =  "volatile const &&";};


#define ptype(T)  std::cout <<  type2name<T>() << " " << ref2name<T>::value <<  std::endl;
#define pvtype(V)  ptype(decltype(V));

//// Template Type Dumper

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


//////////////////////////////////////////////////////////////////////////////////////////////// DEBUG VARS
std::vector<int>	__attribute__((unused)) 	v9      {0,1,2,3,4,5,6,7,8,9},  v0, v23{2,3};
std::deque<int>		__attribute__((unused)) 	d9      {0,1,2,3,4,5,6,7,8,9},  d0, d23{2,3};
std::list<int>		__attribute__((unused)) 	l9      {0,1,2,3,4,5,6,7,8,9},  l0, l23{2,3};
std::forward_list<int>	__attribute__((unused)) 	fl9	{0,1,2,3,4,5,6,7,8,9},  fl0, fl23{2,3};
int			__attribute__((unused))		a9[]    {0,1,2,3,4,5,6,7,8,9},  a23[]{2,3};
char			__attribute__((unused))		c9[99]	{"abc-123"},   c23[]{"BC"},   c1='A',  c0='0', cz='\0', ca='a';
const char		__attribute__((unused))		cc9[99]	{"abc-123"},  cc23[]{"bc"},  cc1='A', cc0='0';
std::string		__attribute__((unused))		s9	{"abc-123"},  s0, s23{"bc"},  s1="a";
std::vector<std::string>__attribute__((unused))		vs9	{"", "a", "bb", "ccc", "dddd", "eeeee", "ffffff", "ggggggg", "hhhhhhhh", "kkkkkkkkk"};
std::vector<const char*>__attribute__((unused))		vc9	{"", "a", "bb", "ccc", "dddd", "eeeee", "ffffff", "ggggggg", "hhhhhhhh", "kkkkkkkkk"};
vector<tuple<int,str>>  __attribute__((unused))		vt9	{MT(1, "a"), MT(2,"bb"), MT(3,"ccc"), MT(4,"dddd"), MT(5,"eeeee"), MT(6,"ffffff"), MT(7,"ggggggg"), MT(8,"hhhhhhhh"), MT(9,"kkkkkkkkk")};
std::map<int,str>  __attribute__((unused))		m9	{MP(1, "a"), MP(2,"bb"), MP(3,"ccc"), MP(4,"dddd"), MP(5,"eeeee"), MP(6,"ffffff"), MP(7,"ggggggg"), MP(8,"hhhhhhhh"), MP(9,"kkkkkkkkk")};
std::set<int>  __attribute__((unused))			st9	{0,1,2,3,4,5,6,7,8,9};
// rvalues
//static std::vector<int>	__attribute__((unused))		mk_v9()	{ return  v9; };
static std::vector<int>	__attribute__((unused))		mk_v9()	{ return  std::vector<int>{0,1,2,3,4,5,6,7,8,9}; };
static std::vector<int>	__attribute__((unused))		mk_v23(){ return  v23; };
static std::vector<int>	__attribute__((unused))		mk_v0()	{ return  v0; };
static std::deque<int>	__attribute__((unused))		mk_d9()	{ return  d9; };


				};	// namespace sto
				#endif  // STO_DEBUG_H
