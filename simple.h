#ifndef  SCC_SIMPLE_H
#define  SCC_SIMPLE_H

#include "scc/stl.h"
#include "scc/range.h"
#include "scc/io.h"
#include "scc/regex.h"


// list af all C/C++ headers --- http://stackoverflow.com/questions/2027991/list-of-standard-header-files-in-c-and-c

//////////////////////////////////////////////////////////////////// C

#include <cstdlib>
//#include <cstddef>
#include <cstring>
extern "C"  void *memcpy(void *dest, const void *src, size_t n);

//#include <cctype>
#include <cmath>
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
#include <type_traits>
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
	using	std::setw;
	using	std::dec;
	using	std::setprecision;

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
	using	std::stack;
	using	std::queue;
	using	std::priority_queue;

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
	using	std::get;			// C++11
	using	std::make_tuple;		// C++11
	using	std::tuple_size;		// C++11
	using	std::make_shared;		// C++11
	using	std::iota;			// C++11

	// iterator
	using	std::begin;			// C++11
	using	std::end;			// C++11
	using	std::prev;			// C++11
	using	std::next;			// C++11
	using	std::advance;			//
	using	std::distance;			//

	// memory  (C++11)
	using	std::shared_ptr;
	using	std::unique_ptr;
	using	std::auto_ptr;
	using	std::weak_ptr;

	// function
	using	std::function;
	using	std::bind;
	using	std::less;
	using	std::greater;
	using	std::equal;
	using	std::placeholders::_1;
	using	std::placeholders::_2;
	using	std::placeholders::_3;
	using	std::placeholders::_4;
	using	std::placeholders::_5;

	// meta
	using	std::is_same;
	using	std::enable_if;


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



///////////////////////////////////////////////////////////////////////////////  HELPER CLASSES




#endif	// SCC_SIMPLE_H
