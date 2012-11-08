				#ifndef  SCC_FUNCTOR_H
				#define  SCC_FUNCTOR_H


				namespace sto {

//  CTYPE.H
char	toupper (char c) { return std::toupper((int)c); }
char	tolower (char c) { return std::tolower((int)c); }

bool	isalnum (char c) { return std::isalnum ((int)c); }
bool	isalpha (char c) { return std::isalpha ((int)c); }
bool	iscntrl (char c) { return std::iscntrl ((int)c); }
bool	isdigit (char c) { return std::isdigit ((int)c); }
bool	isgraph (char c) { return std::isgraph ((int)c); }
bool	islower (char c) { return std::islower ((int)c); }
bool	isprint (char c) { return std::isprint ((int)c); }
bool	ispunct (char c) { return std::ispunct ((int)c); }
bool	isspace (char c) { return std::isspace ((int)c); }
bool	isupper (char c) { return std::isupper ((int)c); }
bool	isxdigit(char c) { return std::isxdigit((int)c); }


// MATH
template<class T> 	T abs(T t) { return  t > 0 ?  t : -t; }
template<class T> 	auto add(T a, T b) -> decltype(a+b)  { return  a+b; }
template<class T> 	auto sub(T a, T b) -> decltype(a-b)  { return  a-b; }
template<class T> 	auto mul(T a, T b) -> decltype(a*b)  { return  a*b; }
template<class T> 	auto div(T a, T b) -> decltype(a/b)  { return  a/b; }

// PREDICATE
template<class T> 	bool is_odd (const T& t) { return  t%2; }
template<class T> 	bool is_even(const T& t) { return  !bool(t%2); }

// equal, less, greater
template<class T> 	struct  eq_t { T t; eq_t (const T& t):t(t){};  bool operator()(const T& x) { return  x==t; } };
template<class T> 	struct  gt_t { T t; gt_t (const T& t):t(t){};  bool operator()(const T& x) { return  x>t; } };
template<class T> 	struct  ls_t { T t; ls_t (const T& t):t(t){};  bool operator()(const T& x) { return  x<t; } };
template<class T> 	eq_t<T> eq(T t)  { return eq_t<T>(t); } 
template<class T> 	gt_t<T> gt(T t)  { return gt_t<T>(t); } 
template<class T> 	ls_t<T> ls(T t)  { return ls_t<T>(t); } 

				};

				#endif
