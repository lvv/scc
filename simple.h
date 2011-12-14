#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

#if __GNUC__ < 4  ||  (__GNUC__ == 4 && (__GNUC_MINOR__ < 7 ) )
#error "error: SCC/simple.h does not support GCC earlier than 4.7"
#endif

//#if 	defined(__GXX_EXPERIMENTAL_CXX0X__) && (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 4 ) ) ) 
//	#define  MODERN_GCC	1
//#endif

//////////////////////////////////////////////////////////////////// C
//#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cctype>
#include <cmath>
//#include <tgmath.h>

///////////////////////////////////////////////////////////////////// C++ IO
#include <iostream>
#include <iomanip>
#include <sstream> 

///////////////////////////////////////////////////////////////////// C++ STL
#include <algorithm>
#include <numeric>
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
///////////////////////////////////////////////////////////////////// C++11 STL
#include <tuple>
#include <memory>


///////////////////////////////////////////////////////////////////// 

	// io
	using	std::cin;
	using	std::cout;
	using	std::cerr;
	using	std::endl;
	using	std::string;
	using	std::basic_string;
	using	std::basic_ostream;
	using	std::istream;
	using	std::ostream;
	using	std::hex;
	using	std::dec;

	// containers
	using	std::vector;
	using	std::deque;
	using	std::set;
	using	std::list;
	using	std::multiset;
	using	std::map;
	using	std::multimap;
	using	std::stringstream;
	using	std::istringstream;
	using	std::ostringstream;
	using	std::numeric_limits;
	using	std::ostream_iterator;
	using	std::istream_iterator;
	using	std::bitset;

	// algo
	using	std::swap;
	using	std::generate;
	using	std::generate_n;

	// Non-modifying
	using	std::for_each;
	using 	std::count;
	using	std::count_if;
	using	std::mismatch;
	using	std::equal;
	using	std::find;
	using	std::find_if;
	using	std::find_end;
	using	std::find_first_of;
	using	std::adjacent_find;
	using	std::search;
	using	std::search_n;

	// modifying 
	using	std::copy;
	using	std::copy_backward;
	using	std::fill;
	using	std::fill_n;
	using	std::transform;
	using	std::generate;
	using	std::generate_n;
	using	std::remove;
	using	std::remove_if;
	using	std::remove_copy;
	using	std::remove_copy_if;
	using	std::replace;
	using	std::replace_if;
	using	std::replace_copy;
	using	std::replace_copy_if;
	using	std::swap;
	using	std::swap_ranges;
	using	std::iter_swap;
	using	std::partition;
	using	std::stable_partition;
	using	std::reverse;
	using	std::reverse_copy;
	using	std::rotate;
	using	std::rotate_copy;
	using	std::random_shuffle;
	using	std::unique;
	using	std::unique_copy;

	// sort
	using	std::sort;
	using	std::partial_sort;
	using	std::partial_sort_copy;
	using	std::stable_sort;
	using	std::nth_element;

	// binary search
	using	std::lower_bound;
	using	std::upper_bound;
	using	std::binary_search;
	using	std::equal_range;


	// set
	using	std::merge;
	using	std::inplace_merge;
	using	std::includes;
	using	std::set_difference;
	using	std::set_intersection;
	using	std::set_symmetric_difference;
	using	std::set_union;


	// heap
	using	std::is_heap;			// C++11
	using	std::make_heap;
	using	std::push_heap;
	using	std::pop_heap;
	using	std::sort_heap;

	// min/max
	using	std::max;
	using	std::min;
	using	std::max_element;
	using	std::min_element;
	using	std::minmax;			// C++11
	using	std::minmax_element;		// C++11
	using	std::lexicographical_compare;
	using	std::next_permutation;
	using	std::prev_permutation;

	// numeric
	using	std::accumulate;
	using	std::inner_product;
	using	std::adjacent_difference;
	using	std::partial_sum;


	// ????
	using	std::pair;
	using	std::make_pair;
	using	std::tie;			// C++11
	using	std::make_tuple;		// C++11
	using	std::iota;			// C++11
	
	// memory  (C++11)
	using	std::shared_ptr;
	using	std::unique_ptr;
	using	std::auto_ptr;
	using	std::weak_ptr;
	

///////////////////////////////////////////////////////////////////// LINE INPUT
//	http://www.parashift.com/c++-faq-lite/input-output.html#faq-15.2
//

	// counting locale -- http://stackoverflow.com/questions/2066126/counting-the-number-of-characters-that-are-output/2067723#2067723
	

///////////////////////////////////////////////////////////////////////////////////////////////////////////   



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

