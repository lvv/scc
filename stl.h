#ifndef  LVV_STL_H
#define  LVV_STL_H

#include <stddef.h>

#include <algorithm>
#include <iterator>
#include <string>
#include <deque>
#include <tuple>

#include "meta.h"
#include "cpptype.h"

/////////////////////////////////////////////////////////////////////////////////////////////  ENDZ()

// like std::end() but type const char[] is assumed to be C-string and its corresponding correct end (at '\0') is returned

template<typename Ct> 
auto  endz(const Ct& C) -> decltype(std::end(C)) {return std::end(C);};

template<size_t N> auto endz( const char (&array)[N] ) -> decltype(std::end(array)) {return  std::find(array,array+N,'\0');};
template<size_t N> auto endz(       char (&array)[N] ) -> decltype(std::end(array)) {return  std::find(array,array+N,'\0');};

/////////////////////////////////////////////////////////////////////////////////////////  MEMBERS ALIASES

//  +Ct   ---   begin(),  	
	template<typename Ct >
	eIF <is_container<Ct>::value, typename Ct::iterator>
operator+      (Ct& C) { return std::begin(C); };

//  -Ct   ---   end(),  	(n/a for c-arrays, use std::end or endz)
	template<typename Ct >
	eIF <is_container<Ct>::value, typename Ct::iterator>
operator-      (Ct& C) { return  std::end(C); };

//  ~Ct  --- size()		(n/a for c-arrays)
	template<typename Ct>
	eIF <has_size<Ct>::value, size_t>
operator~      (const Ct& C) { return C.size(); };


//  if(!Ct)  --- (!Ct.empty())
//  if(Ct)   --- not implemented,  use  !!Ct instead
	template<typename Ct>
	eIF <has_empty<Ct>::value, bool>
operator!      (const Ct& C) { return C.empty(); };


//  ++T / T++  ---  front()/back()/.first/.second  (n/a for c-arrays)

	template<typename Ct>
	eIF <is_container<Ct>::value, typename Ct::reference>
operator++      (Ct& C) { return C.front(); };
//	template<typename Ct>
//	eIF <is_container<Ct>::value, cl_reference<Ct&&>>
//operator++      (Ct&& C) { return std::forward<cl_reference<Ct&&>>(C.front()); };


	template<typename Ct>
	eIF <is_container<Ct>::value, typename Ct::reference>
operator++      (Ct& C, int) { return C.back(); };


//   Ct << x   ---  push_back()  replaement;   usage: scc 'vint V;  V << 1 << 2'   prints: {1, 2}
	template<typename Ct>
	eIF <is_container<Ct>::value   &&   has_push_back<Ct>::value,   Ct>
operator<<      (Ct&& C, typename cl_traits<Ct>::value_type&& x)    { C.push_back(x);   return C; };


//   Set << x   ---  insert()  replaement;   usage: scc 'set<int> V;  V << 1 << 2'   prints: {1, 2}
	template<typename Ct>
	eIF <is_container<Ct>::value   &&   has_insert<Ct>::value,   Ct>
operator<<      (Ct&& C, typename cl_traits<Ct>::value_type&& x)    { C.insert(x);   return std::forward<Ct>(C); };


//  x >> Ct    ---  push_front replaement;   usage: scc 'vint V;  1 >> V'   prints: {1}
	template<typename Ct>
	eIF <is_container<Ct>::value   &&   has_push_front<Ct>::value,   Ct>
operator>>      (typename cl_traits<Ct>::value_type&& x, Ct&& C)    { C.push_front(x);  return std::forward<Ct>(C); };


//  x << Ct >> x   ---  remove head / tail;   usage: scc 'dlong V{1,2,3};  i << V >> j; __ i, V, j;'   prints: 1 {2} 3 
	template<typename Ct>
	eIF <is_container<Ct>::value   &&   has_pop_back<Ct>::value, Ct>
operator>>      (Ct&& C, typename cl_traits<Ct>::value_type& x)    { x = C.back();   C.pop_back();   return  std::forward<Ct>(C); };

	template<typename Ct>
	eIF <is_container<Ct>::value   &&   has_pop_front<Ct>::value, Ct>
operator<<      (typename cl_traits<Ct>::value_type& x, Ct&& C)    { x = C.front();  C.pop_front();  return  std::forward<Ct>(C); };

