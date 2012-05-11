#ifndef  LVV_STL_H
#define  LVV_STL_H

#include <stddef.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <deque>
#include <tuple>


#include "meta.h"
//#include "traits.hpp"

/////////////////////////////////////////////////////////////////////////////////////////  MEMBERS ALIASES

//  +Ct / -Ct   ---   end() /begin()
	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator+      (Ct& C) { return std::begin(C); };

	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator-      (Ct& C) { return  std::end(C); };

//  ~Ct  --- size()
	template<typename Ct>
	typename std::enable_if <has_size<Ct>::value, size_t>::type
operator~      (const Ct& C) { return C.size(); };



//  if(!Ct)  --- (!Ct.empty())
//  if(Ct)   --- not implemented,  use  !!Ct instead
	template<typename Ct>
	typename std::enable_if <has_empty<Ct>::value, bool>::type
operator!      (const Ct& C) { return C.empty(); };



//  ++T / T++  ---  front()/back()/.first/.second
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::reference>::type
operator++      (Ct& C) { return C.front(); };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::reference>::type
operator++      (Ct& C, int) { return C.back(); };

//  x >> Ct << x   ---  push_back/push_front replaement;   usage: scc 'vint V;  V << 1 << 2'   prints: {1, 2}
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value   &&   has_push_back<Ct>::value,   Ct&>::type
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.push_back(x);   return C; };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value   &&   has_insert<Ct>::value,   Ct&>::type
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.insert(x);   return C; };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value   &&   has_push_front<Ct>::value,   Ct>::type &
operator>>      (const typename Ct::value_type x, Ct& C)    { C.push_front(x);  return C; };


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
			&&  std::is_convertible<typename Ct1::value_type, typename Ct2::value_type>::value
		, Ct1
	>::type &
operator <<      (Ct1& C1, const Ct2& C2)    { for(auto x: C2) C1.push_back(x);   return  C1; };

// Ct1 << T[N]
	template<typename Ct1, /*typename T,*/ size_t N>
	typename std::enable_if <
		is_container<Ct1>::value  
			&&   has_push_back<Ct1>::value
			/*&&  std::is_convertible<typename Ct1::value_type, T>::value*/, 
	Ct1 >::type &
operator <<      (Ct1& C, const typename Ct1::value_type (&A)[N])    {  for(auto x: A) C.push_back(x);   return  C; };


// Ct1 << const char[N]
	template<typename Ct1, size_t N>
	typename std::enable_if <
		is_container<Ct1>::value  
			&&   has_push_back<Ct1>::value
			&&  std::is_convertible<typename Ct1::value_type, char>::value, 
	Ct1 >::type &
operator <<      (Ct1& C, const char (&A)[N])    {  auto p=A;  while(*p)  C.push_back(*p++);   return  C; };


// Ct1 >> Ct2
	template<typename Ct1, typename Ct2>
	typename std::enable_if <
		is_container<Ct1>::value  
			&&  is_container<Ct2>::value  
			&&  std::is_same<typename Ct1::value_type, typename Ct2::value_type>::value 
			&&  has_push_front<Ct2>::value,
	 Ct2 >::type &
operator >>      (const Ct1& C1, Ct2& C2)    { std::copy(C1.rbegin(), C1.rend(), std::front_inserter(C2));  return C2; };


// --Ct/Ct--  ---  pop_back/pop_front;     usage:   scc 'vint V{1,2}, W;  W << --V;  __ V, W;'   prints:    {2}, {1}
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct>::type &
operator--      (Ct& C)         { C.pop_front();   return  C; };


	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct>::type &
operator--      (Ct& C, int)    { C.pop_back();    return  C; };



/////////////////////////////////////////////////////////////////////////////////////////////////////  SEARCH

/*
//  Ct / F(x)   ---  find() --> it	   usage: scc 'copy(v9/2, v9/5,oi)'
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value,  typename Ct::iterator>::type
operator /       (Ct& C,  typename std::function<bool(typename Ct::value_type)> F)    {  return  std::find_if(C.begin(), C.end(), F); };
*/

/************************************************************************
		template<typename F,typename R,typename A1>
	void do_stuff(F& f,R (F::*mf)(A1) const) {
	    (f.*mf)(99);
	}

	template<typename F>
void do_stuff(F f) {
    do_stuff(f,&F::operator());
}
***************************************************************************/

//  Ct / F(x)   ---  find() --> it	   usage: scc 'copy(v9/2, v9/5,oi)'
//
			template<typename Ct, typename FCT>
			typename Ct::iterator
	op_div       (Ct& C,  FCT& fct, bool (FCT::*mf)(const typename Ct::value_type&) const)    { 
		return  std::find_if(C.begin(), C.end(), (fct.*mf));
	};


		template<typename Ct, typename LAMB>
		typename std::enable_if <is_container<Ct>::value,  typename Ct::iterator>::type
