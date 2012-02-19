#ifndef  LVV_STL_H
#define  LVV_STL_H

#include <stddef.h>
#include <iterator>
#include <string>
#include <cstring>
#include <deque>
#include <tuple>

#include "meta.h"

/////////////////////////////////////////////////////////////////////////////////////////  MEMEBERS ALIASES

//  +Ct / -Ct   ---   end() /begin()
	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator+      (Ct& C) { return begin(C); };

	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator-      (Ct& C) { return  end(C); };

//  !Ct  --- size()
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, ssize_t>::type
operator!      (const Ct& C) { return C.size(); };	// FIXME: specialization for non-contigues-mem-Ct, C-arr


//  ++T / t++  ---  front()/back()/.first/.second
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::reference>::type
operator++      (Ct& C) { return C.front(); };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::reference>::type
operator++      (Ct& C, int) { return C.back(); };

template<typename U, typename V>   U&     operator++   (std::pair<U,V>& P)      { return P.first;  };
template<typename U, typename V>   V&     operator++   (std::pair<U,V>& P, int) { return P.second; };

	template <class... Types>
	typename std::tuple_element<std::tuple_size<std::tuple<Types...> >::value-1, typename std::tuple<Types...> >::type&
operator++	(typename std::tuple<Types...>& Tpl, int)  {  return  std::get<std::tuple_size<std::tuple<Types...> >::value-1>(Tpl); };


	template <class... Types>
	typename std::tuple_element<0, std::tuple<Types...> >::type&
operator++	(typename std::tuple<Types...>& Tpl)  {  return  std::get<0>(Tpl); };


//  x >> Ct << x   ---  push_back/push_front replaement;   usage: scc 'vint V;  V << 1 << 2'   prints: {1, 2}
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct&>::type
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.push_back(x);   return C; };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct>::type&
operator>>      (typename Ct::value_type x, Ct& C)    { C.push_front(x);  return C; };

/////////////////////////////////////////////////////////////////////////////////////////////////////  STACK

//  Stack << x
	template<typename Ct>
	typename std::enable_if <is_stack<Ct>::value, Ct&>::type&
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.push(x);   return C; };

//  Stack--
	template<typename Ct>
	typename std::enable_if <is_stack<Ct>::value, Ct&>::type&
operator--      (Ct& C, int)    { C.pop();   return C; };

//  Stack >> x
	template<typename Ct>
	typename std::enable_if <is_stack<Ct>::value, typename Ct::value_type&>::type&
operator>>      (Ct& C, typename Ct::value_type& x)    { x = C.top();  C.pop();   return x; };

//  Stack++
	template<typename Ct>
	typename std::enable_if <is_stack<Ct>::value, typename Ct::value_type&>::type&
operator++      (Ct& C, int)    { return C.top(); };

//  !Stack
	template<typename Ct>
	typename std::enable_if <is_stack<Ct>::value, size_t>::type
operator!      (Ct& C)    { return C.size(); };


/////////////////////////////////////////////////////////////////////////////////////////////////////  STACK

//  x << Ct >> x   ---  remove head / tail;   usage: scc 'llong V{1,2,3};  i << V >> j; __ i, V, j;'   prints: 1 {2} 3 
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct>::type&
operator>>      (Ct& C, typename Ct::value_type& x)    { x = C.back();   C.pop_back();    return C; };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct&>::type
operator<<      (typename Ct::value_type& x, Ct& C)    { x = C.front();  C.pop_front();  return C; };


// Ct1 << Ct2
	template<typename Ct1, typename Ct2>
	typename std::enable_if <
		is_container<Ct1>::value   &&  is_container<Ct2>::value
			&&  std::is_same<typename Ct1::value_type, typename Ct2::value_type>::value
		, Ct1
	>::type &
operator <<      (Ct1& C1, const Ct2& C2)    { for(auto x: C2) C1.push_back(x);   return  C1; };