// Set << Ct 
	template<typename Ct1, typename Ct2>
	eIF <has_insert<Ct1>::value   &&  is_container<Ct2>::value   &&  is_cl2cl_convertible<Ct1,Ct2>::value,   Ct1>
operator <<      (Ct1&& C1, const Ct2& C2)    {
	for(auto it = std::begin(C2);   it!=endz(C2);   ++it)
		C1.insert(*it);  
	return  std::forward<Ct1>(C1);
};



// Ct1 << Ct2
	template<typename Ct1, typename Ct2>
	eIF <has_push_back<Ct1>::value   &&  is_container<Ct2>::value   &&  is_cl2cl_convertible<Ct1,Ct2>::value,  Ct1>	// RVO: no coping for T& or T&&
operator <<      (Ct1&& C1, const Ct2& C2)    {

	// Move - works for trace_obj, not for const char[].  Needs cl_traits<Ct>::move_iterator
	//for(auto it = std::make_move_iterator(std::begin(C2));   it!=std::make_move_iterator(endz(C2));   ++it)
	
	for(auto it = std::begin(C2);   it!=endz(C2);   ++it)
		C1.push_back(*it);  
	return  std::forward<Ct1>(C1);
};


// Ct1 >> Ct2			// TOFIX:  self-assigment
	template<typename Ct1, typename Ct2>
	eIF <is_container<Ct1>::value   &&  has_push_front<Ct2>::value   &&  is_cl2cl_convertible<Ct1,Ct2>::value,  Ct2>
operator >>      (const Ct1& C1, Ct2&& C2)    { auto it = endz(C1); while(it-- != std::begin(C1)) C2.push_front(*it);  return C2; };


// --Ct/Ct--  ---  pop_back/pop_front;     usage:   scc 'vint V{1,2}, W;  W << --V;  __ V, W;'   prints:    {2}, {1}
	template<typename Ct>
	eIF <is_container<Ct>::value, Ct>
operator--      (Ct&& C)         { C.pop_front();   return  std::forward<Ct>(C); };


	template<typename Ct>
	eIF <is_container<Ct>::value, Ct>
operator--      (Ct&& C, int)    { C.pop_back();    return  std::forward<Ct>(C); };




//////////////////////////////////////////////////////////////////////////////////////////////  Ct op T

	template<typename Ct>
	struct ct_op  {

				typedef  typename cl_traits<Ct>::value_type  T;
				typedef  typename cl_traits<Ct>::iterator    It;

		/////  DIV

		// Ct / x     usage: scc 'copy(v9/2, v9/5,oi)'
			template<typename Second>  static
			eIF <std::is_same<T, Second>::value, It>
		div(Ct& C, const T& x)  { return std::find(C.begin(), C.end(), x); };


		// Ct / f
			template<typename F>  static
			eIF <is_callable<F, bool(T)>::value, It>
		div(Ct& C, const F& pred)  { return  std::find_if(C.begin(), C.end(), pred); };


		/////  MOD
	
		//  Ct % x   ---  find() --> bool	
			template<typename Second>  static
			eIF<std::is_same<Second, T>::value, bool>
		mod(const Ct& C, const T& x)    {  return C.cend() != std::find(C.cbegin(), C.cend(), x); };


		// Ct % f
			template<typename F>  static
			eIF <is_callable<F, bool(T)>::value, bool>
		mod(const Ct& C, const F& pred)  { return  C.cend()  !=  std::find_if(C.cbegin(), C.cend(), pred); };

			
		//  Ct1 % Ct2   ---  search() --> bool	
			template<typename Ct2>  static
			eIF <is_container<Ct2>::value  &&  std::is_same<T, typename cl_traits<Ct2>::value_type>::value,  bool>
		mod(const Ct& C1, const Ct2& C2)    {  return std::end(C1) != std::search(std::begin(C1), std::end(C1), std::begin(C2), endz(C2)); };


		////// MUL 

			template<typename U>              static eIF< has_resize<U>::value>  ct_resizer(U& D,      size_t n)  { D.resize(n);};
			template<typename U>              static eIF<!has_resize<U>::value>  ct_resizer(U& D,      size_t n)  {};
			template<typename U,  size_t N>   static void                        ct_resizer(U (&D)[N], size_t n)  {}; 


		// Ct * f  (temporary demo, should really return  collection, not a container)
			template<typename F>  static
			eIF <is_callable<F, T(T)>::value, Ct>
		mul(const Ct& C, F f)  {
			Ct D;
			size_t n = std::end(C)-std::begin(C);
			ct_resizer(D, n);

			std::transform(std::begin(C), endz(C), std::begin(D), f);

			// c-string termination
			if (endz(C) < std::end(C))
				* (std::begin(D) + (endz(C) - std::begin(C)) + 0)  = '\0';

			return  D;
		};

	};

