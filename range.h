
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

	template<typename I>
struct  range_t {
		typedef		      I							iterator;
		typedef		const I							const_iterator;
		typedef		typename std::iterator_traits<I>::value_type		value_type;
		typedef		typename std::iterator_traits<I>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<I>::pointer		pointer ;
		typedef		typename std::iterator_traits<I>::reference		reference ;
	iterator b_, e_;

	// CTOR
	range_t()  : b_(0), e_(0) {};
	range_t(iterator b, iterator e)  : b_(b), e_(e) {};


	//template<typename Ct>
	//range_t( typename std::enable_if<std::is_same<I, typename Ct::iterator>::value, Ct>::type&  C)  : b_(begin(C)), e_(end(C)) {};

	iterator	begin()		{ return b_; };
	iterator	end()		{ return e_; };
	const_iterator	begin() const	{ return b_; };
	const_iterator	end()   const	{ return e_; };

	range_t& operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };


	/* to bool conversion --
	*/
	 
			struct PointerConversion { int valid; };
			typedef int PointerConversion::* datamemptr;

	operator datamemptr  () const {
		return  (b_ != e_) ? &PointerConversion::valid : 0;
	};

};

/*
	template<>
struct  range_t<char*> {

		typedef		char*							I;

		typedef		I							iterator;
		typedef		I							const_iterator;
		typedef		typename std::iterator_traits<I>::value_type		value_type;
		typedef		typename std::iterator_traits<I>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<I>::pointer		pointer ;
		typedef		typename std::iterator_traits<I>::reference		reference ;

	iterator b_, e_;
	range_t(iterator b, iterator e)  : b_(b), e_(e) {};

	range_t(      char* p)  : b_(p) { while(*p) p++;  e_=p;};

	iterator	begin()		{ return b_; };
	iterator	end()		{ return e_; };
	const_iterator	begin() const	{ return b_; };
	const_iterator	end()   const	{ return e_; };

	ssize_t		size()   const	{ return std::distance(b_, e_); };

	//range_t& operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };
};
*/


////////////////////////////////////////////////////////////////  OPERATOR, -- (it1, it2) ctor
	template<typename I>
	eIF<is_iterator<I>::value, range_t<I>>
operator, (I b, I e)  { return range_t<I>(b,e); };

////////////////////////////////////////////////////////////////  RANGE() -- makes range

	template<typename I>
	typename std::enable_if<is_iterator<I>::value, range_t<I>>::type
range(I b, I e) { return range_t<I>(b,e); };


	template<typename Ct>
	eIF<is_container<Ct>::value, range_t<cl_iterator<Ct>>>
range(Ct& C) { return range_t<cl_iterator<Ct>>(std::begin(C), std::end(C)); };

template<typename T   ,  size_t N> range_t<T   *> range(T    (&C)[N])  { return range_t<T   *>(std::begin(C), std::end(C)); };
template<                size_t N> range_t<char*> range(char (&C)[N])  { return range_t<char*>(std::begin(C), endz    (C)); };
template<                size_t N> range_t<const char*> range(const char (&C)[N])  { return range_t<const char*>(std::begin(C), endz    (C)); };

/*** we can either a pointer of an array
	range_t<const char*>
range(const char* p) { auto pp=p; while (*p) ++p; return range_t<const char*>(pp,p); };

	range_t<char*>
range(char* p) { auto pp=p; while (*p) ++p; return range_t<char*>(pp,p); };
*/

template<typename I>	struct  is_container <range_t<I>>	: std::true_type { };

static  __attribute__((unused)) struct range_converter_t {} rng;

/////////////////////////////////////////////////////////////////// RNG -- range proxy

	template<typename Ct>
	typename std::enable_if<
		is_container<Ct>::value,
		range_t<typename container_iterator<Ct>::type>
	>::type
operator | (Ct& C, range_converter_t r) { return range(std::begin(C), std::end(C)); };

	template<typename T, size_t N>
	range_t<T*>
operator | (T (&C)[N], range_converter_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Ct>
	typename std::enable_if<
		is_container<Ct>::value,
		range_t<typename container_iterator<Ct>::type>
	>::type
operator | (range_converter_t rng, Ct& C) { return range(std::begin(C), std::end(C)); };


/*
static  __attribute__((unused)) struct iot_t {} iot;

	template<typename Ct>
	typename std::enable_if<
		is_container<Ct>::value,
		range_t<typename container_iterator<Ct>::type>
	>::type
operator | (Ct& C, iot_t r) { return range(std::begin(C), std::end(C)); };
*/

template<typename T>	struct  is_range		: std::false_type {};
template<typename T>	struct  is_range<range_t<T>>	: std::true_type  {};

////////////////////////////////////////////////////////////////  RANGE OPS


//  Ct1 | Ct2   ---  search() --> range	   
/*
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value,  range_t&>::type
operator |       (Ct& C1, const Ct& C2)    { 
	auto it = search(C1.begin(), C1.end(), C2.begin(), C2.end());
	return  range_t(it, advance(it, distance(C2.end(), C2.begin())));
};

//  Ct1 / Ct2   ---  search() --> it
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value,  typename Ct::iterator>::type
operator /       (Ct& C1, const Ct& C2)    {  return  search(C1.begin(), C1.end(), C2.begin(), C2.end()); };
*/


#endif	// LVV_STL_H
