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

template<size_t N> 
const char* endz( const char (&array)[N] ) {return  std::find(array,array+N,'\0');};

/////////////////////////////////////////////////////////////////////////////////////////  MEMBERS ALIASES

//  +Ct   ---   begin(),  	(n/a for c-arrays)
	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator+      (Ct& C) { return std::begin(C); };

//  -Ct   ---   end(),  	(n/a for c-arrays)
	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator-      (Ct& C) { return  std::end(C); };

//  ~Ct  --- size()		(n/a for c-arrays)
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


//   Ct << x   ---  push_back()  replaement;   usage: scc 'vint V;  V << 1 << 2'   prints: {1, 2}
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value   &&   has_push_back<Ct>::value,   Ct&>::type
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.push_back(x);   return C; };


//   Ct << x   ---  insert()  replaement;   usage: scc 'set<int> V;  V << 1 << 2'   prints: {1, 2}
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value   &&   has_insert<Ct>::value,   Ct&>::type
operator<<      (Ct& C, const typename Ct::value_type& x)    { C.insert(x);   return C; };


//  x >> Ct    ---  push_front replaement;   usage: scc 'vint V;  1 >> V'   prints: {1}
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



/*
// Ct1 << Ct2	(works when Ct2 is c-array or c-string)  FIXME:  C1==C2, push_back iter invalidation
	template<typename Ct1, typename Ct2>
	typename std::enable_if <
		is_container<Ct1>::value   &&  is_container<Ct2>::value
			&&  std::is_convertible<typename Ct1::value_type, typename cl_traits<Ct2>::value_type>::value
		, Ct1
	>::type &
operator <<      (Ct1& C1, const Ct2& C2)    { for(auto it=std::begin(C2); it!=endz(C2); ++it) C1.push_back(*it);   return  C1; };

	// Ct1&&
		template<typename Ct1, typename Ct2>
		typename std::enable_if <
			is_container<Ct1>::value   &&  is_container<Ct2>::value
				&&  std::is_convertible<typename Ct1::value_type, typename cl_traits<Ct2>::value_type>::value
			, Ct1
		>::type
	operator <<      (Ct1&& C1, const Ct2& C2)    { for(auto it=std::begin(C2); it!=endz(C2); ++it) C1.push_back(*it);   return  C1; };
*/

	template<typename Ct1, typename Ct2>
	typename std::enable_if <
		is_container<Ct1>::value   &&  is_container<Ct2>::value
		//&&  std::is_convertible<typename std::decay<typename Ct1::value_type>::type, typename std::decay<typename cl_traits<Ct2>::value_type>::type>::value
		&&  std::is_convertible<typename cl_traits<Ct1>::value_type, typename cl_traits<Ct2>::value_type>::value
		//, decltype(std::forward<Ct1>(std::declval<Ct1>()))
		, Ct1
	>::type 
//operator <<      (Ct1&& C1, const Ct2& C2)    { for(auto it=std::begin(std::forward<Ct2>(C2)); it!=endz(std::forward<Ct2>(C2)); ++it) C1.push_back(*it);   return  C1; };
operator <<      (Ct1&& C1, Ct2&& C2)    { for(auto it=std::begin(C2); it!=endz(C2); ++it) C1.push_back(*it);   return  C1; };


// Ct1 >> Ct2
	template<typename Ct1, typename Ct2>
	typename std::enable_if <
		is_container<Ct1>::value  
			&&  is_container<Ct2>::value  
			&&  std::is_same<typename Ct1::value_type, typename Ct2::value_type>::value 
			//&&  std::is_convertible<typename cl_traits<Ct1>::value_type, typename Ct2::value_type>::value 
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




//////////////////////////////////////////////////////////////////////////////////////////////  Ct op T

	template<typename Ct>
	struct ct_op  {

				typedef  typename cl_traits<Ct>::value_type  T;
				typedef  typename cl_traits<Ct>::iterator    It;

		/////  DIV

		// Ct / x     usage: scc 'copy(v9/2, v9/5,oi)'
			template<typename Second>  static
			typename std::enable_if<std::is_same<T, Second>::value, It>::type
		div(Ct& C, const T& x)  { return std::find(C.begin(), C.end(), x); };

		// Ct / f
			template<typename F>  static
			typename std::enable_if <is_callable<F, bool(T)>::value, It>::type
		div(Ct& C, const F& pred)  { return  std::find_if(C.begin(), C.end(), pred); };


		/////  MOD
	
		//  Ct % x   ---  find() --> bool	
			template<typename Second>  static
			typename std::enable_if<std::is_same<Second, T>::value, bool>::type
		mod(const Ct& C, const T& x)    {  return C.cend() != std::find(C.cbegin(), C.cend(), x); };

		// Ct % f
			template<typename F>  static
			typename std::enable_if <is_callable<F, bool(T)>::value, bool>::type
		mod(const Ct& C, const F& pred)  { return  C.cend()  !=  std::find_if(C.cbegin(), C.cend(), pred); };

		
		//  Ct1 % Ct2   ---  search() --> bool	
			template<typename Ct2>  static
			typename std::enable_if <is_container<Ct2>::value  &&  std::is_same<T, typename cl_traits<Ct2>::value_type>::value,  bool>::type
		mod(const Ct& C1, const Ct2& C2)    {  return std::end(C1) != std::search(std::begin(C1), std::end(C1), std::begin(C2), endz(C2)); };

		////// MUL 

			template<typename U>              static T*  ct_resizer(U&  D,  size_t n)  { D.resize(n); return 0; };
			template<typename U,  size_t N>   static void            ct_resizer(U (&D)[N], size_t n)  {}; 

		// Ct * f
			template<typename F>  static
			typename std::enable_if <is_callable<F, T(T)>::value, Ct>::type
		mul(const Ct& C, F f)  {
			Ct D;
			size_t n = std::end(C)-std::begin(C);
			ct_resizer(D, n);

			std::transform(std::begin(C), endz(C), std::begin(D), f);

			// c-string termination
			if (endz(C) < std::end(C))
				* (std::begin(D) + (endz(C) - std::begin(C)) + 0)  = '\0';

			//return  std::move(D);
			return  D;
		};

	};

//  Ct / T   ---  find..() -> it	 
	template<typename Ct, typename Second>
	typename std::enable_if <is_container<Ct>::value , typename Ct::iterator>::type
operator /       (Ct& C, Second x)    {  return  ct_op<Ct>::template div<Second>(C, x); };

//  Ct % T   ---  find..() -> bool	 
	template<typename Ct, typename Second>
	typename std::enable_if <is_container<Ct>::value , bool>::type
operator %       (const Ct& C, const Second& x)    {  return  ct_op<Ct>::template mod<Second>(C, x); };

//  Ct * F   ---  transform(+C,-C,+D,F) -> D
	template<typename Ct, typename Second>
	typename std::enable_if <is_container<Ct>::value , Ct>::type
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
operator~      (const Ct& C)    { return C.size(); };

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
