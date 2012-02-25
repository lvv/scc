//#include<iostream>
//#include<type_traits>
//#include"lvv/lvv.h"
#include <type_traits>
#include <typeinfo>
#include<scc/simple.h>
#include<scc/allocator.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////  IS_PRINTABLE

	template<class T> T& lvalue_of_type();
	template<class T> T  rvalue_of_type();

	template<class T>
struct is_printable {
	template<class U>  static char  test (char(*)[sizeof( lvalue_of_type<std::ostream>() << rvalue_of_type<U>())]);
	template<class U>  static long  test (...);

	enum { value = 1 == sizeof test<T>(0) };
	typedef std::integral_constant<bool, value> type;
};


/////////////////////////////////////////////////////////////////////////

	template<typename T>
struct has_const_iterator {
	template<typename C>  static char  test (typename C::const_iterator*);
	template<typename C>  static long  test (...);
	static const bool value = sizeof(test<T>(0)) == 1;
	typedef T type;
};




////////////////////////////////////////////////////////////////////////

struct out_t {};

template<typename S> struct is_sink{ const static bool value =  std::is_same<S,std::ostream>::value || std::is_same<S,out_t>::value; };

int main() {

	__ endl <<   left <<   setw(25) <<   "TYPE" <<   "\tCntnr\t h_CI\t Ptr\t Iter\t Stack\t Queue\t Ioable";

	#define for_T(name)  __ setw(25) << name \
		<<  "\t  " << is_container<T>::value\
		<<  "\t  " << has_const_iterator<T>::value\
		<<  "\t  " << is_printable<T>::value\
		<<  "\t  " << is_iterator<T>::value\
		<<  "\t  " << is_stack<T>::value\
		<<  "\t  " << is_queue<T>::value\
		<<  "\t  " << is_ioable<T>::value\
	;

	{ typedef vector<int>  T;
	for_T(   "vector<int>"); }

	{ typedef vector<int>::iterator  T;
	for_T(   "vector<int>::iterator"); }

	{ typedef deque<int>::iterator  T;
	for_T(   "deque<int>::iterator"); }

	{ typedef set<int>  T;
	for_T(   "set<int>"); }

	{ typedef set<int,std::greater<int>>  T;
	for_T(   "set<int,std::greater<int>>"); }

	{ typedef map<string, int>  T;
	for_T(   "map<string, int>"); }

	{ typedef pair<string,int>  T;
	for_T(   "pair<string,int>"); }

	{ typedef tuple<string,int>  T;
	for_T(   "tuple<string,int>"); }

	{ typedef queue<int>  T;
	for_T(   "queue<int>"); }

	{ typedef priority_queue<int>  T;
	for_T(   "priority_queue<int>"); }

	{ typedef stack<int>  T;
	for_T(   "stack<int>"); }

	{ typedef string  T;
	for_T(   "string"); }

	{ typedef std::basic_string<char, std::char_traits<char>, nd_allocator<char>> T;
	for_T(   "basic_string<T,....>"); }

	{ typedef string::iterator  T;
	for_T(   "string::iterator"); }

	{ typedef int	T[5];
	for_T(   "int[5]"); }

	{ typedef char	T[5];
	for_T(   "char[5]"); }

	{ typedef const char	T[5];
	for_T(   "const char[5]"); }

	{ typedef const char*  T;
	for_T(   "const char*");  }

	{ typedef int*  T;
	for_T(   "int*");  }

	{ struct T {int a;}; 
	for_T(   "struct");  }

	cout
		<< is_sink<int>::value
		<< is_sink<ostream>::value
		<< is_sink<out_t>::value
		<< endl
		;
}



