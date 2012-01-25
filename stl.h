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
struct is_container {	// from http://stackoverflow.com/questions/4347921/sfinae-compiler-troubles
	template <typename U>
	static char test(
		U* u,
		typename U::const_iterator b = ((U*)0)->begin(),
		typename U::const_iterator e = ((U*)0)->end()
	);
	template <typename U> static long test(...);

	enum { value = sizeof test<T>(0) == 1 };
};


template<typename T, size_t N>	struct  is_container <T[N]>		: std::true_type { };
template<typename T, size_t N>	struct  is_container <std::array<T,N>>	: std::true_type { };

/////  IS STRING
template<typename T>	struct  is_string		: std::false_type {};
template<>		struct  is_string <std::string>	: std::true_type  {};


/////////////////////////////////////////////////////////////////////////////////////////  BEGIN/END

//  +Ct / -Ct   ---   end() /begin()
	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator+      (Ct& C) { return begin(C); };

	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, typename Ct::iterator>::type
operator-      (Ct& C) { return  end(C); };

//  !Ct  --- size()
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::size_type>::type
operator!      (const Ct& C) { return C.size(); };	// FIXME: specialization for non-contigues-mem-Ct, C-arr


//  ++Ct / Ct++  ---  front()/back()
	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::reference>::type
operator++      (Ct& C) { return C.front(); };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::reference>::type
operator++      (Ct& C, int) { return C.back(); };


//  x >> Ct << x   ---  push_back/push_front replaement;   usage: scc 'vint V;  V << 1 << 2'   prints: {1, 2}

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct&>::type
operator<<      (Ct& C, typename Ct::value_type x)    { C.push_back(x); return C; };

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, Ct&>::type
operator>>      (typename Ct::value_type x, Ct& C)    { C.push_front(x); return C; };

// --Ct/Ct--  ---  pop_back/pop_front;     usage:   scc 'vint V{1,2}, W;  W << --V;  __ V, W;'   prints:    {2}, {1}

	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::value_type>::type &&
operator--      (Ct& C)         { typename Ct::value_type x = C.front();   C.pop_front();   return  std::move(x); };


	template<typename Ct>
	typename std::enable_if <is_container<Ct>::value, typename Ct::reference>::type &&
operator--      (Ct& C, int)    { typename Ct::value_type x = C.back();    C.pop_back();    return  std::move(x); };

#endif	// LVV_STL_H
