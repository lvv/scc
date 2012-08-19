#ifndef  STO_RANGE_H
#define  STO_RANGE_H

#include "scc/meta.h"

template<typename T>	struct  	is_range_t			: std::false_type {};
template<typename T>    constexpr bool  is_range()        { return  is_range_t<T>::value; };

#include "scc/numeric_range.h"
#include "scc/iterator_range.h"





/////////////////////////////////////////////////////////////////// RNG -- range proxy
static  __attribute__((unused)) struct range_converter_t {} rng;

	template<typename Ct>
	eIF<
		is_container<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>
operator | (Ct& C, range_converter_t r) { return range(std::begin(C), std::end(C)); };

	template<typename T, size_t N>
	iterator_range<T*>
operator | (T (&C)[N], range_converter_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Ct>
	eIF<
		is_container<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>
operator | (range_converter_t rng, Ct& C) { return range(std::begin(C), std::end(C)); };


/*
static  __attribute__((unused)) struct iot_t {} iot;

	template<typename Ct>
	typename std::enable_if<
		is_container<Ct>(),
		iterator_range<typename container_iterator<Ct>::type>
	>::type
operator | (Ct& C, iot_t r) { return range(std::begin(C), std::end(C)); };
*/

////////////////////////////////////////////////////////////////  RANGE OPS


//  Ct1 | Ct2   ---  search() --> range	   
/*
	template<typename Ct>
	typename std::enable_if <is_container<Ct>(),  iterator_range&>::type
operator |       (Ct& C1, const Ct& C2)    { 
	auto it = search(C1.begin(), C1.end(), C2.begin(), C2.end());
	return  iterator_range(it, advance(it, distance(C2.end(), C2.begin())));
 };

//  Ct1 / Ct2   ---  search() --> it
	template<typename Ct>
	typename std::enable_if <is_container<Ct>(),  typename Ct::iterator>::type
operator /       (Ct& C1, const Ct& C2)    {  return  search(C1.begin(), C1.end(), C2.begin(), C2.end()); };
*/

/////////////////////////////////////////////////////////////////////////////////////  CL TRAITS 
template<typename T>  constexpr bool   is_collection()     {
	return      is_container<T>() 
		||  is_stack<T>() 
		||  is_queue<T>() 
		||  is_range<T>()
	;
 };

template<typename T, typename Ct>     constexpr bool   is_elem_of()        { return  is_collection<Ct>()  &&  std::is_same<rm_ref<T>, rm_ref<cl_elem_type<Ct>>>::value; }
template<typename Ct1, typename Ct2>  constexpr bool   have_same_elem()    { return  is_collection<Ct1>()  &&  is_collection<Ct2>()  &&  std::is_convertible<cl_elem_type<Ct1>,  cl_elem_type<Ct2>>::value; }

#endif	// STO_RANGE_H
