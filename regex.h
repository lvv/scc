#ifndef  LVV_REGEX_H
#define  LVV_REGEX_H

#include <type_traits>
#include <string>

template<typename T>	struct  is_string		: std::false_type {};
template<>		struct  is_string <std::string>	: std::true_type  {};

#include <regex> 
	using std::regex;
	using std::cmatch;
	using std::regex_match;
	using std::match_results;
	using std::regex_token_iterator;
	using std::sregex_token_iterator;
	using std::cregex_token_iterator;
/*
*/

std::regex operator "" _R (const char* p, size_t n)	{ return std::regex(p); };


	template<typename S>
	typename std::enable_if<is_string<S>::value, bool>::type
operator == (const S s,  const std::regex &e)		{ return std::regex_match(s.begin(), s.end(), e); };
	// specialization  for c-string
	bool  
operator == (const char  *p,  const std::regex &e)	{ return std::regex_match(p,e); };


	// regex_search (does not work) - not yet implemented in LIBSTDC++
	template<typename S>
	typename std::enable_if<is_string<S>::value, bool>::type
operator %= (const S s,  const std::regex &e)		{ return std::regex_search(s.begin(), s.end(), e); };


	// convert to regex operator
	template<typename S>
	typename std::enable_if<is_string<S>::value, std::regex>::type
operator ~     (const S e)	{ return  std::regex(e.begin(), e.end()); };



	#define		R		std::regex
	#define		FMT		std::format

	#define		RM		std::regex_match
	//#define		RS		std::regex_search
	#define		RR		std::regex_replace
		// usage: scc 'str s="aa bb"; RR(s, R("(\\w+)"),"*\\1*")'

/*
	//#define	M		std::match
	#define		CM		std::cmatch
	#define		SM		std::smatch

	//typedef	std::regex_iterator		RI;
	typedef		std::sregex_iterator          SRI;
	typedef		std::cregex_iterator          CRI;
		// usage:  echo 'aa bb' | scc 'WRL {SRI it(line.begin(), line.end(), R("\\w+")), e; while (it!=e) cout << *it++ << endl;}
	//typedef	std::regex_token_iterator     RTI;
	typedef		std::sregex_token_iterator    SRTI;
	typedef		std::cregex_token_iterator    CRTI;
	#define		MRTI		std::make_regex_token_iterator

*/

#endif	// LVV_REGEX_H