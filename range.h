
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

#include "meta.h"

/////////////////////////////////////////////////////////////////////////////////////////  ITERATOR_RANGE

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


/////////////////////////////////////////////////////////////////////////////////////////  NUMERIC_RANGE


	template<typename T>
struct  numeric_range {

		//typedef		--- 		const_iterator;
		typedef		T		value_type;
		typedef		size_t		difference_type;
		typedef		size_t		size_type;
		typedef		const T*	const_pointer;
		typedef		const T*	pointer;
		typedef		const T&	const_reference;
		typedef		const_reference	reference;

	struct	const_iterator {
		explicit const_iterator (const numeric_range<T>& range, T init=end_value) : range(range),  current(init) {};

			typedef		std::input_iterator_tag		iterator_category;

			typedef		T		value_type;
			typedef		size_t		difference_type ;
			typedef		size_t		size_type ;
			typedef		const T*	const_pointer ;
			typedef		const_pointer	pointer ;
			typedef		const T&	const_reference ;
			typedef		const_reference	reference ;

		const numeric_range<T>&		range;
		T				current;

		const_reference	operator*()	const	{ return   current; }
		const_pointer	operator->()	const	{ return  &current; }
		const_iterator	operator++()		{ current+=range.step;  return *this; }
		const_iterator	operator++(int)		{ auto tmp=*this;  current+=range.step;  return tmp; }

		bool		operator==(const_iterator rhs)	const	{ return  std::abs(current - rhs.current) <= range.step; }
		bool		operator!=(const_iterator rhs)	const	{ return  std::abs(current - rhs.current) >  range.step; }
		//bool		operator< (const_iterator rhs)	const	{ return  current < rhs.current; }
	};
		typedef		const_iterator	iterator;


	T low, high, step;
	constexpr static T end_value = std::numeric_limits<T>::max();

	// CTOR
	numeric_range()  : low(T()), high(T()), step(T())  {};
	numeric_range(T low, T high, T step=1)  : low(low), high(high), step(step) {};


	const_iterator	begin() const	{ return const_iterator(*this, low); };
	const_iterator	end()   const	{ return const_iterator(*this, high); };

};

template<typename T>	struct  is_collection_t <numeric_range<T>>	: std::true_type { };

	template<class T1, class T2, class T3=T1, class T=decltype(T1()+T2()+T3())>
	eIF<std::is_arithmetic<T>::value,  numeric_range<T>>
range(T1 low,  T2 high,  T3 step=1) { return numeric_range<T>(low, high, step); };


////////////////////////////////////////////////////////////////  OPERATOR, -- (it1, it2) ctor
//	template<typename I>
//	eIF<is_iterator<I>(), iterator_range<I>>
//operator, (I b, I e)  { return iterator_range<I>(b,e); };

////////////////////////////////////////////////////////////////  RANGE() -- makes range

	template<typename I>
	eIF<is_iterator<I>(), iterator_range<I>>
range(I b, I e) { return iterator_range<I>(b,e); };


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

/*
	template<typename Ct>
	eIF<
		is_collection<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>
operator | (Ct& C, range_converter_t r) { return range(std::begin(C), std::end(C)); };

	template<typename T, size_t N>
	iterator_range<T*>
operator | (T (&C)[N], range_converter_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Ct>
	eIF<
		is_collection<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>
operator | (range_converter_t rng, Ct& C) { return range(std::begin(C), std::end(C)); };
*/

/*
static  __attribute__((unused)) struct iot_t {} iot;

	template<typename Ct>
	typename std::enable_if<
		is_collection<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>::type
operator | (Ct& C, iot_t r) { return range(std::begin(C), std::end(C)); };
*/

template<typename T>	struct  is_range_t			: std::false_type {};
template<typename T>	struct  is_range_t<iterator_range<T>>	: std::true_type  {};
template<typename T>	struct  is_range_t<numeric_range<T>>	: std::true_type  {};
template<typename T>    constexpr bool   is_range()        { return  is_range_t<T>::value; };


////////////////////////////////////////////////////////////////  RANGE OPS


//  Ct1 | Ct2   ---  search() --> range	   
/*
	template<typename Ct>
	typename std::enable_if <is_collection<Ct>(),  iterator_range&>::type
operator |       (Ct& C1, const Ct& C2)    { 
	auto it = search(C1.begin(), C1.end(), C2.begin(), C2.end());
	return  iterator_range(it, advance(it, distance(C2.end(), C2.begin())));
};

//  Ct1 / Ct2   ---  search() --> it
	template<typename Ct>
	typename std::enable_if <is_collection<Ct>(),  typename Ct::iterator>::type
operator /       (Ct& C1, const Ct& C2)    {  return  search(C1.begin(), C1.end(), C2.begin(), C2.end()); };
*/

/////////////////////////////////////////////////////////////////////////////////////  CL TRAITS 
template<typename T, typename Ct>     constexpr bool   is_elem_of()        { return  is_collection<Ct>()  &&  std::is_same<rm_ref<T>, rm_ref<cl_elem_type<Ct>>>::value; }
template<typename Ct1, typename Ct2>  constexpr bool   have_same_elem()    { return  is_collection<Ct1>()  &&  is_collection<Ct2>()  &&  std::is_convertible<cl_elem_type<Ct1>,  cl_elem_type<Ct2>>::value; }

#endif	// LVV_STL_H
