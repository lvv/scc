						#ifndef  STO_RANGE_H
						#define  STO_RANGE_H

						#include "scc/numeric_range.h"
						#include "scc/iterator_range.h"
						#include "scc/chain_range.h"

						namespace sto {

/*
/////////////////////////////////////////////////////////////////// RNG -- range proxy

static  __attribute__((unused)) struct range_converter_t {} rng;

	template<typename Rg>
	eIF<
		is_range<Rg>::value,
		iterator_range<rg_iterator<Rg>>
	>
operator | (Rg& C, range_converter_t r) { return range(std::begin(C), std::end(C)); };

	template<typename T, size_t N>
	iterator_range<T*>
operator | (T (&C)[N], range_converter_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Rg>
	eIF<
		is_range<Rg>::value,
		iterator_range<rg_iterator<Rg>>
	>
operator | (range_converter_t rng, Rg& C) { return range(std::begin(C), std::end(C)); };
*/

/*
static  __attribute__((unused)) struct iot_t {} iot;

	template<typename Rg>
	typename std::enable_if<
		is_range<Rg>::value,
		iterator_range<rg_iterator<Rg>>
	>::type
operator | (Rg& C, iot_t r) { return range(std::begin(C), std::end(C)); };
*/

/////////////////////////////////////////////////////////////////////////////////////  CL TRAITS 

						}
						#endif	// STO_RANGE_H
