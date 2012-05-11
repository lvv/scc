
#include "scc/simple.h"
#include "scc/allocator.h"
#include "scc/scc.h"

#include <type_traits>
#include <typeinfo>
#include <functional>
using namespace std;


/////////////////////////////////////////////////////////////////////////  IS_PRINTABLE

	template<class T> T& lvalue_of_type();
	template<class T> T  rvalue_of_type();


/////////////////////////////////////////////////////////////////////////


	template<typename T>
struct has_const_iterator {
	template<typename C>  static char  test (typename C::const_iterator*);
	template<typename C>  static long  test (...);
	static const bool value = sizeof(test<T>(0)) == 1;
	typedef T type;
};



///// func types


bool f_t()                          {return true;};
struct fo_t	{ bool operator()() {return true;}; };
struct mfo_t	{ bool mf()         {return true;}; };
struct empty_t  {};
auto lam = [](int x){return x==0;};



////////////////////////////////////////////////////////////////////////



int main() {

	__ endl <<   left <<   setw(25) <<   "TYPE"
	        <<   "\tCt\t h_cIt\t It\t inIt\t Stack\t Queue\t Ioable\t isF\t rmpF\t isPTR\t isREF\t isMFP";

	#define for_T(name)  __ setw(25) << name \
		<<  "\t  " << is_container<T>::value\
		<<  "\t  " << has_const_iterator<T>::value\
		<<  "\t  " << is_iterator<T>::value\
		<<  "\t  " << is_input_iterator<T>::value\
		<<  "\t  " << is_stack<T>::value\
		<<  "\t  " << is_queue<T>::value\
		<<  "\t  " << is_ioable<T>::value\
		<<  "\t  " << std::is_function<T>::value\
		<<  "\t  " << std::is_function<remove_pointer<T>::type>::value\
		<<  "\t  " << std::is_pointer<T>::value\
		<<  "\t  " << std::is_reference<T>::value\
		<<  "\t  " << std::is_member_function_pointer<T>::value\
		<<  "\t  " << is_fn<T>::value\
	;

	{ typedef vector<int>  T;
	for_T(   "vector<int>"); }

	{ typedef vector<int>::iterator  T;
	for_T(   "vector<int>::iterator"); }

	{ typedef deque<int>::iterator  T;
	for_T(   "deque<int>::iterator"); }

	{ typedef std::ostream_iterator<int>   T;
	for_T(   "ostream_iterator<int>::iterator"); }

	{ typedef std::istream_iterator<int>   T;
	for_T(   "istream_iterator<int>::iterator"); }

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

	{ typedef fld  T;
	for_T(   "fld"); }

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

cout << endl;
	
	{ typedef bool T();
	for_T(   "bool(*)()");  }

	{ typedef bool T();
	for_T(   "bool(&)()");  }

	{ typedef decltype(f_t) T;
	for_T(   "f_t");  }

	{ typedef fo_t  T;
	for_T(   "fo_t");  }

	{ typedef std::function<bool()> T;
	for_T(   "std::function<bool()>");  }

	{ typedef std::function<bool(*)()> T;
	for_T(   "std::function<bool(*)()>");  }

	{ typedef decltype(lam)  T;
	for_T(   "lambda");  }

	{ typedef std::function<decltype(lam)> T;
	for_T(   "std::function<decltype(lam)>");  }

	{ typedef std::negate<int>  T;
	for_T(   "std::negate<int>");  }

	{
	//#define  T  [](){return true;}
	//for_T(     "[](){return true;}"); 
	}

}
