
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


bool   f(int )                         {return true;};
struct fo_t	{ bool operator()(int) {return true;}; };
struct mfo_t	{ bool mf(int)         {return true;}; };
struct empty_t  {};
auto lam = [](int x)->bool {return x==0;};
typedef decltype(lam) lam_t;



////////////////////////////////////////////////////////////////////////



int main() {

	//setw(20)<<""        <<   "\tCt\th_cIt\tIt\tinIt\tStack\tQueue\tIoable\tisF\trmpF\trmrF\tisPTR\tisREF\tisMFP\tiFCT\tiFN\n";
	cout <<  endl <<   left 
		<< setw(26)<<""        <<   " is  has  is  is      is      is          is  is  is  is  is \n"
		<< setw(26)<<""        <<   " CT  cns  IT inpt    Queue    F  is  is  Ptr Ref  MF  FN PRED\n"
		<< setw(26)<<""        <<   "     IT       IT  is      is     F    F          Ptr     ICAT\n"
		<< setw(26)<<""        <<   "                 Stack    IO-    rm  rm                  E   \n"
		<< setw(26)<<""        <<   "                         able    P   Ref                     \n";

	#define for_T(name)  __ setw(26) << name \
		<<   "  " << (is_container<T>::value                                   ? "+" : "\u2219")\
		<<  "   " << (has_const_iterator<T>::value                             ? "+" : "\u2219")\
		<<  "   " << (is_iterator<T>::value                                    ? "+" : "\u2219")\
		<<  "   " << (is_input_iterator<T>::value                              ? "+" : "\u2219")	/* incorrect*/ \
		<<  "   " << (is_stack<T>::value                                       ? "+" : "\u2219")\
		<<  "   " << (is_queue<T>::value                                       ? "+" : "\u2219")\
		<<  "   " << (is_ioable<T>::value                                      ? "+" : "\u2219")\
		<<  "   " << (std::is_function<T>::value                               ? "+" : "\u2219")\
		<<  "   " << (std::is_function<remove_pointer<T>::type>::value         ? "+" : "\u2219")\
		<<  "   " << (std::is_function<remove_reference<T>::type>::value       ? "+" : "\u2219")\
		<<  "   " << (std::is_pointer<T>::value                                ? "+" : "\u2219")\
		<<  "   " << (std::is_reference<T>::value                              ? "+" : "\u2219")\
		<<  "   " << (std::is_member_function_pointer<T>::value                ? "+" : "\u2219")\
		<<  "   " << (is_fn<T>::value                                          ? "+" : "\u2219")\
		<<  "   " << (is_predicate<T,int>::value                               ? "+" : "\u2219")\
		<<  "   " << (is_predicate<T,const int&>::value                               ? "+" : "\u2219")\
	;

		//<<  "   " << (is_predicate<T,int>::value && std::is_same<typename std::function<T>(0)::result_type, int>::value    ? "+" : "\u2219")

	{ typedef vector<int>  T;
	for_T(   "vector<int>"); }

	{ typedef set<int,std::greater<int>>  T;
	for_T(   "set<int,greater<int>>"); }

	{ typedef vector<int>::iterator  T;
	for_T(   "vector<int>::iterator"); }

	{ typedef deque<int>::iterator  T;
	for_T(   "deque<int>::iterator"); }

	{ typedef std::ostream_iterator<int>   T;
	for_T(   "ostream_it<int>::it"); }

	{ typedef std::istream_iterator<int>   T;
	for_T(   "istream_it<int>::it"); }

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
	for_T(   "bool T(int)");  }

	{ typedef bool T();
	for_T(   "bool T()");  }

	{ typedef bool (*T)();
	for_T(   "bool (*T)()");  }

	// errors
	//{ typedef bool (&T)();
	//for_T(   "bool (&T)()");  }

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

	/*
	{ typedef std::unary_negate<int>  T;
	for_T(   "std::unary_negate<int>");  }

	{ typedef std::binary_negate<int>  T;
	for_T(   "std::binary_negate<int>");  }
	*/

	{ typedef std::less<int>  T;
	for_T(   "std::less<int>");  }

	{
	//#define  T  [](){return true;}
	//for_T(     "[](){return true;}"); 
	}

}
