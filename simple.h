#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

#if 	defined(__GXX_EXPERIMENTAL_CXX0X__) && (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 4 ) ) ) 
	#define  MODERN_GCC	1
#endif

//////////////////////////////////////////////////////////////////// C
//#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cctype>
#include <cmath>

///////////////////////////////////////////////////////////////////// C++ IO
#include <iostream>
#include <iomanip>
#include <sstream> 

///////////////////////////////////////////////////////////////////// C++ STL
#include <algorithm>
#include <deque>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <limits>
#include <bitset>
///////////////////////////////////////////////////////////////////// C++0X STL
#ifdef  MODERN_GCC
#include <tuple>
#endif
//#include <type_traits>

///////////////////////////////////////////////////////////////////// 

	using	std::cin;
	using	std::cout;
	using	std::endl;
	using	std::string;
	using	std::basic_string;
	using	std::basic_ostream;
	using	std::istream;
	using	std::ostream;
	using	std::vector;
	using	std::deque;
	using	std::set;
	using	std::multiset;
	using	std::map;
	using	std::multimap;
	using	std::stringstream;
	using	std::istringstream;
	using	std::ostringstream;
	using	std::numeric_limits;
	using	std::ostream_iterator;
	using	std::istream_iterator;
	using	std::swap;


///////////////////////////////////////////////////////////////////// BOOST
#ifdef USE_BOOST

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
	#include <boost/utility.hpp>
		// for enable_if
		// for common_type

	//using namespace boost;
#endif

///////////////////////////////////////////////////////////////////// SHORTCUTS

///// types
#define		vint		std::vector<int>
#define		vuint		std::vector<unsigned int>
#define		vfloat		std::vector<float>
#define		vdouble		std::vector<double>
#define		dint		std::deque<int>
#define		duint		std::deque<unsigned int>
#define		dfloat		std::deque<float>
#define		ddouble		std::deque<double>
#define         S      		std::string
#define         vS     		std::vector<std::string>
#define         vstr   		std::vector<str>
#define         dS     		std::deque<std::string>
#define         dstr   		std::deque<str>

///// utils 
#define 	GL(x)		std::getline(cin,x)
#define		MT		std::make_tuple
#define		NL     		cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
#define 	ISI 		std::istream_iterator
#define 	OSI 		std::ostream_iterator
#define 	b		begin() 	
#define 	e		end() 	

///// boost
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

#ifdef  USE_BOOST
//typedef 	boost::regex_iterator		RI;
typedef 	boost::sregex_iterator          SRI;
typedef 	boost::cregex_iterator          CRI;		
		// usage:  echo 'aa bb' | scc 'WRL {SRI it(line.begin(), line.end(), R("\\w+")), e; while (it!=e) cout << *it++ << endl;}
//typedef 	boost::regex_token_iterator     RTI;		
typedef 	boost::sregex_token_iterator    SRTI;		
typedef 	boost::cregex_token_iterator    CRTI;		
#define 	MRTI		boost::make_regex_token_iterator 
#endif


///////////////////////////////////////////////////////////////////// LINE INPUT
//	http://www.parashift.com/c++-faq-lite/input-output.html#faq-15.2
//

	// counting locale -- http://stackoverflow.com/questions/2066126/counting-the-number-of-characters-that-are-output/2067723#2067723
	

///////////////////////////////////////////////////////////////////////////////////////////////////////////   gcc-4.6.0

#ifdef MODERN_GCC


// OSI -- Output Stream Iterator 
// 	shorthand for:	ostream_iterator<T>(cout, " ")
// 	used as:	copy(V.begin(), V.end(), osi<T>());
// 	also DTOR adds std::endl 

	template<typename T=int>
struct	osi : ostream_iterator<T> {
	osi(): ostream_iterator<T>(cout, " ") { self_addr = (void*) this; }; 
	void* self_addr;	// to check if we are original instance of osi
	~osi() { if (self_addr == (void*) this)   cout << endl; };	
};

