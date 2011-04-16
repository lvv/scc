#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

//////////////////////////////////////////////////////////////////// C
//#include <cstdlib>
#include <cstddef>
//#include <cstdint>
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
#include <tuple>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <limits>

#include <bitset>
///////////////////////////////////////////////////////////////////// C++0X STL
#include <ratio>

// 4.6.0  fail with: scc 'RS("abc", R("abc"))'
//#include <regex>
//


///////////////////////////////////////////////////////////////////// BOOST
#ifdef USE_BOOST

	//#include <boost/algorithm/string.hpp>
	//	using boost::split;

	#include <boost/regex.hpp>
		using boost::regex;
		using boost::cmatch;
		using boost::regex_match;

	//using namespace boost;
#endif

///////////////////////////////////////////////////////////////////// shortcuts

#define 	R	regex
#define 	RM	regex_match
#define 	RS	regex_search
#define 	M	match
#define 	CM	cmatch

#define 	GL(x)	getline(cin,x)

#define		vint	vector<int>
#define		vuint	vector<unsigned int>
#define		vfloat	vector<float>
#define		vdouble	vector<double>
#define		vstr	vector<str>


///////////////////////////////////////////////////////////////////// LOCAL
//#include <lvv/lvv.h>
//#include <lvv/meta.h>
//#include <lvv/array.h>
//	using lvv::array;

//using namespace std;

// FOREACH
//#include <boost/foreach.hpp>
//#define         foreach         BOOST_FOREACH  
//#define reverse_foreach		BOOST_REVERSE_FOREACH



///////////////////////////////////////////////////////////////////// LINE INPUT
//	http://www.parashift.com/c++-faq-lite/input-output.html#faq-15.2
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
	using	std::map;
	using	std::stringstream;
	using	std::istringstream;
	using	std::ostringstream;
	using	std::numeric_limits;
	using	std::ostream_iterator;
	using	std::istream_iterator;

	static istringstream		lin_sstream;
	static char __attribute__((unused))	lin_line[1000];	

	
	#define		nlin   		( \
						cin.getline(lin_line,sizeof(lin_line)-1),  \
						lin_sstream.clear(),  \
						lin_sstream.str(lin_line),  \
						lin_sstream \
	)

	#define		lin  lin_sstream

	#define		NL      		cin.ignore(numeric_limits<std::streamsize>::max(),'\n'); _line_field = 1;
	#define		nl      		cin.ignore(numeric_limits<std::streamsize>::max(),'\n'); _line_field = 1; 


	#define		IS_SPACE                (cin.peek()==' '  || cin.peek()=='\t')
	#define		IS_EOL                  (cin.peek()=='\n' || cin.peek()=='\r')
	#define		IS_COMMA                (cin.peek()==',')
	#define		SKIP_SPACE              while ( IS_SPACE             )    cin.ignore(1);
	#define		SKIP_SPACE_N_COMMA      while ( IS_SPACE || IS_COMMA )    cin.ignore(1);

	size_t static 	 __attribute__((unused))	_line_field	= 1;

std::istream& 	xF(size_t n) {
	string ignore_word; 
	if (_line_field > n) NL;
	for (; _line_field<n; _line_field++)  {
		SKIP_SPACE;
		cin >> ignore_word;
	};
	return cin;
}

	// counting locale -- http://stackoverflow.com/questions/2066126/counting-the-number-of-characters-that-are-output/2067723#2067723
	


	/*  OBSOLETE:  use bitset
	 
	//////// integral to binary string 

			template<typename T> inline
	const string binstr (T v) {
		string binstr(sizeof(T)*8,'#') ;
		for (int i=0; i<sizeof(T)*8; i++) {
			binstr[sizeof(T)*8-1-i] = (v>>i) & 1 ? '1' : '0' ;
			//v = v / 2 ;
		}
		//return std::move(binstr) ;
		return binstr ;
	}

	template<typename T> struct list_t;
	*/

// OSI -- Output Stream Iterator 
// 	shorthand for:	ostream_iterator<T>(cout, " ")
// 	used as:	copy(V.begin(), V.end(), osi<T>());
// 	also DTOR adds '\n'

	template<typename T=int>
struct	osi : ostream_iterator<T> {
	osi(): ostream_iterator<T>(cout, " ") { self_addr = (void*) this; }; 
	void* self_addr;	// to check if we are original instance of osi
	~osi() { if (self_addr == (void*) this)   cout << endl; };	
};

// ISI -- Output Stream Iterator shorthand 
// 	used as:	vector<int> V (isi<int>(cin), isi<int>());
	template<typename T>
struct	isi : istream_iterator<T> {
	isi(istream& is):	istream_iterator<T>(is)	{}; 
	isi(): 			istream_iterator<T>()	{}; 
};

	
///////////////////////////////////////////////////////////////////// PRINT ANY CONTAINER

// print any C-array —  T[]
/*  does not work.  Impossible?
template<std::size_t N>
std::ostream&                                              
operator<<      (ostream& os, int A[N]) {              

        if (!A) return os;

	//os << *A;
	//for (size_t i=1;  i < sizeof(A)/sizeof(*A);  i++)  
        //        os <<  ", " << *(A+i);
        //os << "   size:" << sizeof(A)/sizeof(*A) <<"  ";
	os << *A;
	for (size_t i=1;  i < N;  i++)  
                os <<  ", " << *(A+i);

        os << "   size:" << N <<"  ";
        return os;
};
*/

// print any std::sequance-containter<printable>
template<typename E, template<typename E, typename L> class L > std::ostream&                                              
operator<<      (ostream& os, const L<E, std::allocator<E> >& C) {              
	cout << "{";
	auto it=C.begin();
        for (int i=0;   i < int(C.size())-1;   i++, it++)		os  << *it <<  ", ";
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

#if 	defined(__GXX_EXPERIMENTAL_CXX0X__) && (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 4 ) ) ) 

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


// STR
struct str: string {

	// CTOR
	str(const char*   s)	: string(s) {};
	str(const string& s)	: string(s) {};
	str()			: string()  {};

	// op= assign
	str& operator  = (int I) { ostringstream OS;   OS <<         I;   this->string::assign(OS.str());  return *this; }
	str& operator += (int I) { ostringstream OS;   OS << *this + I;   this->string::assign(OS.str());  return *this; }
	str& operator -= (int I) { ostringstream OS;   OS << *this - I;   this->string::assign(OS.str());  return *this; }
	str& operator *= (int I) { ostringstream OS;   OS << *this * I;   this->string::assign(OS.str());  return *this; }
	str& operator /= (int I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }
	str& operator %= (int I) { ostringstream OS;   OS << *this / I;   this->string::assign(OS.str());  return *this; }

	operator string	(void) { return  *(string*)this; }	// converter to std::string
	operator bool	(void) { return   this->size() != 0; }	// converter to bool

	operator int(void) {	// converter to int
		 istringstream IS;
		 int I;
		 IS.str(*this);
		 IS >> I;
		 return I;
	}

	// prefix/postfix inc/dec
	int operator++() {                   return *this = *this + 1; }
	int operator--() {                   return *this = *this - 1; }
	int operator++(int) { int old = int(*this); *this = *this + 1; return old; }
	int operator--(int) { int old = int(*this); *this = *this - 1; return old; }
};

struct in_t: istream {
	in_t() /*: istream()*/ {};

	//operator int() { int t; cin >> t; return t; }
	template<typename T>
	operator T() { T t; cin >> t; return t; }
};

in_t in;

#endif
