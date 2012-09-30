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
		iterator_range<rn_iterator<Ct>>
	>
operator | (Ct& C, range_converter_t r) { return range(std::begin(C), std::end(C)); };

	template<typename T, size_t N>
	iterator_range<T*>
operator | (T (&C)[N], range_converter_t r) { return range(std::begin(C), std::end(C)); };


	template<typename Ct>
	eIF<
		is_range<Ct>(),
		iterator_range<rn_iterator<Ct>>
	>
operator | (range_converter_t rng, Ct& C) { return range(std::begin(C), std::end(C)); };
*/

/*
static  __attribute__((unused)) struct iot_t {} iot;

	template<typename Ct>
	typename std::enable_if<
		is_range<Ct>(),
		iterator_range<rn_iterator<Ct>>
	>::type
operator | (Ct& C, iot_t r) { return range(std::begin(C), std::end(C)); };
*/

/////////////////////////////////////////////////////////////////////////////////////  CL TRAITS 

						}
						#endif	// STO_RANGE_H
