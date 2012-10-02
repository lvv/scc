					#ifndef  LVV_STL_H
					#define  LVV_STL_H

					#include <stddef.h>

					#include <algorithm>
					#include <iterator>
					#include <string>
					#include <deque>
					#include <tuple>
					#include <cassert>

					#include "meta.h"

					namespace sto {

/////////////////////////////////////////////////////////////////////////////////////////  MEMBERS ALIASES

//  +Ct   ---   begin(),  	(n/a for c-arrays, use std::begin)

	template<typename Ct>		// do we need to care about r-value-ness here?
	eIF <is_range<Ct>()  &&  !std::is_array<Ct>::value,  rn_iterator<Ct>>
operator+      (Ct&& C) { return std::begin(C); };	// does not work with r-values


//  -Ct   ---   end(),  	(n/a for c-arrays, use std::end)
	template<typename Ct>
	eIF <is_range<Ct>()  &&  !std::is_array<Ct>::value,  rn_iterator<Ct>>
operator-      (Ct&& C) { return  std::end(C); };


	template<typename Ct>
	eIF <has_size<Ct>(), size_t>
operator~      (const Ct& C) { return size(C); };


//  if(!Ct)  --- (!Ct.empty())
//  if(Ct)   --- not implemented,  use  !!Ct instead
	template<typename Ct>
	eIF <has_empty<Ct>(), bool>
operator!      (const Ct& C) { return C.empty(); };


//  ++T, T++  ---  front()/back()/.first/.second  (n/a for c-arrays)

	template<typename Ct>
	auto
front    (Ct&& C)  -> decltype(*std::begin(C))  { return std::forward<rn_reference<Ct>>(*std::begin(C)); };

	template<typename Ct>
	//eIF <has_back<Ct>()  &&  !std::is_array<Ct>::value, rn_reference<Ct>>
	eIF <has_back<Ct>(),  rn_reference<Ct>>
back      (Ct&& C) { return std::forward<rn_reference<Ct>>(C.back()); };

	template<class Ct, class=eIF<!has_back<Ct>()>>
	auto
back      (Ct&& C) -> decltype(endz(C))  { return std::forward<rn_reference<Ct>>(*std::prev(sto::endz(C))); };


//  x << Ct >> x   ---  remove head / tail;   usage: scc 'dlong V{1,2,3};  i << V >> j; __ i, V, j;'   prints: 1 {2} 3 
	template<typename Ct, typename T>
	eIF <is_elem_of<T, Ct>() &&   has_pop_back<Ct>(),   Ct&&>
operator>>      (Ct&& C, T&& x)    { x = C.back();   C.pop_back();   return  std::forward<Ct>(C); };


	template<typename Ct, typename T>
	eIF <is_elem_of<T,Ct>()  &&   has_pop_front<Ct>(),   Ct&&>
operator<<      (T& x, Ct&& C)    { x = C.front();  C.pop_front();  return  std::forward<Ct>(C); };



// --Ct, Ct--  ---  pop_back/pop_front;     usage:   scc 'vint V{1,2}, W;  W << --V;  __ V, W;'   prints:    {2}, {1}
	template<typename Ct>
	eIF <is_range<Ct>(), Ct>
operator--      (Ct&& C)         { C.pop_front();   return  std::forward<Ct>(C); };


	template<typename Ct>
	eIF <is_range<Ct>(), Ct>
operator--      (Ct&& C, int)    { C.pop_back();    return  std::forward<Ct>(C); };


//////  X >> Rn << X

	namespace detail {
		template<class Ct, class X>  eIF<has_push_back  <Ct>(), Ct&&>  append_elem(Ct&& C1, X&& x)   { C1.push_back (std::forward<X>(x));  return std::forward<Ct>(C1); };
		template<class Ct, class X>  eIF<has_push       <Ct>(), Ct&&>  append_elem(Ct&& C1, X&& x)   { C1.push      (std::forward<X>(x));  return std::forward<Ct>(C1); };
		template<class Ct, class X>  eIF<has_1arg_insert<Ct>(), Ct&&>  append_elem(Ct&& C1, X&& x)   { C1.insert    (std::forward<X>(x));  return std::forward<Ct>(C1); };
		template<size_t N>                                char (&append_elem(char (&S)[N], char c))[N]  { char* e=endz(S);  assert((e-S)<N);  *e=c;  *++e='\0';  return S; };

		template<class Ct, class X>  eIF<has_push_front <Ct>(), Ct&&> prepend_elem(Ct&& C1, X&& x)   { C1.push_front(std::forward<X>(x));  return std::forward<Ct>(C1); };
		template<class Ct, class X>  eIF<has_push       <Ct>(), Ct&&> prepend_elem(Ct&& C1, X&& x)   { C1.push      (std::forward<X>(x));  return std::forward<Ct>(C1); };
		template<class Ct, class X>  eIF<has_1arg_insert<Ct>(), Ct&&> prepend_elem(Ct&& C1, X&& x)   { C1.insert    (std::forward<X>(x));  return std::forward<Ct>(C1); };

	}

	// Rn << x
	template<class Ct, class X>
	eIF <is_elem_of<X,Ct>(),  Ct&&>
operator << (Ct&& C1, X&& x)            {  detail::append_elem(std::forward<Ct>(C1),  std::forward<X>(x));   return  std::forward<Ct>(C1); };


	// Rn << Cl2
	template<class Ct, class Ct2> 
	eIF <have_same_elem<Ct,Ct2>(),  Ct&&>
operator <<  (Ct&& C1, Ct2&& C2)         {  for (auto i=std::begin(C2);  i!=endz(C2);  ++i)  detail::append_elem(std::forward<Ct>(C1), rn_elem_fwd<Ct2>(*i));   return  std::forward<Ct>(C1); };


//////  T >> Rn 
	// x >> Rn 
	template<class X, class Ct>
	eIF <is_elem_of<X,Ct>(),  Ct&&>
operator >> (X&& x, Ct&& C1)            {  detail::prepend_elem(std::forward<Ct>(C1),  std::forward<X>(x));   return  std::forward<Ct>(C1); };


	// sRn >> tRn
	template<class sRn, class tRn> 
	eIF <have_same_elem<tRn,sRn>(),  tRn&&>
operator >>  (sRn&& src, tRn&& trg)  {

	if (std::begin(src) == endz(src)) 
		return  std::forward<tRn>(trg);

	auto it = endz(src);
	do {
		detail::prepend_elem(std::forward<tRn>(trg), rn_elem_fwd<sRn>(*(it = std::prev(it))));
	} while ( it != std::begin(src));

	return  std::forward<tRn>(trg);
 };



//////////////////////////////////////////////////////////////////////////////////////////////  Ct op T

	namespace detail {


		// Ct / x     usage: scc 'copy(v9/2, v9/5,oi)'
			template<typename Ct, typename X>
			eIF <is_elem_of<X, Ct>(), rn_iterator<Ct>>
		find_elem(Ct&& C, const X& x)   { return std::find(std::begin(C), endz(C), x); };



		// Ct / f
			template<typename Ct, typename F>
			eIF <is_callable<F, bool(rn_elem_type<Ct>)>::value, rn_iterator<Ct>>
		find_elem(Ct&& C, const F& pred)  { return  std::find_if(std::begin(C), endz(C), pred); };


			
		//  Ct1 / Ct2   ---  search() --> it
			template<typename Ct1, typename Ct2>
			eIF <have_same_elem<Ct1, Ct2>(), rn_iterator<Ct1>>
		find_elem(Ct1&& C1, const Ct2& C2)    {  return std::search(std::begin(C1), endz(C1), std::begin(C2), endz(C2)); }; }

///////////////////////////////////////////////////////////////////////////////////////////////  OP-  (ERASE)
////////  Ct - T  
// ---  non callable
	template<typename Ct, typename T>
	eIF <is_range<Ct>() , rn_iterator<Ct>>
operator - (Ct&& C, const T& t)                                { return  detail::find_elem(std::forward<Ct>(C), t); };

/*
// ---  plain func
	template<typename Ct>
	eIF <is_range<Ct>() , rn_iterator<Ct>>
operator / (Ct&& C, bool(*t)(rn_elem_type<Ct>))                { return  detail::find_elem(std::forward<Ct>(C), t); };

// ---  func obj, lambda
	template<typename Ct>
	eIF <is_range<Ct>() , rn_iterator<Ct>>
operator / (Ct&& C, std::function<bool(rn_elem_type<Ct>)> t)   { return  detail::find_elem(std::forward<Ct>(C), t); };
*/

///////////////////////////////////////////////////////////////////////////////////////////////  OP/  (SEARCH)

////////  Ct / T  
// ---  non callable
	template<typename Ct, typename T>
	eIF <is_range<Ct>() , rn_iterator<Ct>>
operator / (Ct&& C, const T& t)                                { return  detail::find_elem(std::forward<Ct>(C), t); };

// ---  plain func
	template<typename Ct>
	eIF <is_range<Ct>() , rn_iterator<Ct>>
operator / (Ct&& C, bool(*t)(rn_elem_type<Ct>))                { return  detail::find_elem(std::forward<Ct>(C), t); };

// ---  func obj, lambda
	template<typename Ct>
	eIF <is_range<Ct>() , rn_iterator<Ct>>
operator / (Ct&& C, std::function<bool(rn_elem_type<Ct>)> t)   { return  detail::find_elem(std::forward<Ct>(C), t); };



////////  Ct % T

//  ---  non callable
	template<typename Ct, typename T>
	eIF <is_range<Ct>(), bool>
operator % (Ct&& C, const T& t)                               { return  endz(C) != detail::find_elem(std::forward<Ct>(C), t); };

//  ---  plain func
	template<typename Ct>
	eIF <is_range<Ct>(), bool>
operator % (Ct&& C, bool(*t)(rn_elem_type<Ct>))               { return  endz(C) != detail::find_elem(std::forward<Ct>(C), t); };

//  ---  func obj, lambda
	template<typename Ct>
	eIF <is_range<Ct>(), bool>
operator % (Ct&& C, std::function<bool(rn_elem_type<Ct>)> t)  { return  endz(C) != detail::find_elem(std::forward<Ct>(C), t); };


/////////////////////////////////////////////////////////////////////////////////////////////////////  TUPLE / PAIR

template<class U, class V>   U&    front  (std::pair<U,V>&  P)		{ return           P.first;   };
template<class U, class V>   U&&   front  (std::pair<U,V>&& P)		{ return std::move(P.first);  };

template<class U, class V>   V&    back   (std::pair<U,V>&  P)		{ return           P.second;  };
template<class U, class V>   V&&   back   (std::pair<U,V>&& P)		{ return std::move(P.second); };


// ++Tpl 
	template <class... Types>
	typename std::tuple_element<std::tuple_size<std::tuple<Types...> >::value-1, typename std::tuple<Types...> >::type&
back	(typename std::tuple<Types...>& Tpl)  {  return  std::get<std::tuple_size<std::tuple<Types...> >::value-1>(Tpl); };

// ++Tpl  (const)
	template <class... Types>
	const typename std::tuple_element<std::tuple_size<std::tuple<Types...> >::value-1, typename std::tuple<Types...> >::type&
back	(const typename std::tuple<Types...>& Tpl)  {  return  std::get<std::tuple_size<std::tuple<Types...> >::value-1>(Tpl); };


// Tpl++ 
	template <class... Types>
	typename std::tuple_element<0, std::tuple<Types...> >::type&
front	(typename std::tuple<Types...>& Tpl)  {  return  std::get<0>(Tpl); };

// Tpl++  (const) 
	template <class... Types>
	const typename std::tuple_element<0, std::tuple<Types...> >::type&
front	(const typename std::tuple<Types...>& Tpl)  {  return  std::get<0>(Tpl); };


	template <class... Types>
	constexpr size_t
operator~	(const typename std::tuple<Types...>& Tpl)  {  return  std::tuple_size<std::tuple<Types...> >::value; };


/////////////////////////////////////////////////////////////////////////////////////////////////////  STACK


//  Stack--
	template<typename Ct>
	eIF <is_stack<Ct>(), Ct>
operator--      (Ct&& C, int)    { C.pop();   return std::forward<Ct>(C); };

//  Stack >> x
//	scc 'int i=10; (stack<int>() << 1 << 2) >> i;  i'
//	3
//	scc 'int i=10; stack<int> st; st << 1 << 2 << 3;  st >> i; __ st, i;'
//	[1, 2] 3

	template<typename Ct, typename Xt>
	eIF <has_pop<Ct>()  &&  is_elem_of<Xt,Ct>(),  Ct>
operator>>      (Ct&& C, Xt&& x)    { x = C.top();  C.pop();   return std::forward<Ct>(C); };


//  Stack++
//	scc ' __ (stack<int>() << 1 << 2 << 3)++;'
//	3
//	scc 'stack<int> st; st << 1 << 2 << 3; st++'
//	3

	template<typename Ct>
 	eIF <has_top<Ct>(), rn_elem_type<Ct>>
back      (Ct&& C)    { return C.top(); };



/////////////////////////////////////////////////////////////////////////////////////////////////////  QUEUE


//  --Queue
	template<class Ct, class Xt>
	eIF <is_queue<Ct>(), Ct&&> 
operator--      (Ct&& C)    { C.pop();   return std::forward<Ct>(C); };

//  x << Queue
	template<class Ct, class Xt>
	eIF <has_pop<Ct>()  &&  is_elem_of<Xt,Ct>(), Ct&&> &
operator<<      (Xt& x, Ct&& C)    { x = C.front();  C.pop();   return std::forward<Ct>(C); };



/////////////////////////////////////////////////////////////////////////////////////////////////////  ITERATOR


//  It / x   ---  find() --> it	   usage: scc 'copy(+v9/2, +v9/5, oi),  does not work with pointers (C++ constrain)
	template<typename It>
	eIF <is_iterator<It>(),  It>
operator/       (It&& i, const typename std::iterator_traits<It>::value_type x)    {  while(*i != x) ++i;    return std::forward<It>(i); };


/////////////////////////////////////////////////////////////////////////////////////////////////////  GENERICS 

template<typename Rn>	auto operator++(Rn&& rn)      -> decltype(front(rn)) 			{ return front(rn); }
template<typename Rn>	auto operator++(Rn&& rn, int) -> decltype(back (rn)) 			{ return back (rn); }

					};
					#endif	// LVV_STL_H
