
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include "meta.h"
						namespace sto {

/////////////////////////////////////////////////////////////////////////////////////////  ITERATOR_RANGE

	template<typename Rn>
struct  chain_range {

		typedef		cl_iterator<Rn>							iterator;
		typedef		cl_const_iterator<Rn>						const_iterator;
		typedef		cl_elem_type<Rn>  						value_type;
		typedef		typename std::iterator_traits<iterator>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<iterator>::pointer		pointer ;
		typedef		typename std::iterator_traits<iterator>::reference		reference ;

	Rn& rn;

	// CTOR
	chain_range(Rn& rn)  : rn(rn) {};
	chain_range&   operator= (value_type v) { for(auto& el: *this) el = v;  return *this; };

	// ITERATOR
	iterator	begin()		{ return std::begin(rn); }
	iterator	end()		{ return std::end(rn); }
	const_iterator	begin() const	{ return std::begin(rn); }
	const_iterator	end()   const	{ return std::end(rn); }


	// CT MANAGMENT
	size_t		size  () const	{ return  sto::size (rn); }
	bool		empty () const	{ return  sto::empty(rn); }
	explicit operator bool() const	{ return !sto::empty(rn); }


	// ELEM ACCESS
	
	value_type  	front()  const	{ return  *std::begin(rn); }  
	reference  	front()		{ return  *std::begin(rn); }  

	value_type  	back()  const	{ return  *(std::prev(sto::endz(rn))); }  
	reference  	back()		{ return  *(std::prev(sto::endz(rn))); }  

	// CT MOD
	/*
	eIF<has_push_back<Rn>()>	push_back( const value_type& value)	{rn.push_back(value);}
	eIF<has_push_back<Rn>()>	push_back( value_type&& value)		{rn.push_back(std::move(value));}
	
	eIF<has_push_front<Rn>()>	push_front( const value_type& value)	{rn.push_front(value);}
	eIF<has_push_front<Rn>()>	push_front( value_type&& value)		{rn.push_front(std::move(value));}
	
	eIF<has_1arg_insert<Rn>()>	insert( const value_type& value)	{rn.insert(value);}
	eIF<has_1arg_insert<Rn>()>	insert( value_type&& value)		{rn.insert(std::move(value));}
	*/
 };


////////////////////////////////////////////////////////////////  RANGE() -- range maker


	template<typename Rn>
	eIF<is_range<Rn>(), chain_range<Rn>>
range(Rn& rn) { return chain_range<Rn>(rn); };


						}; 
						#endif //  STO_CHAIN_RANGE_H
