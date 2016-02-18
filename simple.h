#ifndef  SCC_SIMPLE_H
#define  SCC_SIMPLE_H


// list af all C/C++ headers --- http://stackoverflow.com/questions/2027991/list-of-standard-header-files-in-c-and-c

// GCC
#if  defined(__GXX_EXPERIMENTAL_CXX0X__) 
	#define CXX11
#endif

// CLANG
#if  defined(__clang__)  
	#if __has_feature(cxx_decltype)
		#define CXX11
	#endif
#endif

// MSVC (not tested)
#if  defined(_MSC_VER)  &&  _MSC_VER >= 1600
	#define CXX11
#endif

//////////////////////////////////////////////////////////////////// NUMERIC CONSTANTS
const double e      = 2.7182818284590452354;
const double pi     = 3.14159265358979323846;


//////////////////////////////////////////////////////////////////// LVV

/*
namespace lvv {

	template <class T>                T max(T value)                { return value; }
	template <class T, class... Args> T max(T first, Args... rest)  { return std::max(first, lvv::max(rest...)); }

	template <class T>                T min(T value)                { return value; }
	template <class T, class... Args> T min(T first, Args... rest)  { return std::min(first, lvv::min(rest...)); }
};*/

#include "scc/loops_macro.h"
//////////////////////////////////////////////////////////////////// C

//#include <cstdlib>		// inject info global namespace: div, ...

	// from cstdlib
	/*
	int		rand(void);
	long		random(void);
	double		drand48(void);
	char*		getenv(const char *);
	void		exit(int);
	double		atof(const char *);
	int		atoi(const char *);
	long		atol(const char *);
	long long	atoll(const char *);
	*/
//#include <cstddef>
#include <limits.h>
#include <wchar.h>
#include <wctype.h>


#include <cstring>
extern "C"  void *memcpy(void *dest, const void *src, size_t n);

#include <cmath>
	//using	std::abs;
	using	std::floor;
	using	std::ceil;
	using	std::signbit;
	#ifdef CXX11
	using	std::trunc;
	using	std::round;
	#endif

#include <cassert>




///////////////////////////////////////////////////////////////////// C++ IO
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>


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

#ifdef CXX11
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <forward_list>
#include <chrono>
#endif

///////////////////////////////////////////////////////////////////// C++11 STL
#ifdef CXX11
	#include <type_traits>
	#include <tuple>
	#include <memory>
	#include <functional>
#endif

#ifdef scc_BOOST_BIND
	#include <boost/bind.hpp>
#endif

#ifdef scc_BOOST_LAMBDA
	#include <boost/lambda/lambda.hpp>
#endif


