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

//  +Rg   ---   begin(),  	(n/a for c-arrays, use std::begin)

	template<typename Rg>		// do we need to care about r-value-ness here?
	eIF <is_range<Rg>()  &&  !std::is_array<Rg>::value,  rg_iterator<Rg>>
operator+      (Rg&& rg) { return std::begin(rg); };	// does not work with r-values


//  -Rg   ---   end(),  	(n/a for c-arrays, use std::end)
	template<typename Rg>
	eIF <is_range<Rg>()  &&  !std::is_array<Rg>::value,  rg_iterator<Rg>>
operator-      (Rg&& rg) { return  std::end(rg); };


	template<typename Rg>
	eIF <has_size<Rg>(), size_t>
operator~      (const Rg& rg) { return size(rg); };


//  if(!Rg)  --- (!Rg.empty())
//  if(Rg)   --- not implemented,  use  !!Rg instead
	template<typename Rg>
	eIF <has_empty<Rg>(), bool>
operator!      (const Rg& rg) { return rg.empty(); };


//  ++T, T++  ---  front()/back()/.first/.second  (n/a for c-arrays)

	template<typename Rg>
	auto
front    (Rg&& rg)  -> decltype(*std::begin(rg))  { return std::forward<rg_reference<Rg>>(*std::begin(rg)); };

	template<typename Rg>
	//eIF <has_back<Rg>()  &&  !std::is_array<Rg>::value, rg_reference<Rg>>
	eIF <has_back<Rg>(),  rg_reference<Rg>>
back      (Rg&& rg) { return std::forward<rg_reference<Rg>>(rg.back()); };

	template<class Rg, class=eIF<!has_back<Rg>()>>
	auto
back      (Rg&& rg) -> decltype(endz(rg))  { return std::forward<rg_reference<Rg>>(*std::prev(sto::endz(rg))); };


//  x << Rg >> x   ---  remove head / tail;   usage: scc 'dlong V{1,2,3};  i << V >> j; __ i, V, j;'   prints: 1 {2} 3 
	template<typename Rg, typename T>
	eIF <is_elem_of<T, Rg>() &&   has_pop_back<Rg>(),   Rg&&>
operator>>      (Rg&& rg, T&& x)    { x = rg.back();   rg.pop_back();   return  std::forward<Rg>(rg); };


	template<typename Rg, typename T>
	eIF <is_elem_of<T,Rg>()  &&   has_pop_front<Rg>(),   Rg&&>
operator<<      (T& x, Rg&& rg)    { x = rg.front();  rg.pop_front();  return  std::forward<Rg>(rg); };



// --Rg, Rg--  ---  pop_back/pop_front;     usage:   scc 'vint V{1,2}, W;  W << --V;  __ V, W;'   prints:    {2}, {1}
	template<typename Rg>
	eIF <is_range<Rg>(), Rg>
operator--      (Rg&& rg)         { rg.pop_front();   return  std::forward<Rg>(rg); };


	template<typename Rg>
	eIF <is_range<Rg>(), Rg>
operator--      (Rg&& rg, int)    { rg.pop_back();    return  std::forward<Rg>(rg); };


