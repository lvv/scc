#ifndef  LVV_META_H
#define  LVV_META_H

#include <type_traits>	 // for META
#include <array>

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

#endif