/*
// ISI -- Output Stream Iterator shortcut
// 	used as:	vector<int> V (isi<int>(cin), isi<int>());
	template<typename T>
struct	isi : istream_iterator<T> {
	isi(istream& is):	istream_iterator<T>(is)	{}; 
	isi(): 			istream_iterator<T>()	{}; 
};
*/

	
///////////////////////////////////////////////////////////////////// UTILS

#ifdef USE_BOOST


	template <class T, class U>
	typename std::common_type<T, U>::type
min(T t, U u) {
   return t < u ? t : u;
}

	template <class T, class U>
	typename std::common_type<T, U>::type
max(T t, U u) {
   return t >= u ? t : u;
}

#endif

	

template <int N>
string&
operator+ (const char* s, int i)
{ return string(s) + str(i); }



///////////////////////////////////////////////////////////////////// PRINT ANY CONTAINER

// Print any C-array

		template<class T, std::size_t N> 		
		typename boost::disable_if<typename std::is_same<T, char>::type,  std::ostream&>::type
	operator<<      (ostream& os, const T (&A)[N]) {
		cout << "{";
			int i=0;
			for (; i<N-1;  i++)	os  << A[i] <<  ", ";
			os << A[i];
		cout << "}";
		return os;
	};



// print any std::sequance-containter<printable>
template<typename E, template<typename E, typename L> class L > std::ostream&                                              
operator<<      (ostream& os, const L<E, std::allocator<E> >& C) {              
	cout << "{";
		auto it=C.begin();
		for (int i=0;   i < int(C.size())-1;   i++, it++)	os  << *it <<  ", ";
		if (!C.empty())  					os  << *it;
	cout << "}";
        return os;
};


// SET -- print any std::set<printable>  with std comparator and allocator
template<typename K> inline std::ostream&                                              
operator<<      (ostream& os, const set<K, std::less<K>, std::allocator<K> >& C) {              
	cout << "{";
	auto it=C.begin();
        for (int i=0;   i < int(C.size())-1;   i++, it++)		os  << *it <<  ", ";
	if (!C.empty())  						os  << *it;
	cout << "}";
        return os;
};



// MAP -- print any std::map<printable, printable>  with std comparator and allocator
template<typename K, typename V> inline std::ostream&                                              
operator<<      (ostream& os, const map<K, V, std::less<K>, std::allocator<std::pair<const K,V> > > & C) {              
	cout << "{";
	auto it = C.begin();
        for (int i=0;   i < int(C.size())-1;   i++, it++)		os  << *it <<  ", ";
	if (!C.empty())  						os  << *it;
	cout << "}";
        return os;
};
	

// PAIR -- print any std::pair<printable1, printable2>

		template<typename T, typename U> inline std::ostream&  
operator<<      (ostream& os, const typename std::pair<T,U>& p) {               
	os << "⟨" << p.first << "," << p.second <<"⟩";
	return os;
};


	// Using C++0x Variadic Templates to Pretty-Print Types 
	// 	-- http://mlangc.wordpress.com/2010/04/18/using-c0x-variadic-templates-to-pretty-print-types/

///////////////////////////////////////////////////////////////////////////////  HELPER CLASSES


