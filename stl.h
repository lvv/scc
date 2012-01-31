#ifndef  LVV_STL_H
#define  LVV_STL_H

#include <stddef.h>

#include <type_traits>	 // for META
#include <string>
#include <deque>

/////////////////////////////////////////////////////////////////////////////////////////  CONTAINER MANIP


/////////////////////////////////////////////////////////////////////////////////////////  META


///// IS_CONTAINER

	template <typename T>
struct is_container {
	template <typename U, typename S = decltype (((U*)0)->size()), typename I = typename U::const_iterator>
	static char test(U* u);
	template <typename U> static long test(...);
	enum { value = sizeof test<T>(0) == 1 };
};



template<typename T, size_t N>	struct  is_container <T[N]>		: std::true_type { };
template<typename T, size_t N>	struct  is_container <std::array<T,N>>	: std::true_type { };

/////  IS STRING
template<typename T>	struct  is_string		: std::false_type {};
template<>		struct  is_string <std::string>	: std::true_type  {};


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


// Ct1 <<= Ct2
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

#endif	// LVV_STL_H