//////  X >> Rg << X

	namespace detail {
		template<class Rg, class X>  eIF<has_push_back  <Rg>(), Rg&&>  append_elem(Rg&& rg1, X&& x)   { rg1.push_back (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_push       <Rg>(), Rg&&>  append_elem(Rg&& rg1, X&& x)   { rg1.push      (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_1arg_insert<Rg>(), Rg&&>  append_elem(Rg&& rg1, X&& x)   { rg1.insert    (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<size_t N>                                char (&append_elem(char (&S)[N], char c))[N]  { char* e=endz(S);  assert((e-S)<N);  *e=c;  *++e='\0';  return S; };

		template<class Rg, class X>  eIF<has_push_front <Rg>(), Rg&&> prepend_elem(Rg&& rg1, X&& x)   { rg1.push_front(std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_push       <Rg>(), Rg&&> prepend_elem(Rg&& rg1, X&& x)   { rg1.push      (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_1arg_insert<Rg>(), Rg&&> prepend_elem(Rg&& rg1, X&& x)   { rg1.insert    (std::forward<X>(x));  return std::forward<Rg>(rg1); };

	}

	// Rg << x
	template<class Rg, class X>
	eIF <is_elem_of<X,Rg>(),  Rg&&>
operator << (Rg&& rg1, X&& x)            {  detail::append_elem(std::forward<Rg>(rg1),  std::forward<X>(x));   return  std::forward<Rg>(rg1); };


	// Rg << Cl2
	template<class Rg, class Rg2> 
	eIF <have_same_elem<Rg,Rg2>(),  Rg&&>
operator <<  (Rg&& rg1, Rg2&& rg2)         {  for (auto i=std::begin(rg2);  i!=endz(rg2);  ++i)  detail::append_elem(std::forward<Rg>(rg1), rg_elem_fwd<Rg2>(*i));   return  std::forward<Rg>(rg1); };


//////  T >> Rg 
	// x >> Rg 
	template<class X, class Rg>
	eIF <is_elem_of<X,Rg>(),  Rg&&>
operator >> (X&& x, Rg&& rg1)            {  detail::prepend_elem(std::forward<Rg>(rg1),  std::forward<X>(x));   return  std::forward<Rg>(rg1); };


	// sRn >> tRn
	template<class sRn, class tRn> 
	eIF <have_same_elem<tRn,sRn>(),  tRn&&>
operator >>  (sRn&& src, tRn&& trg)  {

	if (std::begin(src) == endz(src)) 
		return  std::forward<tRn>(trg);

	auto it = endz(src);
	do {
		detail::prepend_elem(std::forward<tRn>(trg), rg_elem_fwd<sRn>(*(it = std::prev(it))));
	} while ( it != std::begin(src));

	return  std::forward<tRn>(trg);
 };



//////////////////////////////////////////////////////////////////////////////////////////////  Rg op T

	namespace detail {


		// Rg / x     usage: scc 'copy(v9/2, v9/5,oi)'
			template<typename Rg, typename X>
			eIF <is_elem_of<X, Rg>(), rg_iterator<Rg>>
		find_elem(Rg&& rg, const X& x)   { return std::find(std::begin(rg), endz(rg), x); };



		// Rg / f
			template<typename Rg, typename F>
			eIF <is_callable<F, bool(rg_elem_type<Rg>)>::value, rg_iterator<Rg>>
		find_elem(Rg&& rg, const F& pred)  { return  std::find_if(std::begin(rg), endz(rg), pred); };


			
		//  Rg1 / Rg2   ---  search() --> it
			template<typename Rg1, typename Rg2>
			eIF <have_same_elem<Rg1, Rg2>(), rg_iterator<Rg1>>
		find_elem(Rg1&& rg1, const Rg2& rg2)    {  return std::search(std::begin(rg1), endz(rg1), std::begin(rg2), endz(rg2)); }; }

///////////////////////////////////////////////////////////////////////////////////////////////  OP-  (ERASE)
////////  Rg - T  
// ---  non callable
	template<typename Rg, typename T>
	eIF <is_range<Rg>() , rg_iterator<Rg>>
operator - (Rg&& rg, const T& t)                                { return  detail::find_elem(std::forward<Rg>(rg), t); };

/*
// ---  plain func
	template<typename Rg>
	eIF <is_range<Rg>() , rg_iterator<Rg>>
operator / (Rg&& rg, bool(*t)(rg_elem_type<Rg>))                { return  detail::find_elem(std::forward<Rg>(rg), t); };

// ---  func obj, lambda
	template<typename Rg>
	eIF <is_range<Rg>() , rg_iterator<Rg>>
operator / (Rg&& rg, std::function<bool(rg_elem_type<Rg>)> t)   { return  detail::find_elem(std::forward<Rg>(rg), t); };
*/

///////////////////////////////////////////////////////////////////////////////////////////////  OP/  (SEARCH)

////////  Rg / T  
// ---  non callable
	template<typename Rg, typename T>
	eIF <is_range<Rg>() , rg_iterator<Rg>>
operator / (Rg&& rg, const T& t)                                { return  detail::find_elem(std::forward<Rg>(rg), t); };

// ---  plain func
	template<typename Rg>
	eIF <is_range<Rg>() , rg_iterator<Rg>>
operator / (Rg&& rg, bool(*t)(rg_elem_type<Rg>))                { return  detail::find_elem(std::forward<Rg>(rg), t); };

// ---  func obj, lambda
	template<typename Rg>
	eIF <is_range<Rg>() , rg_iterator<Rg>>
operator / (Rg&& rg, std::function<bool(rg_elem_type<Rg>)> t)   { return  detail::find_elem(std::forward<Rg>(rg), t); };



////////  Rg % T

//  ---  non callable
	template<typename Rg, typename T>
	eIF <is_range<Rg>(), bool>
operator % (Rg&& rg, const T& t)                               { return  endz(rg) != detail::find_elem(std::forward<Rg>(rg), t); };

//  ---  plain func
	template<typename Rg>
	eIF <is_range<Rg>(), bool>
operator % (Rg&& rg, bool(*t)(rg_elem_type<Rg>))               { return  endz(rg) != detail::find_elem(std::forward<Rg>(rg), t); };

//  ---  func obj, lambda
	template<typename Rg>
	eIF <is_range<Rg>(), bool>
operator % (Rg&& rg, std::function<bool(rg_elem_type<Rg>)> t)  { return  endz(rg) != detail::find_elem(std::forward<Rg>(rg), t); };


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
	template<typename Rg>
	eIF <is_stack<Rg>(), Rg>
operator--      (Rg&& rg, int)    { rg.pop();   return std::forward<Rg>(rg); };

//  Stack >> x
//	scc 'int i=10; (stack<int>() << 1 << 2) >> i;  i'
//	3
//	scc 'int i=10; stack<int> st; st << 1 << 2 << 3;  st >> i; __ st, i;'
//	[1, 2] 3

	template<typename Rg, typename Xt>
	eIF <has_pop<Rg>()  &&  is_elem_of<Xt,Rg>(),  Rg>
operator>>      (Rg&& rg, Xt&& x)    { x = rg.top();  rg.pop();   return std::forward<Rg>(rg); };


//  Stack++
//	scc ' __ (stack<int>() << 1 << 2 << 3)++;'
//	3
//	scc 'stack<int> st; st << 1 << 2 << 3; st++'
//	3

	template<typename Rg>
 	eIF <has_top<Rg>(), rg_elem_type<Rg>>
back      (Rg&& rg)    { return rg.top(); };



/////////////////////////////////////////////////////////////////////////////////////////////////////  QUEUE


//  --Queue
	template<class Rg, class Xt>
	eIF <is_queue<Rg>(), Rg&&> 
operator--      (Rg&& rg)    { rg.pop();   return std::forward<Rg>(rg); };

//  x << Queue
	template<class Rg, class Xt>
	eIF <has_pop<Rg>()  &&  is_elem_of<Xt,Rg>(), Rg&&> &
operator<<      (Xt& x, Rg&& rg)    { x = rg.front();  rg.pop();   return std::forward<Rg>(rg); };



/////////////////////////////////////////////////////////////////////////////////////////////////////  ITERATOR


//  It / x   ---  find() --> it	   usage: scc 'copy(+v9/2, +v9/5, oi),  does not work with pointers (rg++ constrain)
	template<typename It>
	eIF <is_iterator<It>(),  It>
operator/       (It&& i, const typename std::iterator_traits<It>::value_type x)    {  while(*i != x) ++i;    return std::forward<It>(i); };


/////////////////////////////////////////////////////////////////////////////////////////////////////  GENERICS 

template<typename Rg>	auto operator++(Rg&& rg)      -> decltype(front(rg)) 		{ return front(rg); }
template<typename Rg>	auto operator++(Rg&& rg, int) -> decltype(back (rg)) 		{ return back (rg); }

					};
					#endif	// LVV_STL_H
