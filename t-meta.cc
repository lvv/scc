
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
struct has_const_iterator_t {
	template<typename C>  static char  test (typename C::const_iterator*);
	template<typename C>  static long  test (...);
	static const bool value = sizeof(test<T>(0)) == 1;
	typedef T type;
};
	template<typename T>   constexpr bool has_const_iterator() { return  has_const_iterator_t <T>::value; } ;



///// func types


bool   f(int )                         { return true; };
struct fo_t	{ bool operator()(int) { return true; }; };
struct mfo_t	{ bool mf(int)         { return true; }; };
struct empty_t  {};
auto lam = [](int x)->bool { return x==0; };
typedef decltype(lam) lam_t;


////////////////////////////////////////////////////////////////////////



int main() {

	//setw(20)<<""        <<   "\tCt\th_cIt\tIt\tinIt\tStack\tQueue\tIoable\tisF\trmpF\trmrF\tisPTR\tisREF\tisMFP\tiFCT\tiFN\n";
	cout <<  endl <<   left 
		<< setw(26)<<""        <<   " is  is  has  is  is      is      is     \n"
		<< setw(26)<<""        <<   " Co  Rg  cns  IT inpt    Queue   call    \n"
		<< setw(26)<<""        <<   "         IT       IT  is      is  1   is \n"
		<< setw(26)<<""        <<   "                     Stack    IO-    call\n"
		<< setw(26)<<""        <<   "                             able     2  \n";

	#define for_T(name)  __ setw(26) << name \
		<<  "  " <<  (is_collection<T>()                                   ? "+" : "\u2219")\
		<<  "  " <<  (is_range<T>::value                                   ? "+" : "\u2219")\
		<<  "   " << (has_const_iterator<T>()                             ? "+" : "\u2219")\
		<<  "   " << (is_iterator<T>::value                                    ? "+" : "\u2219")\
		<<  "   " << (is_input_iterator<T>()                              ? "+" : "\u2219")	/* incorrect*/ \
		<<  "   " << (is_stack<T>::value                                       ? "+" : "\u2219")\
		<<  "   " << (is_queue<T>::value                                       ? "+" : "\u2219")\
		<<  "   " << (is_ioable_t<T>::value                                      ? "+" : "\u2219")\
		<<  "   " << (is_callable<T, bool(int)>::value                         ? "+" : "\u2219")\
		<<  "   " << (is_callable<T, bool(int, int)>::value                    ? "+" : "\u2219")\
	;


cout << "CONTAINER ---------------------------------------------------------------------\n";
	{ typedef array<int,2>  T;
	for_T(   "array<int,2>"); }

	{ typedef numeric_range<int>  T;
	for_T(   "numeric_range<int>"); }

	{ typedef iterator_range<vint::iterator>  T;
	for_T(   "iterator_range<vint::it>"); }

	{ typedef vector<int>  T;
	for_T(   "vector<int>"); }

	{ typedef set<int,std::greater<int>>  T;
	for_T(   "set<int,greater<int>>"); }

	{ typedef set<int>  T;
	for_T(   "set<int>"); }

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

cout << "ITERATOR ---------------------------------------------------------------------\n";
	{ typedef vector<int>::iterator  T;
	for_T(   "vector<int>::iterator"); }

	{ typedef deque<int>::iterator  T;
	for_T(   "deque<int>::iterator"); }

	{ typedef std::ostream  T;
	for_T(   "ostream::it"); }

	{ typedef std::ostream_iterator<int>   T;
	for_T(        "ostream_it<int>::it"); }

	{ typedef std::istream_iterator<int>   T;
	for_T(        "istream_it<int>::it"); }

	{ typedef string::iterator  T;
	for_T(   "string::iterator"); }

	/*
	{ typedef vector<const int&>::iterator  T;
	for_T(   "vector<const int&>::iterator"); }

	{ typedef vector<int&&>::iterator  T;
	for_T(   "vector<int&&>::iterator"); }
	*/

	
cout << "STRING ---------------------------------------------------------------------\n";
	{ typedef string  T;
	for_T(   "string"); }

	{ typedef fld  T;
	for_T(   "fld"); }

	{ typedef std::basic_string<char, std::char_traits<char>, nd_allocator<char>> T;
	for_T(   "basic_string<T,....>"); }

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

cout << "FUNCTION ---------------------------------------------------------------------\n";
	
	{ typedef bool T(int);
	for_T(   "bool T(int)");  }

	{ typedef int* T(int);
	for_T(   "int* T(int)");  }

	{ typedef bool T(const int&);
	for_T(   "bool T(const int&)");  }

	{ typedef bool T();
	for_T(   "bool T()");  }

	{ typedef bool (*T)(int);
	for_T(   "bool (*T)(int)");  }

	{ typedef bool (&T)();
	for_T(   "bool (&T)()");  }

	{ typedef decltype(f) T;
	for_T(   "decltype(f)");  }

	{ typedef decltype(::sin)  T;
	for_T(   "decltype(::sin)");  }

	{ typedef fo_t  T;
	for_T(   "fo_t");  }

	{ typedef std::function<bool(int)> T;
	for_T(   "std::function<bool(int)>");  }

	{ typedef std::function<bool()> T;
	for_T(   "std::function<bool()>");  }

	{ typedef std::function<bool(*)()> T;
	for_T(   "std::function<bool(*)()>");  }

	{ typedef lam_t  T;
	for_T(   "lam_t");  }

	{ typedef std::function<lam_t> T;
	for_T(   "std::function<lam_t>");  }

	{ typedef std::negate<int>  T;
	for_T(   "std::negate<int>");  }


	{ typedef std::less<int>  T;
	for_T(   "std::less<int>");  }

}
