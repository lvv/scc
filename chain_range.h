
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

		chain_range&
	operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };

	iterator	begin()		{ return std::begin(rn); };
	iterator	end()		{ return std::end(rn); };
	const_iterator	begin() const	{ return std::begin(rn); };
	const_iterator	end()   const	{ return std::end(rn); };
	size_t		size()  const	{ return ::size(rn); };
	bool		empty() const	{ return ::empty(rn); }

	explicit operator bool  () const { return  (bool) ::size(rn); }

 };


////////////////////////////////////////////////////////////////  RANGE() -- range maker


	template<typename Rn>
	eIF<is_range<Rn>(), chain_range<Rn>>
range(Rn& rn) { return chain_range<Rn>(rn); };


						#endif //  STO_CHAIN_RANGE_H
