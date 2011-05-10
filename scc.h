#ifndef  LVV_SCC_H
#define  LVV_SCC_H

///////////////////////////////////////////////////////////////////// BOOST
#ifndef NO_BOOST

	//#include <regex> 	 // std::regex - 4.6.0  fail with: scc 'RS("abc", R("abc"))'

	#include <boost/regex.hpp>
		using boost::regex;
		using boost::cmatch;
		using boost::regex_match;
		using boost::regex_token_iterator;
		using boost::sregex_token_iterator;
		using boost::cregex_token_iterator;
	#include <boost/format.hpp>
		using boost::format;
	//using namespace boost;
#endif

///////////////////////////////////////////////////////////////////////////////  STR
struct str: string {

	// CTOR
	str(const char*   s)	: string(s) {};
	str(const string& s)	: string(s) {};
	str(int           i)	: string()  {*this = (long)i;};
	str(long          i)	: string()  {*this = (long)i;};
	str(double        i)	: string()  {*this = (double)i;};
	str()			: string()  {};

	// op= assign
	str& operator  = (int I) { ostringstream OS;   OS <<         I;   this->string::assign(OS.str());  return *this; }
	str& operator += (int I) { ostringstream OS;   OS << int(*this) + I;   this->string::assign(OS.str());  return *this; }
	str& operator -= (int I) { ostringstream OS;   OS << int(*this) - I;   this->string::assign(OS.str());  return *this; }
	str& operator *= (int I) { ostringstream OS;   OS << int(*this) * I;   this->string::assign(OS.str());  return *this; }
	str& operator /= (int I) { ostringstream OS;   OS << int(*this) / I;   this->string::assign(OS.str());  return *this; }
	str& operator %= (int I) { ostringstream OS;   OS << int(*this) / I;   this->string::assign(OS.str());  return *this; }

	str& operator  = (long I) { ostringstream OS;   OS <<         I;   this->string::assign(OS.str());  return *this; }
	str& operator += (long I) { ostringstream OS;   OS << long(*this) + I;   this->string::assign(OS.str());  return *this; }
	str& operator -= (long I) { ostringstream OS;   OS << long(*this) - I;   this->string::assign(OS.str());  return *this; }
	str& operator *= (long I) { ostringstream OS;   OS << long(*this) * I;   this->string::assign(OS.str());  return *this; }
	str& operator /= (long I) { ostringstream OS;   OS << long(*this) / I;   this->string::assign(OS.str());  return *this; }
	str& operator %= (long I) { ostringstream OS;   OS << long(*this) / I;   this->string::assign(OS.str());  return *this; }

	str& operator  = (double I) { ostringstream OS;   OS <<         I;   this->string::assign(OS.str());  return *this; }
	str& operator += (double I) { ostringstream OS;   OS << double(*this) + I;   this->string::assign(OS.str());  return *this; }
	str& operator -= (double I) { ostringstream OS;   OS << double(*this) - I;   this->string::assign(OS.str());  return *this; }
	str& operator *= (double I) { ostringstream OS;   OS << double(*this) * I;   this->string::assign(OS.str());  return *this; }
	str& operator /= (double I) { ostringstream OS;   OS << double(*this) / I;   this->string::assign(OS.str());  return *this; }
	str& operator %= (double I) { ostringstream OS;   OS << double(*this) / I;   this->string::assign(OS.str());  return *this; }

		template<class T>
	str& operator << (T t) { ostringstream OS;   OS << *this << t;  *this =  OS.str(); return *this; }

	operator const string&	(void) const 	{ return  *(string*)this; }	// converter to std::string&
	operator string&	(void) 		{ return  *(string*)this; }	// converter to std::string&
	operator bool		(void) const 	{ return   this->size() != 0; }	// converter to bool

	// converter to numerics
		