// OUTI -- Output Stream Iterator
// 	shorthand for:	ostream_iterator<T>(cout, " ")
// 	used as:	copy(V.begin(), V.end(), outi);


	struct	outi_any_t {
		// CTOR
		template<typename T>			outi_any_t(const T& v)		{ cout << v; };
		template<typename T>			outi_any_t(T&& v)		{ cout << v; };
		// OP=
		template<typename T>	outi_any_t&	operator=(const T& v)		{ cout << v;  return *this; };
		template<typename T>	outi_any_t&	operator=(T&& v)		{ cout << v;  return *this; };
	};

	ostream& operator<< (ostream& os, const outi_any_t& s) { return os; }; // NOP to make outi_any_t accapable for ostream<<

struct	outi_t  : ostream_iterator<outi_any_t> {
	outi_t(): ostream_iterator<outi_any_t> (cout, " ") {};
};

static outi_t outi;




	
///////////////////////////////////////////////////////////////////// UTILS

// std::max(1, 2.2)  - compiler error
template <class T, class U>	typename std::common_type<T, U>::type	min(T t, U u) { return t <  u ? t : u; }
template <class T, class U>	typename std::common_type<T, U>::type	max(T t, U u) { return t >= u ? t : u; }

// Even / Odd
template <typename  T>  bool  is_even(T x) { return  !(x % 2); }
template <typename  T>	bool  is_odd (T x) { return    x % 2;  }


// Greatest Common divisor
int gcd(long a, long b) {
	if (b==0)	return a;
	else		return gcd(b,a%b);
}

#define countof(array) (sizeof (array) / sizeof(array[0]))

// 11x does not have disable_if
template <typename COND, typename T = void> 	struct disable_if                     { typedef T type; };
template <typename T> 				struct disable_if<std::true_type,T>   {};

////////////////////////////////////////////////////////////////////  OUT, OUTLN


struct  out { 
	bool  first_use;
	const char*	sep;
	const char*	paren;

	out ()					      : first_use(true), sep(0),   paren(0)     {init();};
	out (const char* sep, const char* paren=0) : first_use(true), sep(sep), paren(paren) {init();};
	void init() { if (sep   && !strlen(sep))	sep   = 0; }


	void send_sep() { if (sep && !first_use) cout << sep;  first_use = false; };

	template<typename T>	out&  operator<<  (T x)	{ send_sep();  cout <<         x;	return *this; };
	template<typename T>	out&  operator,   (T x)	{ send_sep();  cout <<         x;	return *this; };
	//template<typename T>	out&  operator|   (T x)	{ send_sep();  cout << " "  << x;	return *this; };
	template<typename T>	out&  operator^   (T x)	{ send_sep();  cout << " " << x;	return *this; };

	// endl, hex, ..
				out&  operator<< (std::ostream&  (*pf) (std::ostream& ) ) { cout << pf;  return *this; };
				out&  operator<< (std::ios&      (*pf) (std::ios&     ) ) { cout << pf;  return *this; };
				out&  operator<< (std::ios_base& (*pf) (std::ios_base&) ) { cout << pf;  return *this; };
				out&  operator,  (std::ostream&  (*pf) (std::ostream& ) ) { cout << pf;  return *this; };
				out&  operator,  (std::ios&      (*pf) (std::ios&     ) ) { cout << pf;  return *this; };
				out&  operator,  (std::ios_base& (*pf) (std::ios_base&) ) { cout << pf;  return *this; };

	// sequance container
	
		template<typename T, template<typename TT> class  Al, template<typename T, typename Al> class Ct >
		out& 
	operator<<      (const Ct<const T, Al<const T> >& C) {              
		if (paren)  	{if(strlen(paren)) cout << paren[0];}
		else 		cout << '{';
		//cout << (paren ? paren[0] : '{');

		for (int i=0;   i < int(C.size());   i++)	{if(i && C.size()) cout  << (sep ? sep : ", ");  cout << C[i];}

		if (paren)  	{if(strlen(paren)) cout << paren[1];}
		else 		cout << '}';
		//cout << (paren ? paren[1] : '}');
		return *this; 
	};


			template<class T, std::size_t N>                
		typename disable_if<typename std::is_same<T, char>::type,  out&>::type
	operator<<      (const T (&A)[N]) {
		cout << "{";
			int i=0;
			for (; i<(int)N-1;  i++)	cout << A[i] <<  ", ";
			cout << A[i];
		cout << "}";
		return *this;
	};



		template<typename T, template<typename TT> class  Al, template<typename T, typename Al> class Ct >
		out& 
	operator,       (const Ct<T, Al<T> >& C) {  return operator<<(C); }

	operator bool   () {  return true; }
 };

struct  outln : out  {
	outln(const char* sep=0, const char* paren=0)	:out(sep, paren)	{};
	~outln()				{ cout << endl; }
 };

#define		_    out()   << 
#define		__   outln() << 


std::ostream&    operator<<      (ostream& os, out out) {return os; };    // NOP



///////////////////////////////////////////////////////////////////// PRINT ANY CONTAINER

