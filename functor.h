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

// PREDICATE
template<class T> 	bool is_even(const T& t) { return  t%2; }
template<class T> 	bool is_odd (const T& t) { return  !bool(t%2); }

				};

				#endif
