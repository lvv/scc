#ifndef  LVV_REGEX_H
#define  LVV_REGEX_H
///////////////////////////////////////////////////////////////////// REGEX

//template<typename T>	struct  is_string		: std::false_type {};
//template<>		struct  is_string <std::string>	: std::true_type  {};

#include <regex> 	 // C++11;   std::regex - 4.7.0  fail with: scc 'RS("abc", R("abc"))'
	using std::regex;
	using std::cmatch;
	using std::regex_match;
	using std::match_results;
	using std::regex_token_iterator;
	using std::sregex_token_iterator;
	using std::cregex_token_iterator;

regex operator "" _R (const char* p, size_t n)	{ return regex(p); };

bool  operator ==     (const char  *p,  const regex &e)	{ return regex_match(p,e); };
bool  operator ==     (const string s,  const regex &e)	{ return regex_match(s,e); };


/*

		// RR accept const char*  as regex
			template <class traits, class charT>
			basic_string<charT>
		RR (
			const basic_string<charT>& s,
			//const basic_regex<charT, traits>& e,
			const char* r,
			const basic_string<charT>& fmt,
			boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default
		)  {
			return boost::regex_replace<traits, charT>  (s, boost::regex(r), fmt, flags);
		}
*/



	#define		R		std::regex
	#define		FMT		std::format

	#define		RM		std::regex_match
	//#define		RS		std::regex_search
	#define		RR		std::regex_replace
		// usage: scc 'str s="aa bb"; RR(s, R("(\\w+)"),"*\\1*")'

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


#endif	// LVV_REGEX_H
