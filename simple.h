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

//////////////////////////////////////////////////////////////////// C

#include <cstdlib>
//#include <cstddef>


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
#endif

///////////////////////////////////////////////////////////////////// C++11 STL
#ifdef CXX11
#include <type_traits>
#include <tuple>
#include <memory>
#endif


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
	using	std::setw;
	using	std::dec;
	using	std::setprecision;

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
	#endif

	// iterator
	using	std::advance;
	using	std::distance;
	#ifdef CXX11
	using	std::begin;			// C++11
	using	std::end;			// C++11
	using	std::prev;			// C++11
	using	std::next;			// C++11

	// memory  (C++11)
	using	std::shared_ptr;
	using	std::unique_ptr;
	using	std::auto_ptr;
	using	std::weak_ptr;

	// function
	using	std::function;
	using	std::bind;
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

	#ifdef CXX11
	using	std::placeholders::_1;
	using	std::placeholders::_2;
	using	std::placeholders::_3;
	using	std::placeholders::_4;
	using	std::placeholders::_5;

	// meta
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
typedef		const	int			cint;
typedef		size_t				idx;
typedef		std::vector<int>		vint;
typedef		std::vector<unsigned int>	vuint;
typedef		std::vector<long>		vlong;
typedef		std::vector<unsigned long>	vulong;
typedef		std::vector<char>		vchar;
typedef		std::vector<float>		vfloat;
typedef		std::vector<double>		vdouble;

typedef		std::deque<int>			dint;
typedef		std::deque<int>			dlong;
typedef		std::deque<unsigned int>	duint;
typedef		std::deque<float>		dfloat;
typedef		std::deque<double>		ddouble;
typedef		std::deque<char>		dchar;

typedef		std::list<int>			lint;
typedef		std::list<unsigned int>		luint;
typedef		std::list<long>			llong;
typedef		std::list<unsigned long>	lulong;
typedef		std::list<char>			lchar;
typedef		std::list<float>		lfloat;
typedef		std::list<double>		ldouble;

typedef		std::string			str;
typedef		std::vector<std::string>	vstr;
typedef		std::deque<std::string>		dstr;
typedef		std::list<std::string>		lstr;

///// utils
#define		MT		std::make_tuple
#define		MP		std::make_pair

#define		GL(x)		std::getline(cin,x)
#define		NL		cin.ignore(numeric_limits<std::streamsize>::max(),'\n');


///////////////////////////////////////////////////////////////////// LOOPS


#define		FOR(i,i0,N)	for (long i = (i0), max_##i=(N);   i < max_##i;   i++)
#define		ROF(i,a,b)	for (long i = (b)-1; i >= long(a); i--)
#define		REP(N)		for (long i_REP_ue923u=0, N_REP_2uf23f=(N);   i_REP_ue923u< N_REP_2uf23f;   i_REP_ue923u++)

#define		iFOR(N)		FOR(i,0,N)
#define		jFOR(N)		FOR(j,0,N)
#define		kFOR(N)		FOR(k,0,N)
#define		tFOR(N)		FOR(t,0,N)
#define		nFOR(N)		FOR(m,0,N)
#define		mFOR(N)		FOR(m,0,N)

#define		ALL(IT, C)	for (auto IT=begin(C);  IT != end(C);   IT++)
#define		LLA(IT, C)	for (auto IT=end(C)-1;  IT >= begin(C);   IT--)
#define		itALL(C)	ALL(it,C)
#define		pALL(C)		ALL(p,C)
#define		qALL(C)		ALL(q,C)
#define		pLLA(C)		LLA(p,C)
#define		iALL(C)		for (long i=0;  i<(long)(end(C)-begin(C));   i++)
#define		jALL(C)		for (long j=0;  j<(long)(end(C)-begin(C));   j++)
#define		kALL(C)		for (long k=0;  k<(long)(end(C)-begin(C));   k++)
#define		lALL(C)		for (long l=0;  l<(long)(end(C)-begin(C));   l++)
#define		mALL(C)		for (long m=0;  m<(long)(end(C)-begin(C));   m++)
#define		nALL(C)		for (long n=0;  n<(long)(end(C)-begin(C));   n++)
#define		cALL(C)		for (auto c:C) if(c == '\0') break;  else
#define		xALL(C)		for (auto x:C)


#ifndef STO_H
	#undef 		_
	#define		_    std::cout<< 
	#undef 		__
	#define		__   std::cout<< 
#endif 


#endif	// SCC_SIMPLE_H