/////////////////////////////////////////////////////////////////////

	// io
	using	std::cin;
	using	std::basic_ostream;
	using	std::istream;
	using	std::ostream;
	using	std::fstream;

	using	std::cout;
	using	std::cerr;
	using	std::endl;
	using	std::hex;
	using	std::flush;
	using	std::setw;
	using	std::dec;
	using	std::setprecision;

	using	std::wcout;
	using	std::wcin;

	// strings
	using	std::string;
	using	std::wstring;
	using	std::basic_string;
	#ifdef CXX11
	using	std::to_string;
	#endif

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
	using	std::stack;
	using	std::queue;
	using	std::priority_queue;
	#ifdef CXX11
	using	std::array;
	using	std::unordered_set;
	using	std::unordered_multiset;
	using	std::forward_list;
	using	std::unordered_map;
	using	std::unordered_multimap;
	#endif

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
	#ifdef CXX11
	using	std::copy_if;		//C++11
	#endif
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
	#ifdef CXX11
		using	std::is_heap;			// C++11
	#endif
	using	std::make_heap;
	using	std::push_heap;
	using	std::pop_heap;
	using	std::sort_heap;

	// min/max
	using	std::max;
	using	std::min;
	#ifdef CXX11
		using	std::max_element;
		using	std::min_element;
		using	std::minmax;			// C++11
		using	std::minmax_element;		// C++11
	#endif
	using	std::lexicographical_compare;
	using	std::next_permutation;
	using	std::prev_permutation;

	// numeric
	using	std::accumulate;
	using	std::inner_product;
	using	std::adjacent_difference;
	using	std::partial_sum;


	// utils
	using	std::pair;
	using	std::make_pair;
	#ifdef CXX11
		using	std::get;			// C++11
		using	std::tie;			// C++11
		using	std::tuple;			// C++11
		using	std::make_tuple;		// C++11
		using	std::tuple_size;		// C++11
		using	std::make_shared;		// C++11
		using	std::iota;			// C++11
		using   namespace std::chrono;
	#endif

	// iterator
	using	std::advance;
	using	std::distance;


	#ifdef CXX11
		using	std::begin;			// C++11
		using	std::end;			// C++11
		using	std::prev;			// C++11
		using	std::next;			// C++11
		using	std::move_iterator;    		// C++11

		// memory  (C++11)
		using	std::shared_ptr;
		using	std::unique_ptr;
		using	std::auto_ptr;
		using	std::weak_ptr;

		// function
		using	std::function;
	#endif


	#ifdef scc_BOOST_LAMBDA
		using	namespace boost::lambda;
	#endif


	#ifdef scc_BOOST_BIND
		using	boost::bind;
	#else
		#ifdef CXX11
		using	std::bind;
		#endif
	#endif

	using	std::plus;
	using	std::minus;
	using	std::multiplies;
	using	std::divides;
	using	std::modulus;
	using	std::negate;

	using	std::less;
	using	std::greater;
	using	std::equal;
	using	std::equal_to;
	using	std::not_equal_to;
	using	std::greater_equal;
	using	std::less_equal;

	using	std::bit_and;
	using	std::bit_or;
	using	std::bit_xor;

	using	std::logical_and;
	using	std::logical_or;
	using	std::logical_not;

	using	std::unary_negate;
	using	std::binary_negate;

	using	std::not1;
	using	std::not2;

	#if   defined(scc_BOOST_BIND)  ||  defined(scc_BOOST_LAMBDA)
		// already in global namaspace
	#else
		#if   !defined(scc_RO) && defined(CXX11)
		using	std::placeholders::_1;
		using	std::placeholders::_2;
		using	std::placeholders::_3;
		using	std::placeholders::_4;
		using	std::placeholders::_5;
		#endif
	#endif

	// meta
	#ifdef CXX11
	using	std::is_placeholder;
	using	std::is_same;
	using	std::is_base_of;
	using	std::enable_if;
	using	std::declval;
	#endif

	using	std::input_iterator_tag;
	using	std::output_iterator_tag;
	using	std::forward_iterator_tag;
	using	std::bidirectional_iterator_tag;
	using	std::random_access_iterator_tag;


///////////////////////////////////////////////////////////////////// SHORTCUTS

///// types
typedef		double		dbl;

///// Linux Kernel types
typedef		uint8_t		u8;
typedef		uint16_t	u16;
typedef		uint32_t	u32;

typedef		int8_t		i8;
typedef		int16_t		i16;
typedef		int32_t		i32;


///// STL containers types
typedef		std::vector<int>		vint;
typedef		std::vector<vint>		vvint;
typedef		std::vector<unsigned int>	vuint;
typedef		std::vector<long>		vlong;
typedef		std::vector<unsigned long>	vulong;
typedef		std::vector<char>		vchar;
typedef		std::vector<float>		vfloat;
typedef		std::vector<double>		vdouble;
typedef		std::vector<double>		vdbl;
typedef		std::vector<vdouble>		vvdbl;

typedef		std::deque<int>			dint;
typedef		std::deque<int>			dlong;
typedef		std::deque<unsigned int>	duint;
typedef		std::deque<float>		dfloat;
typedef		std::deque<double>		ddouble;
typedef		std::deque<double>		ddbl;
typedef		std::deque<char>		dchar;

typedef		std::list<int>			lint;
typedef		std::list<unsigned int>		luint;
typedef		std::list<long>			llong;
typedef		std::list<unsigned long>	lulong;
typedef		std::list<char>			lchar;
typedef		std::list<float>		lfloat;
typedef		std::list<double>		ldouble;
typedef		std::list<double>		ldbl;

typedef		std::string			str;
typedef		std::vector<std::string>	vstr;
typedef		std::deque<std::string>		dstr;
typedef		std::list<std::string>		lstr;

typedef		std::set<int>			sint;
typedef		std::set<long>			slong;
//typedef		std::set<char>			schar;		// conflict with OpenCV

typedef		std::multiset<int>	       	msint;
typedef		std::multiset<long>	       	mslong;
typedef		std::multiset<char>	       	mschar;


///// utils
#define		MT		std::make_tuple
//#define		MP		std::make_pair		// conflicts with OpenCV

#define		GL(x)		std::getline(cin,x)
#define		NL		cin.ignore(numeric_limits<std::streamsize>::max(),'\n');




#ifdef RO_H
	using namespace ro;
#else
	#undef 		_
	#define		_    std::cout<< 
	#undef 		__
	#define		__   std::cout<< 
#endif 


#endif	// SCC_SIMPLE_H
