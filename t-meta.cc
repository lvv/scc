//#include<iostream>
//#include<type_traits>
//#include"lvv/lvv.h"
#include<scc/simple>

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


/////////////////////////////////////////////////////////////////////////  IS_CONTAINER

	template <typename T>
struct is_container {	// from http://stackoverflow.com/questions/4347921/sfinae-compiler-troubles
	template <typename U>
	static char test(
		U* u,
		typename U::const_iterator b = ((U*)0)->begin(),
		typename U::const_iterator e = ((U*)0)->end()
	);
	template <typename U> static long test(...);

	enum { value = sizeof test<T>(0) == 1 };
};

template<typename T, size_t N>	struct is_container<T[N]> 	: std::true_type { };
template<size_t N>		struct is_container<char[N]>	: std::false_type { };
template<>			struct is_container<std::basic_string<char>> : std::false_type { };

/////////////////////////////////////////////////////////////////////////
/* Brokern
	template<class T>
struct is_iterator {
	static T makeT();
	typedef void * twoptrs[2];  // sizeof(twoptrs) > sizeof(void *)
	static twoptrs & test(...); // Common case
	template<class R> static typename R::iterator_category * test(R); // Iterator
	template<class R> static void * test(R *); // Pointer
	static const bool value = sizeof(test(makeT())) == sizeof(void *); 
};
*/
////////////////////////////////////////////////////////////////////////

struct out_t {};

template<typename S> struct is_sink{ const static bool value =  std::is_same<S,std::ostream>::value || std::is_same<S,out_t>::value; };

int main() {

	cout << left;  cout.width(25);
	__ endl, "type",  "is_Ct\t", "h_CI", "is_P", endl; 

	#define for_T(name) cout.width(25);  _ name; \
		outln ("\t") \
		<<  is_container<T>::value\
		<<  has_const_iterator<T>::value\
		<<  is_printable<T>::value\
		<<  is_iterator<T>::value\
	;

	{ typedef vector<int>  T;
	for_T(   "vector<int>"); }

	{ typedef vector<int>::iterator  T;
	for_T(   "vector<int>::iterator"); }

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

	{ typedef string  T;
	for_T(   "string"); }

	{ typedef string::iterator  T;
	for_T(   "string::iterator"); }

	{ typedef int	T[5];
	for_T(   "int[5]"); }

	{ typedef char	T[5];
	for_T(   "char[5]"); }

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
		;
}


	
