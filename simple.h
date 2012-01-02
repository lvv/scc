#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

#if __GNUC__ < 4  ||  (__GNUC__ == 4 && (__GNUC_MINOR__ < 7 ) )
	#error "SCC/simple.h does not support GCC earlier than 4.7"
#endif

//#if	defined(__GXX_EXPERIMENTAL_CXX0X__) && (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 4 ) ) )
//	#define  MODERN_GCC	1
//#endif

#include <print.h>

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
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <utility>
#include <vector>
#include <array>
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
	using	std::flush;
	using	std::dec;

	// containers
	using	std::vector;
	using	std::array;
	using	std::deque;
	using	std::set;
	using	std::unordered_set;
	using	std::unordered_multiset;
	using	std::list;
	using	std::multiset;
	using	std::map;
	using	std::unordered_map;
	using	std::unordered_multimap;
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
	using	std::count;
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
	using	std::copy_if;		//C++11
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
	using	std::tuple;			// C++11
	using	std::make_tuple;		// C++11
	using	std::iota;			// C++11
	using	std::begin;			// C++11
	using	std::end;			// C++11

	// memory  (C++11)
	using	std::shared_ptr;
	using	std::unique_ptr;
	using	std::auto_ptr;
	using	std::weak_ptr;


///////////////////////////////////////////////////////////////////// LINE INPUT
//	http://www.parashift.com/c++-faq-lite/input-output.html#faq-15.2
//
	// counting locale -- http://stackoverflow.com/questions/2066126/counting-the-number-of-characters-that-are-output/2067723#2067723


///////////////////////////////////////////////////////////////////// UTILS


// Greatest Common divisor
int gcd(long a, long b) {
	if (b==0)	return a;
	else		return gcd(b,a%b);
}

#define countof(array) (sizeof (array) / sizeof(array[0]))



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
//   used as:	int i(in);


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



	#define		R		std::regex
	//R		operator "" r(const char * s, size_t n) {return R(s);};
	#define		FMT		std::format

	#define		RM		std::regex_match
	#define		RS		std::regex_search
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



#endif	// LVV_SIMPLE_H
