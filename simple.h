#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

#if 	defined(__GXX_EXPERIMENTAL_CXX0X__) && (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 4 ) ) ) 
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
///////////////////////////////////////////////////////////////////// C++0X STL
#ifdef  MODERN_GCC
#include <tuple>
//#include <slist>
#endif
//#include <type_traits>

///////////////////////////////////////////////////////////////////// BOOST
#ifndef NO_BOOST
#include <boost/utility.hpp>
	// enable_if
#include <boost/type_traits/is_same.hpp> 
	// is_same
#endif

///////////////////////////////////////////////////////////////////// 

	// io
	using	std::cin;
	using	std::cout;
	using	std::endl;
	using	std::string;
	using	std::basic_string;
	using	std::basic_ostream;
	using	std::istream;
	using	std::ostream;

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
	using	std::is_heap;
	using	std::make_heap;
	using	std::push_heap;
	using	std::pop_heap;
	using	std::sort_heap;

	// min/max
	//using	std::max;
	//using	std::min;
	using	std::max_element;
	using	std::min_element;
	using	std::lexicographical_compare;
	using	std::next_permutation;
	using	std::prev_permutation;

	// numeric
	using	std::accumulate;
	using	std::inner_product;
	using	std::adjacent_difference;
	using	std::partial_sum;


	// ????
	using	std::make_pair;
	using	std::make_tuple;
	using	std::tie;
	

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

// std::max(1, 2.2)  - compiler error

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



///////////////////////////////////////////////////////////////////// PRINT ANY CONTAINER

// Print any C-array

//#ifdef BOOST_VERSION
		template<class T, std::size_t N> 		// std::disable_if - does not exist yet	
		typename boost::disable_if<typename boost::is_same<T, char>::type,  std::ostream&>::type
	operator<<      (ostream& os, const T (&A)[N]) {
		cout << "{";
			int i=0;
			for (; i<N-1;  i++)	os  << A[i] <<  ", ";
			os << A[i];
		cout << "}";
		return os;
	};
//#endif



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


// TUPLE -- print any std::tuple<printable ...>
// 	tr1::tuple() used to be printable, but now with gcc460 - it is not.

#ifdef 	MODERN_GCC
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
	// Using C++0x Variadic Templates to Pretty-Print Types 
	// 	-- http://mlangc.wordpress.com/2010/04/18/using-c0x-variadic-templates-to-pretty-print-types/
	





///////////////////////////////////////////////////////////////////////////////  HELPER CLASSES

#ifdef 	MODERN_GCC
////// push_back/push_front replaement
//
// usage: 
//    scc 'vint V;  V << 1 << 2'
//    {1, 2}
//
//    scc 'dint V;  11 >> (22 >> V)'
//    {11}
//


	template<typename T, template<typename T, typename C> class C > 
	C <T,std::allocator<T>> &                                              
operator<<      (C<T, std::allocator<T> >& V, T x)    { V.push_back(x); return V; }; 

	template<typename T, template<typename T, typename C> class C > 
	C <T,std::allocator<T>> &                                              
operator>>      (T x, C<T, std::allocator<T> >& V)    { V.push_front(x); return V; }; 

////// vector = scallar
/* gcc:  operator=(C<T, std::allocator<_T1> >&, T)’ must be a nonstatic member function
	template<typename T, template<typename T, typename C> class C > 
	C <T,std::allocator<T>> &                                              
operator=      (C<T, std::allocator<T> >& V, T x)    { fill(V.begin(), V.end(), x); return V; }; 
*/

#endif

///////////////////////////////////////////////////////////////////////////////  INPUT

// IN   -- read cin when `in` value is accessed.
//   used as:    	int i(in);




struct  out_t { 
	template<typename T>	out_t&	operator<<  (T x)			{ cout <<         x;	return *this; };
	template<typename T>	out_t&	operator,   (T x)			{ cout <<         x;	return *this; };
	//template<typename T>	out_t&	operator|   (T x)			{ cout << " "  << x;	return *this; };
	template<typename T>	out_t&	operator^   (T x)			{ cout << " " << x;	return *this; };

	// endl, hex, ..
				out_t&  operator<<  (ostream& (*pf)(ostream&))	{ cout <<        pf;	return *this; };
				out_t&  operator<<  (std::ios& (*pf)(std::ios&)){ cout <<        pf;	return *this; };
				out_t&  operator<<  (std::ios_base& (*pf)(std::ios_base&)){ cout <<        pf;	return *this; };
				out_t&  operator,   (ostream& (*pf)(ostream&))	{ cout <<        pf;	return *this; };
				out_t&  operator,   (std::ios& (*pf)(std::ios&)){ cout <<        pf;	return *this; };
				out_t&  operator,   (std::ios_base& (*pf)(std::ios_base&)){ cout <<        pf;	return *this; };
};

struct  outln_t : out_t  { ~outln_t() { cout << endl; } };

std::ostream&    operator<<      (ostream& os, out_t out) {return os; };    // I allway forget to put semicolon  in:   scc '_ 1;'


#define		_    out_t()   << 
#define		__   outln_t() << 

struct in_t {	 
	in_t (): n(0) {};

	// input a POD type
	// usage:   echo 1   | scc 'int N(in);  N'
	template<typename T> operator T() { T t; cin >> t; return t; }


	// input  any std::sequance-containter<inputable>
	// usage:   echo a b c  | scc 'list<char> C = in(3); C'
	size_t n;
	in_t& operator() (long N) { n=N;  return *this; }

		template<typename T, template<typename T, typename C> class C >
	operator C<T,std::allocator<T> >()        {
		C<T,std::allocator<T> > c(n);  
		c.resize(0);
		cin >> c;  
		return c;
	}

	/*  STD::SET  - does not work
		template<typename T>
	operator std::set<T,std::allocator<T> >()        {
		std::set<T,std::allocator<T> > S;  
		T elem;
		while(n-- && cin) { cin >> elem;  S.insert(elem); } ;  
		return S;
	}
	*/
};

in_t in;



// Input any std::sequance-containter<printable> 
// Container must have non-zero size()
// Used as:   vector<int> V(3);   cin >> V;

	#ifdef 	MODERN_GCC
	template<typename T, template<typename T, typename Ct=std::allocator<T> > class Ct >
	std::istream&                                              
operator>>      (istream& is, Ct<T>& C)    {
	for(typename Ct<T>::iterator it=C.begin();  it!=C.end();  it++)
		if(!(is>>*it)) break;
	return is;
}; 
	#endif



#endif	// MODERN_GCC



#endif	// LVV_SIMPLE_H
