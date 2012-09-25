						#ifndef  STO_RANGE_H
						#define  STO_RANGE_H

						#include "scc/numeric_range.h"
						#include "scc/iterator_range.h"
						#include "scc/chain_range.h"

						namespace sto {

/*
/////////////////////////////////////////////////////////////////// RNG -- range proxy

static  __attribute__((unused)) struct range_converter_t {} rng;

	template<typename Ct>
	eIF<
		is_range<Ct>(),
		iterator_range<cl_iterator<Ct>>
	>
operator | (Ct& C, range_converter_t r) { return range(std::begin(C), std::end(C)); };

	template<typename T, size_t N>
	iterator_range<T*>
operator | (T (&C)[N], range_converter_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Ct>
	eIF<
		is_range<Ct>(),
		iterator_range<cl_iterator<Ct>>
	>
operator | (range_converter_t rng, Ct& C) { return range(std::begin(C), std::end(C)); };
*/

/*
static  __attribute__((unused)) struct iot_t {} iot;

	template<typename Ct>
	typename std::enable_if<
		is_range<Ct>(),
		iterator_range<cl_iterator<Ct>>
	>::type
operator | (Ct& C, iot_t r) { return range(std::begin(C), std::end(C)); };
*/

////////////////////////////////////////////////////////////////  RANGE OPS


//  Ct1 | Pred    --> range	 (grep like)
	//template<class Rn, class Pred = bool(*)(const cl_elem_type<Rn>&)>
//operator|  (Rn&& rn,  identity<Pred> pred)    { 
//operator|  (Rn&& rn,  bool(*)(const cl_elem_type<Rn>&) pred)    { 
template<class Rn> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator|  (Rn&& rn,  std::function<bool(const cl_elem_type<Rn>&)> pred)  { return  chain_range<Rn&&>(std::forward<Rn>(rn), pred); };
template<class Rn> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator|  (Rn&& rn,  bool(pred)(const cl_elem_type<Rn>&))  { return  chain_range<Rn&&>(std::forward<Rn>(rn), pred); };
template<class Rn> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator|  (Rn&& rn,  bool(pred)(cl_elem_type<Rn>))  { return  chain_range<Rn&&>(std::forward<Rn>(rn), pred); };

//  Ct1 | Ct2   ---  search() --> range	   
/*
	template<typename Ct>
	typename std::enable_if <is_range<Ct>(),  iterator_range&>::type
operator |       (Ct& C1, const Ct& C2)    { 
	auto it = search(C1.begin(), C1.end(), C2.begin(), C2.end());
	return  iterator_range(it, advance(it, distance(C2.end(), C2.begin())));
 };

//  Ct1 / Ct2   ---  search() --> it
	template<typename Ct>
	typename std::enable_if <is_range<Ct>(),  typename Ct::iterator>::type
operator /       (Ct& C1, const Ct& C2)    {  return  search(C1.begin(), C1.end(), C2.begin(), C2.end()); };
*/

/////////////////////////////////////////////////////////////////////////////////////  CL TRAITS 

						}
						#endif	// STO_RANGE_H
