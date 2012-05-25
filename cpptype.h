				#ifndef  LVV_CPPTYPE_H
				#define  LVV_CPPTYPEG_H

				namespace cpp {
char	toupper(char c) { return ::toupper((int)c); }
char	tolower(char c) { return ::tolower((int)c); }

bool	isalnum (char c) { return ::isalnum ((int)c); }
bool	isalpha (char c) { return ::isalpha ((int)c); }
bool	iscntrl (char c) { return ::iscntrl ((int)c); }
bool	isdigit (char c) { return ::isdigit ((int)c); }
bool	isgraph (char c) { return ::isgraph ((int)c); }
bool	islower (char c) { return ::islower ((int)c); }
bool	isprint (char c) { return ::isprint ((int)c); }
bool	ispunct (char c) { return ::ispunct ((int)c); }
bool	isspace (char c) { return ::isspace ((int)c); }
bool	isupper (char c) { return ::isupper ((int)c); }
bool	isxdigit(char c) { return ::isxdigit((int)c); }

				}
				#endif
