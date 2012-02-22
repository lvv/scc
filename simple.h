#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

//#if __GNUC__ < 4  ||  (__GNUC__ == 4 && (__GNUC_MINOR__ < 7 ) )
//	#error "SCC/simple.h does not support GCC earlier than 4.7"
//#endif

//#if	defined(__GXX_EXPERIMENTAL_CXX0X__) && (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 4 ) ) )
//	#define  MODERN_GCC	1
//#endif

#include "scc/stl.h"
#include "scc/io.h"
//#include "scc/regex.h"

//////////////////////////////////////////////////////////////////// C
//#include <cstdlib>
//#include <cstddef>
#include <cstring>
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




///////////////////////////////////////////////////////////////////////////////  INPUT

// IN   -- read cin when `in` value is accessed.
//   used as:	int i(in);

	// usage:   echo 1   | scc 'int N(in);  N'


struct in_t {
	in_t (): n(0) {};

		// set container size
		size_t n;
	in_t& operator() (long N) { n=N;  return *this; }


		template<typename T>		// primary
	operator T() {
		T x;
		input<T>(x); 
		n = 0;
		return x;
	};


		template<typename T>		// pod-like
		typename std::enable_if<
			//std::is_arithmetic<T>::value || is_string<T>::value,
			std::is_arithmetic<T>::value,
			void
		>::type
	input(T& x)	{ cin >> x; }

	// SEQ-CONT
		template<typename Ct>
		typename std::enable_if<is_container<Ct>::value  &&  has_push_back<Ct>::value,  void>::type
	input(Ct& C)	{
		typename Ct::value_type t;
		if (n>0) C.resize(n);
		if (!C.empty())		for (typename Ct::value_type&x : C)  { std::cin >> t;   if(!cin || n-- <= 0)  break;  x=t;}
		else			{ C.clear();  while  (std::cin >> t, cin)  C.push_back(t);}
	}

	// SET
		template<typename Ct>
		typename std::enable_if<is_container<Ct>::value  &&  has_insert<Ct>::value  &&  !has_mapped_type<Ct>::value,  void>::type
	input(Ct& C)	{
		typename Ct::value_type t;
		C.clear(); 
		n = n ? n : -1;
		while  (cin >> t,  cin && n--)   C.insert(t);
	}

	// MAP
		template<typename Ct>
		typename std::enable_if<is_container<Ct>::value  &&  has_insert<Ct>::value  &&  has_mapped_type<Ct>::value,  void>::type
	input(Ct& C)	{
		typename Ct::key_type	  k;
		typename Ct::mapped_type  m;
		C.clear(); 
		n = n ? n : -1;
		while(cin >> k >> m  && n--)  C[k] = m;
	}



	// C-ARRAY
		template<typename T, size_t N>
		void
	input(T(&A)[N])	{
		T t;
		for (size_t i=0;  i<N && n>0;  i++, n--)  { std::cin >> t;   if(cin.bad()) break;  A[i]=t;}
	}

};

static in_t in;


// SEQ-CONTAINER

		template<typename Ct>
		typename std::enable_if<is_container<Ct>::value  &&  has_push_back<Ct>::value, std::istream& >::type
operator>>      (istream& is, Ct& C)    {
	int n = C.size() ? C.size() : -1;
	C.clear(); 
	typename Ct::value_type c;
	while(is>>c && n--)  C.push_back(c);
	return is;
};

// C-ARRAY
		template<typename T, size_t N>
		std::istream&
operator>>      (istream& is, T(&A)[N])    {
	T t;
	for(size_t i=0;  i<N  &&  cin;  i++)  {
		if(!(is>>t)) break;
		A[i] = t;
	}
	return is;
};


// STD::ARRAY
		template<typename T, size_t N>
		std::istream&
operator>>      (istream& is, std::array<T,N>& A) {
	T t;
	for (size_t i=0;  i<N;  i++)  {
		is >> t; if (!is) break;
		A[i] = t;
	}
	return is;
};

// PAIR
		template<typename T, typename U>
		std::istream&
operator>>      (istream& is, std::pair<T,U>& p) {
	is >> p.first >>  p.second;
	return is;
};


// TUPLE

			template< int RI, typename... TT>
	struct	input_tuple_elem  {
		input_tuple_elem (istream& is, std::tuple<TT...>& tup)  {
			const size_t  tsize = std::tuple_size<std::tuple<TT...>>::value;
			const size_t  i = tsize - RI;
			is >>  std::get<i>(tup);
			input_tuple_elem<RI-1, TT...>(is, tup);
		};
	};

			template<typename... TT>
	struct	input_tuple_elem <0, TT...> {
		input_tuple_elem (istream& is, std::tuple<TT...>& tup)  {};
	};


		template<typename... TT>
		std::istream&
operator>>      (istream& is, std::tuple<TT...>& tup) {
	const size_t  tsize = std::tuple_size<std::tuple<TT...>>::value;
	input_tuple_elem<tsize, TT...>(is, tup);
	return is;
};


// SET
		template<typename Ct>
		typename std::enable_if<is_container<Ct>::value  &&  has_insert<Ct>::value && !has_mapped_type<Ct>::value, std::istream& >::type
operator>>      (istream& is, Ct& C)    {
	typename Ct::value_type c;
	while(is>>c)  C.insert(c);
	return is;
};


// MAP
		template<typename Ct>
		typename std::enable_if<is_container<Ct>::value  &&  has_insert<Ct>::value && has_mapped_type<Ct>::value, std::istream& >::type
operator>>      (istream& is, Ct& C)    {
	typename Ct::key_type	  k;
	typename Ct::mapped_type  m;
	while(is >> k >> m)  C[k] = m;
	return is;
};


#endif	// LVV_SIMPLE_H