operator /       (Ct& C,  LAMB l)    { 
	return  op_div<Ct,LAMB>(C, l, &LAMB::operator()) ;
 };


//  Ct / F(x)   ---  find() --> it	   usage: scc 'copy(v9/2, v9/5,oi)'
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value,  typename Ct::iterator>::type
operator /       (Ct& C,  typename std::function<bool(typename Ct::value_type)> F)    {  return  std::find_if(C.begin(), C.end(), F); };


//  Ct / x   ---  find() --> it	   usage: scc 'copy(v9/2, v9/5,oi)'
	template<typename Ct>
	typename std::enable_if < is_container<Ct>::value , typename Ct::iterator >::type
operator /       (Ct& C, const typename Ct::value_type& x)    {  return std::find(C.begin(), C.end(), x); };



//  Ct % x   ---  find() --> bool	
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value,  bool>::type
operator %       (const Ct& C, const typename Ct::value_type& x)    {  return C.cend() != std::find(C.cbegin(), C.cend(), x); };


//  Ct1 % Ct2   ---  search() --> bool	
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value,  bool>::type
operator %       (const Ct& C1, const Ct& C2)    {  return C1.end() != std::search(C1.begin(), C1.end(), C2.begin(), C2.end()); };


/*
//  Ct /= x   ---  find() --> *it	   usage: scc 'v9 /= 3 = 33; v9'
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value,  typename Ct::value_type&>::type
operator /=       (Ct& C, const typename Ct::value_type& x)    { 
	auto it = find(C.begin(), C.end(), x);
	if (it == C.end()) {
		C.push_back(typename Ct::value_type());
		return C.back();
	}
	return *it;
};
*/




/////////////////////////////////////////////////////////////////////////////////////////////////////  TUPLE / PAIR

template<typename U, typename V>   U&     operator++   (std::pair<U,V>& P)      { return P.first;  };
template<typename U, typename V>   V&     operator++   (std::pair<U,V>& P, int) { return P.second; };

	template <class... Types>
	typename std::tuple_element<std::tuple_size<std::tuple<Types...> >::value-1, typename std::tuple<Types...> >::type&
operator++	(typename std::tuple<Types...>& Tpl, int)  {  return  std::get<std::tuple_size<std::tuple<Types...> >::value-1>(Tpl); };


	template <class... Types>
	typename std::tuple_element<0, std::tuple<Types...> >::type&
operator++	(typename std::tuple<Types...>& Tpl)  {  return  std::get<0>(Tpl); };

	template <class... Types>
	constexpr size_t
operator~	(const typename std::tuple<Types...>& Tpl)  {  return  std::tuple_size<std::tuple<Types...> >::value; };


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


/////////////////////////////////////////////////////////////////////////////////////////////////////  QUEUE

//  Queue << x
	template<typename Ct>
	typename std::enable_if <is_queue<Ct>::value, Ct&>::type&
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.push(x);   return C; };

//  --Queue
	template<typename Ct>
	typename std::enable_if <is_queue<Ct>::value, Ct&>::type&
operator--      (Ct& C)    { C.pop();   return C; };

//  x << Queue
	template<typename Ct>
	typename std::enable_if <is_queue<Ct>::value, typename Ct::value_type&>::type&
operator<<      (typename Ct::value_type& x, Ct& C)    { x = C.front();  C.pop();   return x; };

//  Queue++
	template<typename Ct>
	typename std::enable_if <is_queue<Ct>::value, typename Ct::value_type&>::type&
operator++      (Ct& C, int)    { return C.back(); };

//  ++Queue
	template<typename Ct>
	typename std::enable_if <is_queue<Ct>::value, typename Ct::value_type&>::type&
operator++      (Ct& C)    { return C.front(); };

//  !Queue
	template<typename Ct>
	typename std::enable_if <is_queue<Ct>::value, size_t>::type
operator~      (Ct& C)    { return C.size(); };

/////////////////////////////////////////////////////////////////////////////////////////////////////  ITERATOR


//  It / x   ---  find() --> it	   usage: scc 'copy(+v9/2, +v9/5, oi),  does not work with pointers (C++ constrain)
	template<typename It>
	typename std::enable_if <is_iterator<It>::value,  It>::type
operator/       (It i, const typename std::iterator_traits<It>::value_type x)    {  while(*i != x) ++i;    return i; };


/////////////////////////////////////////////////////////////////////////////////////////////////////  

namespace x {  // eXperimental

// waiting for implementation of Inherited Ctor-s -- http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2540.htm
template<typename T>
struct vector : std::vector<T> {

	/* to bool conversion -- */
			struct PointerConversion { int valid; };
			typedef int PointerConversion::* datamemptr;

	operator datamemptr  () const {
		return  this->empty() ? &PointerConversion::valid : 0;
	};
};

} // x namespace

#endif	// LVV_STL_H
