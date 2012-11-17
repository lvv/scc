						#ifndef  STO_RANGE_H
						#define  STO_RANGE_H

						#include "scc/numeric_range.h"
						#include "scc/iterator_range.h"
						#include "scc/mapped_range.h"
						#include "scc/predicated_range.h"

						namespace sto {

/////////////////////////////////////////////////////////////////  OPERATORS - FREE FUNCTIONS

				// FIXME: this really should be 2 separate funcs for chain
				// and  numeric to make corresponding includes not to depend on range.h 

////  it - n
	template <class RgI>
	eIF<
		( is_numeric_range_iterator<RgI>::value  ||  is_sto_range_iterator<RgI>::value )
		&&  is_random_access_iterator<RgI>::value
		, rm_ref<decltype(std::declval<RgI>().current-1, std::declval<RgI>())> 
	>  
operator-  (RgI it, typename RgI::difference_type n) {
	it.current-=n;  return std::move(it);
 }


////  it + n
	template <class RgI>
	eIF<
		( is_numeric_range_iterator<RgI>::value  ||  is_sto_range_iterator<RgI>::value )
		&&  is_random_access_iterator<RgI>::value
		, rm_ref<decltype(std::declval<RgI>().current+1, std::declval<RgI>())> 
	>  
operator+  (RgI it, typename RgI::difference_type n) {
	it.current+=n;  return std::move(it);
 }


////  n + it
	template <class RgI>
	eIF<
		( is_numeric_range_iterator<RgI>::value  ||  is_sto_range_iterator<RgI>::value )
		&&  is_random_access_iterator<RgI>::value
		, rm_ref<decltype(1 + std::declval<RgI>().current,  std::declval<RgI>())> 
	>  
operator+  (typename RgI::difference_type n,  RgI it) {
	it.current+=n;  return std::move(it);
 }


////  it - it
	template <class RgI>
	eIF <
		( is_numeric_range_iterator<RgI>::value  ||  is_sto_range_iterator<RgI>::value )
		&&  is_random_access_iterator<RgI>::value
		, rm_ref<decltype(std::declval<RgI>().current - std::declval<RgI>().current,  typename RgI::difference_type())> 
	>  
operator-  (const RgI& it1, const RgI& it2) {
	return it1.current-it2.current;
 }


////////////////////////////////////////////////////////////////////////////////////////////

						}       // sto namespace
						#endif	// STO_RANGE_H
