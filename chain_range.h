
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include "meta.h"

/////////////////////////////////////////////////////////////////////////////////////////  ITERATOR_RANGE

	template<typename Rn>
struct  chain_range {

		Rn& rn;

	// CTOR
	chain_range(Rn& rn)  : rn(rn) {};

		typedef		cl_iterator<Rn>							iterator;
		typedef		cl_const_iterator<Rn>						const_iterator;
		typedef		cl_elem_type<Rn>  						value_type;
		typedef		typename std::iterator_traits<iterator>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<iterator>::pointer		pointer ;
		typedef		typename std::iterator_traits<iterator>::reference		reference ;


	iterator	begin()		{ return std::begin(rn); };
	iterator	end()		{ return std::end(rn); };
	const_iterator	begin() const	{ return std::begin(rn); };
	const_iterator	end()   const	{ return std::end(rn); };
	size_t		size()  const	{ return ::size(rn); };

		chain_range&
	operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };


	//explicit operator bool  (eIF<has_empty<Rn>(), int*> not_used=0) const { return rn.empty(); }
	explicit operator bool  () const { return  (bool) ::size(rn); }
	//explicit operator eIF<has_empty<Rn>(), bool>  () const { return rn.empty(); }

	bool empty() const { return (bool) ::size(rn); }

 };


////////////////////////////////////////////////////////////////  RANGE() -- range maker


//  container wrapper range
	template<typename Rn>
	eIF<is_range<Rn>(), chain_range<Rn>>
range(Rn& rn) { return chain_range<Rn>(rn); };

//template<typename T, size_t N> chain_range<T(&)[N]>          range(T          (&C)[N]) { return chain_range<T   (&)[N]>      (C); };
//template<            size_t N> chain_range<char(&)[N]>       range(char       (&C)[N]) { return chain_range<char(&)[N]>      (C); };
//template<            size_t N> chain_range<const char(&)[N]> range(const char (&C)[N]) { return chain_range<const char(&)[N]>(C); };


						#endif //  STO_CHAIN_RANGE_H
