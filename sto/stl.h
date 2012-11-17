					#ifndef  STO_STL_H
					#define  STO_STL_H

					#include <stddef.h>

					#include <algorithm>
					#include <iterator>
					#include <string>
					#include <deque>
					#include <tuple>
					#include <cassert>

					#include <sto/meta.h>

					namespace sto {

/////////////////////////////////////////////////////////////////////////////////////////  MEMBERS ALIASES

//  +Rg   ---   begin(),  	(n/a for c-arrays, use std::begin)

	template<typename Rg>		// do we need to care about r-value-ness here?
	eIF <is_range<Rg>::value  &&  !std::is_array<Rg>::value,  rg_iterator<Rg>>
operator+      (Rg&& C) { return std::begin(C); };	// does not work with r-values


//  -Rg   ---   end(),  	(n/a for c-arrays, use std::end)
	template<typename Rg>
	eIF <is_range<Rg>::value  &&  !std::is_array<Rg>::value,  rg_iterator<Rg>>
operator-      (Rg&& C) { return  std::end(C); };


	template<typename Rg>
	eIF <has_size<Rg>::value, size_t>
operator~      (const Rg& C) { return size(C); };


//  if(!Rg)  --- (!Rg.empty())
//  if(Rg)   --- not implemented,  use  !!Rg instead
	template<typename Rg>
	eIF <has_empty<Rg>::value, bool>
operator!      (const Rg& C) { return C.empty(); };


//  ++T, T++  ---  front()/back()/.first/.second  (n/a for c-arrays)

	template<typename Rg>
	auto
front    (Rg&& C)  -> decltype(*std::begin(C))  { return std::forward<decltype(*std::begin(C))>(*std::begin(C)); };


	template<typename Rg>		// has_back
	eIF <has_back<Rg>::value,  rg_reference<Rg>>
back      (Rg&& C) { return std::forward<rg_reference<Rg>>(C.back()); };


	template<class Rg, class=eIF<!has_back<Rg>::value>>	// ! has_back
	auto
back      (Rg&& C) -> decltype(endz(C))  { return std::forward<decltype(endz(C))>(*std::prev(sto::endz(C))); };


//  x << Rg >> x   ---  remove head / tail;   usage: scc 'dlong V{1,2,3};  i << V >> j; __ i, V, j;'   prints: 1 {2} 3 
	template<typename Rg, typename T>
	eIF <is_elem_of<T, Rg>::value &&   has_pop_back<Rg>::value,   Rg&&>
operator>>      (Rg&& C, T&& x)    { x = C.back();   C.pop_back();   return  std::forward<Rg>(C); };


	template<typename Rg, typename T>
	eIF <is_elem_of<T,Rg>::value  &&   has_pop_front<Rg>::value,   Rg&&>
operator<<      (T& x, Rg&& C)    { x = C.front();  C.pop_front();  return  std::forward<Rg>(C); };



// --Rg, Rg--  ---  pop_back/pop_front;     usage:   scc 'vint V{1,2}, W;  W << --V;  __ V, W;'   prints:    {2}, {1}
	template<typename Rg>
	eIF <is_range<Rg>::value, Rg>
operator--      (Rg&& C)         { C.pop_front();   return  std::forward<Rg>(C); };


	template<typename Rg>
	eIF <is_range<Rg>::value, Rg>
operator--      (Rg&& C, int)    { C.pop_back();    return  std::forward<Rg>(C); };


//////  X >> Rg << X

	namespace detail {
		template<class Rg, class X>  eIF<has_push_back  <Rg>::value, Rg&&>	append_elem(Rg&& rg1, X&& x)   { rg1.push_back (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_push       <Rg>::value, Rg&&>	append_elem(Rg&& rg1, X&& x)   { rg1.push      (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_1arg_insert<Rg>::value, Rg&&>	append_elem(Rg&& rg1, X&& x)   { rg1.insert    (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		//template<class Rg, class X>  eIF<is_cstr<Rg>::value, Rg&&>		append_elem(Rg&& rg1, X&& x)   { auto e=endz(rg1); *e=x; *(e+1)='\0'; return std::forward<Rg>(rg1); };
		//template<size_t N>                           char (&append_elem(char (&S)[N], char c))[N]  { char* e=endz(S);  assert((e-S)<N);  *e=c;  *++e='\0';  return S; };

		template<class Rg, class X>  eIF<has_push_front <Rg>::value, Rg&&>	prepend_elem(Rg&& rg1, X&& x)   { rg1.push_front(std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_push       <Rg>::value, Rg&&>	prepend_elem(Rg&& rg1, X&& x)   { rg1.push      (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<has_1arg_insert<Rg>::value, Rg&&>	prepend_elem(Rg&& rg1, X&& x)   { rg1.insert    (std::forward<X>(x));  return std::forward<Rg>(rg1); };
		template<class Rg, class X>  eIF<!has_push_front<Rg>::value && has_insert<Rg>::value, Rg&&>
											prepend_elem(Rg&& rg1, X&& x)   { rg1.insert    (std::begin(rg1), std::forward<X>(x));  return std::forward<Rg>(rg1); };
		//template<size_t N>                                               char (&prepend_elem(char (&S)[N], char c))[N]  { char* e=endz(S);  assert((e-S)<N);  std::copy(S,e+1, S+1); *S=c;  return S; };

	}

	// Rg << x
	template<class Rg, class X>
	eIF <is_elem_of<X,Rg>::value,  Rg&&>
operator << (Rg&& rg1, X&& x)            {  detail::append_elem(std::forward<Rg>(rg1),  std::forward<X>(x));   return  std::forward<Rg>(rg1); };


	// Rg << Cl2
	template<class Rg, class Rg2> 
	eIF <have_same_elem<Rg,Rg2>::value,  Rg&&>
operator <<  (Rg&& rg1, Rg2&& rg2)         {  for (auto i=std::begin(rg2);  i!=endz(rg2);  ++i)  detail::append_elem(std::forward<Rg>(rg1), rg_elem_fwd<Rg2>(*i));   return  std::forward<Rg>(rg1); };


//////  T >> Rg 
	// x >> Rg 
	template<class X, class Rg>
	eIF <is_elem_of<X,Rg>::value,  Rg&&>
operator >> (X&& x, Rg&& rg1)            {  detail::prepend_elem(std::forward<Rg>(rg1),  std::forward<X>(x));   return  std::forward<Rg>(rg1); };


	// sRn >> tRn
	template<class sRn, class tRn> 
	eIF <have_same_elem<tRn,sRn>::value,  tRn&&>
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
			eIF <is_elem_of<X, Rg>::value, rg_iterator<Rg>>
		find_elem(Rg&& C, const X& x)   { return std::find(std::begin(C), endz(C), x); };



		// Rg / f
			template<typename Rg, typename F>
			eIF <is_callable<F, bool(rg_elem_type<Rg>)>::value, rg_iterator<Rg>>
		find_elem(Rg&& C, const F& pred)  { return  std::find_if(std::begin(C), endz(C), pred); };


			
		//  Rg1 / Rg2   ---  search() --> it
			template<typename Rg1, typename Rg2>
			eIF <have_same_elem<Rg1, Rg2>::value, rg_iterator<Rg1>>
		find_elem(Rg1&& rg1, const Rg2& rg2)    {  return std::search(std::begin(rg1), endz(rg1), std::begin(rg2), endz(rg2)); }; }


///////////////////////////////////////////////////////////////////////////////////////////////  OP-  (ERASE)

	
// vector - value
	template<typename Rg>
	Rg&&
erase_value_impl (Rg&& rg, rg_elem_type<Rg> value, vector_erasable) {
	rg.erase(std::remove(rg.begin(), rg.end(), value), rg.end());
	return  std::forward<Rg>(rg);
 };

// list - value
	template<typename Rg>
	Rg&&
erase_value_impl (Rg&& rg, rg_elem_type<Rg> value, list_erasable) {
	rg.remove(value);
	return  std::forward<Rg>(rg);
 };

// set - value
	template<typename Rg>
	Rg&&
erase_value_impl (Rg&& rg, rg_elem_type<Rg> value, map_erasable) {
	rg.erase(value);
	return  std::forward<Rg>(rg);
 };


///// rg - value
	template<class Rg>
	eIF <is_range<Rg>::value   &&  !is_map<Rg>::value, Rg>
operator- (Rg&& rg, rg_elem_type<Rg> value)    {
	return  erase_value_impl(std::forward<Rg>(rg), value, erasable_category(rg));
 };

	
// mapa - value
	template<class Rg>
	eIF <is_range<Rg>::value   &&  is_map<Rg>::value, Rg>
operator- (Rg&& rg, typename rm_qualifier<Rg>::key_type value)    {
	rg.erase(value);
	return  std::forward<Rg>(rg);
 };



// vector - pred
	template<class Rg>
	Rg&&
erase_predicate_impl(Rg&& rg,  bool(*f)(const rg_elem_type<Rg>&), vector_erasable) {
	rg.erase(std::remove_if(rg.begin(), rg.end(), f), rg.end());
	return  std::forward<Rg>(rg);
 };

// list - pred
	template<typename Rg>
	Rg&&
erase_predicate_impl(Rg&& rg,  bool(*f)(const rg_elem_type<Rg>&), list_erasable) {
	rg.remove_if(f);
	return  std::forward<Rg>(rg);
 };


///// Rg - pred
	template<class Rg>
	eIF<is_range<Rg>::value  &&  ! is_map<Rg>::value, Rg>
operator-(Rg&& rg, bool(*f)(const rg_elem_type<Rg>&)) {
	return  erase_predicate_impl(std::forward<Rg>(rg), f, erasable_category(rg));
 };

// map - pred
	template<class Rg>
	eIF<is_range<Rg>::value  &&  is_map<Rg>::value, Rg>
operator-(Rg&& rg, bool(*f)(const typename rm_qualifier<Rg>::key_type&)) {
	for (auto i = rg.begin();  i != rg.end(); ) {
		if (f(i->first))	rg.erase(i++);
		else		++i;
	}
	return  std::forward<Rg>(rg);
 };

// rg - it
	template<typename Rg>
	eIF<is_range<Rg>::value  &&  !is_cstr<Rg>::value,  Rg&&>
operator-(Rg&& rg,  rg_iterator<Rg> it) {
	rg.erase(it);
	return  std::forward<Rg>(rg);
 };

// cstr - it
/*
	template<typename Rg>
	eIF<is_range<Rg>::value  &&  is_cstr<Rg>::value,  Rg&&>
operator-(Rg&& rg,  rg_iterator<Rg> it) {
	std::copy(it+1, endz(rg), it);
	return  std::forward<Rg>(rg);
 };
 */

// rg - sub_rg
	template<class Rg, class sub_Rg>
	eIF<is_range<Rg>::value  &&  !is_cstr<Rg>::value &&  is_range<sub_Rg>::value  &&  have_same_elem<Rg,sub_Rg>::value,  Rg&&>
operator-(Rg&& rg,  sub_Rg&& sub_rg) {
	auto rg_e = endz(rg);
	auto b    = std::search(std::begin(rg), rg_e, std::begin(sub_rg), endz(sub_rg));
	if (b==rg_e)  return  std::forward<Rg>(rg);
	auto e = b;
	std::advance(e,size(sub_rg));
	rg.erase(b,e); 
	return  std::forward<Rg>(rg);
 };

// cstr - sub_rg
	template<class Rg, class sub_Rg>
	eIF<is_cstr<Rg>::value &&  is_range<sub_Rg>::value  &&  have_same_elem<Rg,sub_Rg>::value,  Rg&&>
operator-(Rg&& rg,  sub_Rg&& sub_rg) {
	auto rg_e = endz(rg);
	auto b    = std::search(std::begin(rg), rg_e, std::begin(sub_rg), endz(sub_rg));
	if (b==rg_e)  return  std::forward<Rg>(rg);
	auto e = b;
	//rg.erase(b,e); 
	std::copy(e,rg_e+1,b);
	return  std::forward<Rg>(rg);
 };


///////////////////////////////////////////////////////////////////////////////////////////////  OP/  (SEARCH)

////////  Rg / T  
// ---  non callable
	template<typename Rg, typename T>
	eIF <is_range<Rg>::value , rg_iterator<Rg>>
operator / (Rg&& C, const T& t)                                { return  detail::find_elem(std::forward<Rg>(C), t); };

// ---  plain func
	template<typename Rg>
	eIF <is_range<Rg>::value , rg_iterator<Rg>>
operator / (Rg&& C, bool(*t)(rg_elem_type<Rg>))                { return  detail::find_elem(std::forward<Rg>(C), t); };

// ---  func obj, lambda
	template<typename Rg>
	eIF <is_range<Rg>::value , rg_iterator<Rg>>
operator / (Rg&& C, std::function<bool(rg_elem_type<Rg>)> t)   { return  detail::find_elem(std::forward<Rg>(C), t); };



////////  Rg % T

//  ---  non callable
	template<typename Rg, typename T>
	eIF <is_range<Rg>::value, bool>
operator % (Rg&& C, const T& t)                               { return  endz(C) != detail::find_elem(std::forward<Rg>(C), t); };

//  ---  plain func
	template<typename Rg>
	eIF <is_range<Rg>::value, bool>
operator % (Rg&& C, bool(*t)(rg_elem_type<Rg>))               { return  endz(C) != detail::find_elem(std::forward<Rg>(C), t); };

//  ---  func obj, lambda
	template<typename Rg>
	eIF <is_range<Rg>::value, bool>
operator % (Rg&& C, std::function<bool(rg_elem_type<Rg>)> t)  { return  endz(C) != detail::find_elem(std::forward<Rg>(C), t); };


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
	eIF <is_stack<Rg>::value, Rg>
operator--      (Rg&& C, int)    { C.pop();   return std::forward<Rg>(C); };

//  Stack >> x
//	scc 'int i=10; (stack<int>() << 1 << 2) >> i;  i'
//	3
//	scc 'int i=10; stack<int> st; st << 1 << 2 << 3;  st >> i; __ st, i;'
//	[1, 2] 3

	template<typename Rg, typename Xt>
	eIF <has_pop<Rg>::value  &&  is_elem_of<Xt,Rg>::value,  Rg>
operator>>      (Rg&& C, Xt&& x)    { x = C.top();  C.pop();   return std::forward<Rg>(C); };


//  Stack++
//	scc ' __ (stack<int>() << 1 << 2 << 3)++;'
//	3
//	scc 'stack<int> st; st << 1 << 2 << 3; st++'
//	3

	template<typename Rg>
 	eIF <has_top<Rg>::value, rg_elem_type<Rg>>
back      (Rg&& C)    { return C.top(); };



/////////////////////////////////////////////////////////////////////////////////////////////////////  QUEUE


//  --Queue
	template<class Rg, class Xt>
	eIF <is_queue<Rg>::value, Rg&&> 
operator--      (Rg&& C)    { C.pop();   return std::forward<Rg>(C); };

//  x << Queue
	template<class Rg, class Xt>
	eIF <has_pop<Rg>::value  &&  is_elem_of<Xt,Rg>::value, Rg&&> &
operator<<      (Xt& x, Rg&& C)    { x = C.front();  C.pop();   return std::forward<Rg>(C); };



/////////////////////////////////////////////////////////////////////////////////////////////////////  ITERATOR


//  It / x   ---  find() --> it	   usage: scc 'copy(+v9/2, +v9/5, oi),  does not work with pointers (C++ constrain)
	template<typename It>
	eIF <is_iterator<It>::value,  It>
operator/       (It&& i, const typename std::iterator_traits<It>::value_type x)    {  while(*i != x) ++i;    return std::forward<It>(i); };


/////////////////////////////////////////////////////////////////////////////////////////////////////  GENERICS 

template<class Rg>	auto operator++(Rg&& rg)      -> decltype(front(rg)) 		{ return front(rg); }
//template<class Rg>	auto operator++(Rg&& rg)      -> decltype(front(rg))&& 		{ return std::forward<rg_reference<Rg>>(front(std::forward<Rg>(rg))); }
template<class Rg>	auto operator++(Rg&& rg, int) -> decltype(back (rg)) 		{ return back (rg); }

					};
					#endif	// STO_STL_H