// Print any C-array

               template<class T, std::size_t N>                
                                                               // disable C-array print for  char[]
               typename disable_if<typename std::is_same<T, char>::type,  std::ostream&>::type
	operator<<      (ostream& os, const T (&A)[N]) {
		cout << "{";
			int i=0;
			for (; i<(int)N-1;  i++)	os << A[i] <<  ", ";
			os << A[i];
		cout << "}";
		return os;
	};


// print any std::sequance-containter<printable>
	template<typename T, template<typename T, typename Al> class Ct >
	std::ostream&                                              
operator<<      (ostream& os, const Ct<T, std::allocator<T> >& C) {              
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
	// Using C++0x Variadic Templates to Pretty-Print Types 
	// 	-- http://mlangc.wordpress.com/2010/04/18/using-c0x-variadic-templates-to-pretty-print-types/
	





///////////////////////////////////////////////////////////////////////////////  HELPER CLASSES


////// push_back/push_front replaement
//
// usage: 
//    scc 'vint V;  V << 1 << 2'
//    {1, 2}
//
//    scc 'dint V;  11 >> (22 >> V)'
//    {11}
//

	template<typename T, template<typename T, typename Ct> class Ct > 
	Ct <T,std::allocator<T>> &                                              
operator<<      (Ct<T, std::allocator<T> >& C, T x)    { C.push_back(x); return C; }; 

	template<typename T, template<typename T, typename Ct> class Ct > 
	Ct <T,std::allocator<T>> &                                              
operator>>      (T x, Ct<T, std::allocator<T> >& C)    { C.push_front(x); return C; }; 

// operator-=  -- remove member from container
	template<typename T, template<typename T, typename Ct> class Ct > 
	Ct <T,std::allocator<T>> &                                              
operator-=      (Ct<T, std::allocator<T> >& C, T x )    { C.erase(remove(C.begin(), C.end(), x), C.end()); return C; }; 


///////////////////////////////////////////////////////////////////////////////  INPUT

// IN   -- read cin when `in` value is accessed.
//   used as:    	int i(in);




struct in_t {	 
	in_t (): n(0) {};

	// input a POD type
	// usage:   echo 1   | scc 'int N(in);  N'
	template<typename T>	operator T()		{ T t;   cin >> t;   return t; }


	// input  any std::sequance-containter<inputable>
	// usage:   echo a b c  | scc 'list<char> C = in(3); C'

		size_t n;
		in_t& operator() (long N) { n=N;  return *this; }

		template<typename T, template<typename T, typename C> class C >
	operator C<T,std::allocator<T> >()        {
		C<T,std::allocator<T> > c(n);  
		cin >> c;  
		return c;
	}


	/*  STD::SET  - does not work
		template<typename T>
	operator std::set<T,std::allocator<T> >()        {
		std::set<T,std::allocator<T> > str;  
		T elem;
		while(n-- && cin) { cin >> elem;  str.insert(elem); } ;  
		return str;
	}
	*/
};

in_t in;



// Input any std::sequance-containter<printable> 
// Container must have non-zero size()
// Used as:   vector<int> V(3);   cin >> V;

	template<typename T, template<typename T, typename Ct=std::allocator<T> > class Ct >
	std::istream&                                              
operator>>      (istream& is, Ct<T>& C)    {
	if (C.size() > 0)  {
		for(typename Ct<T>::iterator it=C.begin();  it!=C.end();  it++)
			if(!(is>>*it)) break;
	}  else  {
		T c;   while(is>>c)  C.push_back(c);
	}
	return is;
}; 




///////////////////////////////////////////////////////////////////// REGEX

//#include <boost/regex.hpp> 	
#include <regex> 	 // C++11;   std::regex - 4.7.0  fail with: scc 'RS("abc", R("abc"))'
	using std::regex;
	using std::cmatch;
	using std::regex_match;
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



	#define 	R		std::regex
	//R 	operator "" r(const char * s, size_t n) {return R(s);};
	#define		FMT 		std::format

	#define 	RM		std::regex_match
	#define 	RS		std::regex_search
	#define 	RR		std::regex_replace
		// usage: scc 'str s="aa bb"; RR(s, R("(\\w+)"),"*\\1*")'
	
	//#define 	M		std::match
	#define 	CM		std::cmatch
	#define 	SM		std::smatch

	//typedef 	std::regex_iterator		RI;
	typedef 	std::sregex_iterator          SRI;
	typedef 	std::cregex_iterator          CRI;		
		// usage:  echo 'aa bb' | scc 'WRL {SRI it(line.begin(), line.end(), R("\\w+")), e; while (it!=e) cout << *it++ << endl;}
	//typedef 	std::regex_token_iterator     RTI;		
	typedef 	std::sregex_token_iterator    SRTI;		
	typedef 	std::cregex_token_iterator    CRTI;		
	#define 	MRTI		std::make_regex_token_iterator 


///////////////////////////////////////////////////////////////////// SORTCUTS
typedef		std::vector<std::string>	vstr;
typedef		std::deque<std::string>		dstr;


#endif	// LVV_SIMPLE_H
