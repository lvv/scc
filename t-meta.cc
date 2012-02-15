//#include<iostream>
//#include<type_traits>
//#include"lvv/lvv.h"
#include <type_traits>
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



/////////////////////////////////////////////////////////////////////////

/* does not work with T[N] */
	template<typename T>
struct is_iterator {
	//static T(&)[N] makeT();
	typedef void * twoptrs[2];						// sizeof(twoptrs) > sizeof(void *)
				static twoptrs &			test(...);		// Common case
	template<typename  U>	static typename U::iterator_category*	test(U);	// Iterator
	template<typename  U>	static void *				test(U*);	// Pointer
	//template<typename  U>	static void *				test(U(&)[N]);	// C-array

	static const bool value = sizeof(test(T())) == sizeof(void *);
	//static const bool value = sizeof(test(makeT())) == sizeof(void *);
	//static const bool value = sizeof(test(T(&)[N])) == sizeof(void *);
};

template <typename T>	constexpr bool		is_it(T** x)	{return true;}
template <typename T>	constexpr bool		is_it(T* x)	{return false;}
template <typename T, size_t N>	constexpr bool  is_it(T (*x)[N] )	{return true;}


////////////////////////////////////////////////////////////////////////

struct out_t {};

template<typename S> struct is_sink{ const static bool value =  std::is_same<S,std::ostream>::value || std::is_same<S,out_t>::value; };

int main() {

	__ endl <<   left <<   setw(25) <<   "TYPE" <<   "\tis_Ct\t h_CI\t is_Pr\t is_It\n";

	#define for_T(name)  __ setw(25) << name \
		<<  "\t  " << is_container<T>::value\
		<<  "\t  " << has_const_iterator<T>::value\
		<<  "\t  " << is_printable<T>::value\
		/*<<  "\t  " << is_iterator<T>::value*/\
		<<  "\t  " << is_it((T*)nullptr)\
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
		<< endl
		;
}