			operator double		(void) { istringstream IS;  double I;  IS.str(*this);  IS >> I;  return I; }
	#if 	 (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6 ) ) ) 
	explicit	operator int		(void) { istringstream IS;  int    I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator long		(void) { istringstream IS;  long   I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator unsigned int	(void) { istringstream IS;  unsigned int    I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator unsigned long	(void) { istringstream IS;  unsigned long    I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator float		(void) { istringstream IS;  double I;  IS.str(*this);  IS >> I;  return I; }
	#endif

	////
	str  operator +  (const char* s) { return  *(std::string*)this +  std::string(s); }	

	// prefix/postfix inc/dec
	long operator++() {                   return *this = long(*this) + 1; }
	long operator--() {                   return *this = long(*this) - 1; }
	long operator++(int) { long old = long(*this); *this = long(*this) + 1; return old; }
	long operator--(int) { long old = long(*this); *this = long(*this) - 1; return old; }
	// TODO for double
};



std::ostream&   operator<<      (ostream& os, const str& s) { os << (std::string)s; return os; };


///////////////////////////////////////////////////////////////////////////////  F

	struct   F_t : std::deque<str> {
		str& 	operator()(size_t I) {
			if (this->size()<I+1) this->resize(I+1);
			return (*this)[I];
		};
	};

	std::ostream&   operator<<      (ostream& os, const deque<str, std::allocator<str> >& C) {              
		os << "{";
		auto it=C.begin();
		for (int i=0;   i < int(C.size())-1;   i++, it++)	os  << *it <<  ", ";
		if (!C.empty())  					os  << *it;
		os << "}";
		return os;
	};

///////////////////////////////////////////////////////////////////////////////  AWK's vars

	F_t F;
	int NF = 0;
	int NR = -1;

	string       __attribute__((unused))	line;

	#ifdef  arg_OFS
	string	     __attribute__((unused))	OFS(arg_OFS);
	#else
	string	     __attribute__((unused))	OFS(" ");
	#endif

	const char*  __attribute__((unused))	CSV="\"((?:(?:\\\\\")|[^\"])*)\"(\\s*,\\s*|$)";

	#ifdef  arg_IFS
	string       __attribute__((unused))	IFS(arg_IFS);
	#else
	string       __attribute__((unused))	IFS("(\\S+)(\\s+|$)");	// IFS is second group (\2)
	#endif

///////////////////////////////////////////////////////////////////////////////  Utils functions

	void	split() {
		#ifdef USE_BOOST
			boost::sregex_token_iterator   ite, it(line.begin(),line.end(), boost::regex(IFS),1);
			while(it!=ite)   F.push_back(str(*it++));
		#else
			stringstream	ss(line);
			string		f;
			F.clear();
			while(ss >> f)   F.push_back(f);
		#endif

		NF = F.size();
	};

	bool  read_line() {
		F.clear();
		if (getline(cin,line)) {
			split();
			++ NR;
			return true;
		} else {
			return false;
		}
	};

	#ifdef xxxUSE_BOOST
		// simplified regex_replace (now accept const char* for regex)
			template <class traits, class charT>
			basic_string<charT>
		RR (
			const basic_string<charT>& s,
	               	const basic_regex<charT, traits>& e,
			const basic_string<charT>& fmt,
			boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default
		)  {
			return boost::regex_replace<traits, charT>  (s, e, fmt, flags);
		}

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

	#endif

	#define WRL  while(read_line())

///// boost

#ifdef  USE_BOOST

#define 	R		boost::regex
//R 	operator "" r(const char * s, size_t n) {return R(s);};
#define		FMT 		boost::format

#define 	RM		boost::regex_match
#define 	RS		boost::regex_search
#define 	RR		boost::regex_replace
		// usage: scc 'S s="aa bb"; RR(s, R("(\\w+)"),"*\\1*")'
	
//#define 	M		boost::match
#define 	CM		boost::cmatch
#define 	SM		boost::cmatch

//typedef 	boost::regex_iterator		RI;
typedef 	boost::sregex_iterator          SRI;
typedef 	boost::cregex_iterator          CRI;		
		// usage:  echo 'aa bb' | scc 'WRL {SRI it(line.begin(), line.end(), R("\\w+")), e; while (it!=e) cout << *it++ << endl;}
//typedef 	boost::regex_token_iterator     RTI;		
typedef 	boost::sregex_token_iterator    SRTI;		
typedef 	boost::cregex_token_iterator    CRTI;		
#define 	MRTI		boost::make_regex_token_iterator 

#endif


#endif // SCC