// Ct1 >> Ct2
	template<typename Ct1, typename Ct2>
	typename std::enable_if <
		is_container<Ct1>::value   &&  is_container<Ct2>::value
			&&  std::is_same<typename Ct1::value_type, typename Ct2::value_type>::value
		, Ct1
	>::type &
operator >>      (const Ct1& C1, Ct2& C2)    { for(auto x: C1) C2.push_back(x);   return  C2; };


// --Ct/Ct--  ---  pop_back/pop_front;     usage:   scc 'vint V{1,2}, W;  W << --V;  __ V, W;'   prints:    {2}, {1}
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::value_type>::type &&
operator--      (Ct& C)         { typename Ct::value_type x = C.front();   C.pop_front();   return  std::move(x); };


	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::value_type>::type &&
operator--      (Ct& C, int)    { typename Ct::value_type x = C.back();    C.pop_back();    return  std::move(x); };


// Ct1 <= Ct2
	template<typename Ct1, typename Ct2>
	typename std::enable_if <
		is_container<Ct1>::value   &&  is_container<Ct2>::value
			&&  std::is_same<typename Ct1::value_type, typename Ct2::value_type>::value
		, Ct1
	>::type &
operator <=      (Ct1& C1, const Ct2& C2)    { C1.clear(); for(auto x: C2) C1.push_back(x);   return  C1; };

	template<typename Ct, size_t N>
	typename std::enable_if < is_container<Ct>::value , Ct >::type &
operator <=      (Ct& C, const typename Ct::value_type (&A)[N])    { C.clear();  for(auto x: A) C.push_back(x);   return  C; };


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
	range_t(iterator b, iterator e)  : b_(b), e_(e) {};

	//template<typename Ct>
	//range_t( typename std::enable_if<std::is_same<I, typename Ct::iterator>::value, Ct>::type&  C)  : b_(begin(C)), e_(end(C)) {};

	iterator	begin()		{ return b_; };
	iterator	end()		{ return e_; };
	const_iterator	begin() const	{ return b_; };
	const_iterator	end()   const	{ return e_; };

	range_t& operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };
};

	template<>
struct  range_t<const char*> {

		typedef		const char*							I;

		typedef		I							iterator;
		typedef		I							const_iterator;
		typedef		typename std::iterator_traits<I>::value_type		value_type;
		typedef		typename std::iterator_traits<I>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<I>::pointer		pointer ;
		typedef		typename std::iterator_traits<I>::reference		reference ;

	iterator b_, e_;
	range_t(iterator b, iterator e)  : b_(b), e_(e) {};

	range_t(const char* p)  : b_(p), e_(p+std::strlen(p)) {};

	iterator	begin()		{ return b_; };
	iterator	end()		{ return e_; };
	const_iterator	begin() const	{ return b_; };
	const_iterator	end()   const	{ return e_; };

	//range_t& operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };
};

	template<typename I>
	typename std::enable_if<is_iterator<I>::value, range_t<I>>::type
range(I b, I e) { return range_t<I>(b,e); };


	template<typename I>
	typename std::enable_if<is_iterator<I>::value, range_t<I>>::type
operator / (I b, I e) { return range_t<I>(b,e); };

	template<typename Ct>
	typename std::enable_if<is_container<Ct>::value, range_t<typename Ct::iterator>>::type
range(Ct& C) { return range_t<typename Ct::iterator>(begin(C),end(C)); };

	range_t<const char*>
range(const char* p) { return range_t<const char*>(p,p+std::strlen(p)); };


template<typename I>	struct  is_container <range_t<I>>	: std::true_type { };

struct rng_t {} rng;


	template<typename Ct>
	typename std::enable_if<
		is_container<Ct>::value,
		range_t<typename container_iterator<Ct>::type>
	>::type
operator | (Ct& C, rng_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Ct>
	typename std::enable_if<
		is_container<Ct>::value,
		range_t<typename container_iterator<Ct>::type>
	>::type
operator | (rng_t rng, Ct& C) { return range(std::begin(C), std::end(C)); };


#endif	// LVV_STL_H
