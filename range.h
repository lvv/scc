
#ifndef  LVV_RANGE_H
#define  LVV_RANGE_H

/*
#include <stddef.h>
#include <iterator>
#include <string>
#include <cstring>
#include <deque>
#include <tuple>
*/

#include "scc/meta.h"

/////////////////////////////////////////////////////////////////////////////////////////  RANGE

	struct range_tag{};

	template<typename I>
struct  iterator_range {
		typedef		      I							iterator;
		typedef		const I							const_iterator;
		typedef		typename std::iterator_traits<I>::value_type		value_type;
		typedef		typename std::iterator_traits<I>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<I>::pointer		pointer ;
		typedef		typename std::iterator_traits<I>::reference		reference ;
	iterator b_, e_;

	// CTOR
	iterator_range()  : b_(0), e_(0) {};
	iterator_range(iterator b, iterator e)  : b_(b), e_(e) {};


	//template<typename Ct>
	//iterator_range( typename std::enable_if<std::is_same<I, typename Ct::iterator>::value, Ct>::type&  C)  : b_(begin(C)), e_(end(C)) {};

	iterator	begin()		{ return b_; };
	iterator	end()		{ return e_; };
	const_iterator	begin() const	{ return b_; };
	const_iterator	end()   const	{ return e_; };

	iterator_range& operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };


	/* to bool conversion --
	*/
	 
			struct PointerConversion { int valid; };
			typedef int PointerConversion::* datamemptr;

	operator datamemptr  () const {
		return  (b_ != e_) ? &PointerConversion::valid : 0;
	};

};



////////////////////////////////////////////////////////////////  OPERATOR, -- (it1, it2) ctor
	template<typename I>
	eIF<is_iterator<I>(), iterator_range<I>>
operator, (I b, I e)  { return iterator_range<I>(b,e); };

////////////////////////////////////////////////////////////////  RANGE() -- makes range

	template<typename I>
	eIF<is_iterator<I>(), iterator_range<I>>
range(I b, I e) { return iterator_range<I>(b,e); };


	template<typename Ct>
	eIF<is_container<Ct>(), iterator_range<cl_iterator<Ct>>>
range(Ct& C) { return iterator_range<cl_iterator<Ct>>(std::begin(C), std::end(C)); };

template<typename T   ,  size_t N> iterator_range<T   *> range(T    (&C)[N])  { return iterator_range<T   *>(std::begin(C), std::end(C)); };
template<                size_t N> iterator_range<char*> range(char (&C)[N])  { return iterator_range<char*>(std::begin(C), endz    (C)); };
template<                size_t N> iterator_range<const char*> range(const char (&C)[N])  { return iterator_range<const char*>(std::begin(C), endz    (C)); };

/*** we can either a pointer of an array
	iterator_range<const char*>
range(const char* p) { auto pp=p; while (*p) ++p; return iterator_range<const char*>(pp,p); };

	iterator_range<char*>
range(char* p) { auto pp=p; while (*p) ++p; return iterator_range<char*>(pp,p); };
*/

template<typename I>	struct  is_container_t <iterator_range<I>>	: std::true_type { };

static  __attribute__((unused)) struct range_converter_t {} rng;

/////////////////////////////////////////////////////////////////// RNG -- range proxy

	template<typename Ct>
	eIF<
		is_container<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>
operator | (Ct& C, range_converter_t r) { return range(std::begin(C), std::end(C)); };

	template<typename T, size_t N>
	iterator_range<T*>
operator | (T (&C)[N], range_converter_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Ct>
	eIF<
		is_container<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>
operator | (range_converter_t rng, Ct& C) { return range(std::begin(C), std::end(C)); };


/*
static  __attribute__((unused)) struct iot_t {} iot;

	template<typename Ct>
	typename std::enable_if<
		is_container<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>::type
operator | (Ct& C, iot_t r) { return range(std::begin(C), std::end(C)); };
*/

template<typename T>	struct  is_range		: std::false_type {};
template<typename T>	struct  is_range<iterator_range<T>>	: std::true_type  {};

////////////////////////////////////////////////////////////////  RANGE OPS


//  Ct1 | Ct2   ---  search() --> range	   
/*
	template<typename Ct>
	typename std::enable_if <is_container<Ct>(),  iterator_range&>::type
operator |       (Ct& C1, const Ct& C2)    { 
	auto it = search(C1.begin(), C1.end(), C2.begin(), C2.end());
	return  iterator_range(it, advance(it, distance(C2.end(), C2.begin())));
};

//  Ct1 / Ct2   ---  search() --> it
	template<typename Ct>
	typename std::enable_if <is_container<Ct>(),  typename Ct::iterator>::type
operator /       (Ct& C1, const Ct& C2)    {  return  search(C1.begin(), C1.end(), C2.begin(), C2.end()); };
*/


#endif	// LVV_STL_H