// STR
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
	str& operator += (int I) { ostringstream OS;   OS << *this + I;   this->string::assign(OS.str());  return *this; }
	str& operator -= (int I) { ostringstream OS;   OS << *this - I;   this->string::assign(OS.str());  return *this; }
	str& operator *= (int I) { ostringstream OS;   OS << *this * I;   this->string::assign(OS.str());  return *this; }
	str& operator /= (int I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }
	str& operator %= (int I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }

	str& operator  = (long I) { ostringstream OS;   OS <<         I;   this->string::assign(OS.str());  return *this; }
	str& operator += (long I) { ostringstream OS;   OS << *this + I;   this->string::assign(OS.str());  return *this; }
	str& operator -= (long I) { ostringstream OS;   OS << *this - I;   this->string::assign(OS.str());  return *this; }
	str& operator *= (long I) { ostringstream OS;   OS << *this * I;   this->string::assign(OS.str());  return *this; }
	str& operator /= (long I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }
	str& operator %= (long I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }

	str& operator  = (double I) { ostringstream OS;   OS <<         I;   this->string::assign(OS.str());  return *this; }
	str& operator += (double I) { ostringstream OS;   OS << *this + I;   this->string::assign(OS.str());  return *this; }
	str& operator -= (double I) { ostringstream OS;   OS << *this - I;   this->string::assign(OS.str());  return *this; }
	str& operator *= (double I) { ostringstream OS;   OS << *this * I;   this->string::assign(OS.str());  return *this; }
	str& operator /= (double I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }
	str& operator %= (double I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }

		template<class T>
	str& operator << (T t) { ostringstream OS;   OS << *this << t;  *this =  OS.str(); return *this; }

	operator const string&	(void) const 	{ return  *(string*)this; }	// converter to std::string&
	operator string&	(void) 		{ return  *(string*)this; }	// converter to std::string&
	operator bool		(void) const 	{ return   this->size() != 0; }	// converter to bool

	// converter to numerics
	explicit	operator int		(void) { istringstream IS;  int    I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator long		(void) { istringstream IS;  long   I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator unsigned int	(void) { istringstream IS;  unsigned int    I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator unsigned long	(void) { istringstream IS;  unsigned long    I;  IS.str(*this);  IS >> I;  return I; }
			operator double		(void) { istringstream IS;  double I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator float		(void) { istringstream IS;  double I;  IS.str(*this);  IS >> I;  return I; }

	////
	str  operator +  (const char* s) { return  *(string*)this +  string(s); }	

	// prefix/postfix inc/dec
	int operator++() {                   return *this = *this + 1; }
	int operator--() {                   return *this = *this - 1; }
	int operator++(int) { long old = long(*this); *this = *this + 1; return old; }
	int operator--(int) { long old = long(*this); *this = *this - 1; return old; }
	// TODO for double
};

std::ostream&   operator<<      (ostream& os, const str& s) { os << (string)s; return os; };

struct in_t {	 // used as:   int i(in);
	in_t () {};

	// input a POD type
	template<typename T> operator T() { T t; cin >> t; return t; }
};

in_t in;


/*
	template<class T> 
std::string& operator<<(std::string s, const T t) { 
	std::ostringstream ss; 
	ss << t;
	return s += ss.str(); 
}*/ 


// input any std::sequance-containter<printable>  (container must have size()) 
template<typename E, template<typename E, typename L> class L > std::istream&                                              
operator>>      (istream& is, L<E, std::allocator<E> >& C)    { for(auto &c:C) if(!(is>>c)) break; return is; }; 


// TUPLE -- print any std::tuple<printable ...>
// 	tr1::tuple() used to be printable, but now with gcc460 - it is not.
	using	std::tuple;
	using	std::tuple_size;
	using	std::get;



			template< int RI, typename... TT>
	struct	print_tuple_elem  {
		print_tuple_elem (ostream& os, const tuple<TT...>& tup)  {               
			const size_t  tsize = tuple_size<tuple<TT...>>::value;
			const size_t  i = tsize - RI;
			os <<  get<i>(tup);
			if  (i != tsize-1)   cout << ", ";
			print_tuple_elem<RI-1, TT...>(os, tup);
		};
	};

			template<typename... TT>
	struct	print_tuple_elem <0, TT...> {
		print_tuple_elem (ostream& os, const tuple<TT...>& tup)  {};
	};


		template<typename... TT> inline
		std::ostream&  
operator<<      (ostream& os, const tuple<TT...>& tup) {               
	const size_t  tsize = tuple_size<tuple<TT...>>::value;
	os << "⟨";     print_tuple_elem<tsize, TT...>(os, tup);    os << "⟩";
	return os;
};
#endif



#endif