//  Ct / T   ---  find..() -> it	 
	template<typename Ct, typename Second>
	eIF <is_container<Ct>::value , typename Ct::iterator>
operator /       (Ct& C, Second x)    {  return  ct_op<Ct>::template div<Second>(C, x); };

//  Ct % T   ---  find..() -> bool	 
	template<typename Ct, typename Second>
	eIF <is_container<Ct>::value , bool>
operator %       (const Ct& C, const Second& x)    {  return  ct_op<Ct>::template mod<Second>(C, x); };

//  Ct * F   ---  transform(+C,-C,+D,F) -> D
	template<typename Ct, typename Second>
	eIF <is_container<Ct>::value , Ct>
operator *       (const Ct& C, const Second& x)    {  return  ct_op<Ct>::template mul<Second>(C, x); };


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
	template<typename Ct, typename Xt>
	eIF <is_stack<Ct>::value  &&  is_x2cl_convertible<Ct,Xt>::value,  Ct>
operator<<      (Ct&& C, Xt&& x)    { C.push(std::forward<Xt>(x));   return std::forward<Ct>(C); };

//  Stack--
	template<typename Ct>
	eIF <is_stack<Ct>::value, Ct>
operator--      (Ct&& C, int)    { C.pop();   return std::forward<Ct>(C); };

//  Stack >> x
//	scc 'int i=10; (stack<int>() << 1 << 2) >> i;  i'
//	3
//	scc 'int i=10; stack<int> st; st << 1 << 2 << 3;  st >> i; __ st, i;'
//	[1, 2] 3

	template<typename Ct, typename Xt>
	eIF <is_stack<Ct>::value  &&  is_x2cl_convertible<Ct,Xt>::value, Ct>
operator>>      (Ct&& C, Xt&& x)    { x = C.top();  C.pop();   return std::forward<Ct>(C); };


//  Stack++
//	scc ' __ (stack<int>() << 1 << 2 << 3)++;'
//	3
//	scc 'stack<int> st; st << 1 << 2 << 3; st++'
//	3

	template<typename Ct>
 	//eIF <is_stack<Ct>::value, typename Ct::value_type>
 	eIF <is_stack<Ct>::value, cl_value_type<Ct>>
operator++      (Ct&& C, int)    { return C.top(); };



/////////////////////////////////////////////////////////////////////////////////////////////////////  QUEUE

//  Queue << x
	template<typename Ct>
	eIF <is_queue<Ct>::value, Ct> &
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.push(x);   return C; };

//  --Queue
	template<typename Ct>
	eIF <is_queue<Ct>::value, Ct> &
operator--      (Ct& C)    { C.pop();   return C; };

//  x << Queue
	template<typename Ct>
	eIF <is_queue<Ct>::value, typename Ct::value_type> &
operator<<      (typename Ct::value_type& x, Ct& C)    { x = C.front();  C.pop();   return x; };


//  Queue++
	template<typename Ct>
	eIF <is_queue<Ct>::value, typename Ct::value_type> &
operator++      (Ct& C, int)    { return C.back(); };

//  ++Queue
	template<typename Ct>
	eIF <is_queue<Ct>::value, typename Ct::value_type> &
operator++      (Ct& C)    { return C.front(); };

//  !Queue
	template<typename Ct>
	eIF <is_queue<Ct>::value, size_t>
operator~      (const Ct& C)    { return C.size(); };


/////////////////////////////////////////////////////////////////////////////////////////////////////  ITERATOR


//  It / x   ---  find() --> it	   usage: scc 'copy(+v9/2, +v9/5, oi),  does not work with pointers (C++ constrain)
	template<typename It>
	eIF <is_iterator<It>::value,  It>
operator/       (It&& i, const typename std::iterator_traits<It>::value_type x)    {  while(*i != x) ++i;    return std::forward<It>(i); };

/*
	template<typename It, typename Ct>
	eIF <is_iterator<It>::value,  It>
operator <<       (It&& it, Ct&& C)    {};
*/


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
