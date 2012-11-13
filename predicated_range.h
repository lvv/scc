
						#ifndef  STO_PREDICATED_RANGE_H
						#define  STO_PREDICATED_RANGE_H

						#include "scc/basic_range.h"

						namespace sto {

	// forward dcl
	template< class Rg, class F = void*>  struct  predicated_range;

/////////////////////////////////////////////////////////////////////////////////////////  PREDICATED_RANGE_ITERATOR

	template <class Rg, class F, bool RO>
struct predicated_range_iterator : basic_range_iterator<Rg,RO> {

	typedef   basic_range_iterator<Rg,RO>  b;

	typedef	SEL <
		RO,
		predicated_range<Rg,F> const,
		predicated_range<Rg,F>
	>  parent_t;

	//parent_t * const & parent_p = (parent_t*)(b::parent_p);

	// STL ITERATOR TYPES
	typedef		typename parent_t::iterator		iterator;
	typedef		typename parent_t::const_iterator	const_iterator;
	typedef		rm_ref<predicated_range_iterator>		self_type;

	typedef		typename b::iterator_category 		iterator_category;
	typedef		typename b::org_iterator 		org_iterator;
	typedef		typename parent_t::value_type		value_type;

	using							typename b::size_type;
	using							typename b::difference_type;
	using							typename b::pointer;

	typedef         rg_const_reference<Rg>			const_reference;

	typedef		typename std::conditional <
				std::is_const<Rg>::value || RO,
				rg_const_reference<Rg>,
				rg_reference<Rg>
			>::type					reference;


	// non-STL
	using 							typename b::elem_type;

	////// MEMBERS

	
	////// CTOR
	predicated_range_iterator (const self_type& rhs)				: b(rhs)  		{};  // copy 
	predicated_range_iterator (parent_t* parent_p,  const org_iterator current)	: b(parent_p, current)	{};


	////// CONVERSION  non-const --> const
	//operator predicated_range_iterator<Rg&&,F,true>() { return predicated_range_iterator<Rg&&,F,true>(parent_p, b::current); };
	operator predicated_range_iterator<Rg&&,F,true>() { return predicated_range_iterator<Rg&&,F,true>((parent_t*)b::parent_p, b::current); };

	////// IFACE
	reference	operator*()  		{ return  *b::current; };
	const_reference operator*() const 	{ return  *b::current; };

	pointer		operator->()		{ return  &(operator*()); }
	pointer	const 	operator->() const	{ return  &(operator*()); }

	// ++ It
	self_type&	operator++()		{ move_pos();  return *this; }

	// ++ It

	self_type	operator++(int)		{
		org_iterator e = endz(b::parent_p->rg);    assert(b::current !=e);
		self_type tmp=*this;
		move_pos();
		return std::move(tmp);
	}


	bool		operator==(const_iterator rhs)	const	{ return   b::current == rhs.current; }
	bool		operator!=(const_iterator rhs)	const	{ return   b::current != rhs.current; }

	///////////////////////////////////////////////////////////////////// INPORT ORG_ITERATOR METHODS
	
	/*
	//  bidiractional 
	using 		b::operator--;		// TOFIX
	                                                          
	// random access
	using		b::operator+=;		// TOFIX
	using		b::operator-=;		// TOFIX
	using		b::operator[];		// TOFIX
	using		b::operator<;
	using		b::operator<=;
	using		b::operator>;
	using		b::operator>=;
	*/


	void	move_pos()	{	// move current pos 
		org_iterator e = endz(b::parent_p->rg);
		assert(b::current !=e);
	
		b::current = std::find_if(++b::current, e, ((parent_t*)b::parent_p)->f);
	}

 };



/////////////////////////////////////////////////////////////////////////////////////////  PREDICATED_RANGE
	template<class Rg, class F>
struct  predicated_range : basic_range<Rg> {

	typedef   basic_range<Rg>  b;

	// STL IFACE
	typedef		rg_elem_type<Rg>				value_type;
	typedef		predicated_range_iterator<Rg,F,false>    		iterator;
	typedef		predicated_range_iterator<Rg,F,true>		const_iterator;

	typedef		size_t  					size_type;
	typedef		ptrdiff_t 					difference_type ;
	typedef		rm_ref<value_type>*				pointer;

	typedef         rg_const_reference<Rg>     const_reference;  // non-STL
	typedef		typename std::conditional <
				std::is_const<Rg>::value /* || RO*/,      // <-- different from interator
				rg_const_reference<Rg>,
				rg_reference<Rg>
			 >::type 					reference;

	// non-STL
	typedef		rg_elem_type<Rg>  				elem_type;
	typedef		predicated_range					self_type;


	// MEMBERS
	F f;

	////  CTOR 
	explicit predicated_range (Rg&& rg, F f) :   b(std::forward<Rg>(rg)),   f(f) {};


	////  ASSIGNMENT
	using b::operator=;


	////  ITERATOR
	      iterator	end()		{ return        iterator(this, endz(b::rg)); }
	const_iterator	end()   const	{ return  const_iterator(this, endz(b::rg)); }

	      iterator	begin()		{ return        iterator(this, std::find_if(std::begin(b::rg), endz(b::rg), f)); };
	const_iterator	begin()	const	{ return  const_iterator(this, std::find_if(std::begin(b::rg), endz(b::rg), f)); };


	////  RG PROPERTIES
	size_type	size  () const	{ return  std::count_if(std::begin(b::rg), endz(b::rg), f); }	
	bool		empty () const	{ return  size()==0; }
	explicit operator bool() const	{ return !empty(); }


	////  ELEM ACCESS
	reference const	front()  const	{ return  *begin(); }
	reference  	front()		{ return  *begin(); }

	reference const back()  const	{ return  *std::prev(sto::endz(b::rg)); }	// TOFIX
	reference  	back()		{ return  *std::prev(sto::endz(b::rg)); }	// TOFIX


	////  INPORTED RG METHODS
	/*  filtered should not have (?) these methods
	using b::push_front;
	using b::push_back;
	using b::insert;
	using b::pop_front;
	using b::pop_back;
	using b::operator[];
	*/
 };


////////////////////////////////////////////////////////////////  TRAITS
template<class Rg, class F>		struct is_range_t<predicated_range<Rg,F>>			: std::true_type  {};
template<class Rg, class F, bool RO>	struct is_range_t<predicated_range_iterator<Rg,F,RO>>	: std::false_type {};

template<class Rg, class F>		struct is_sto_range<predicated_range<Rg,F>>			: std::true_type {};

template<class Rg, class F, bool RO>	struct is_sto_range_iterator <predicated_range_iterator<Rg,F,RO>> : std::true_type  {};

////////////////////////////////////////////////////////////////  PREDICATED


//  Rg1 | Pred    --> range
template<class Rg>		eIF<is_range<Rg>::value,  predicated_range<Rg&&,std::function<bool(const rg_elem_type<Rg>&)> >>	operator|  (Rg&& rg,  std::function<bool(const rg_elem_type<Rg>&)> pred){ return   predicated_range<Rg&&,std::function<bool(const rg_elem_type<Rg>&)>> (std::forward<Rg>(rg),  pred); };
template<class Rg>		eIF<is_range<Rg>::value,  predicated_range<Rg&&,std::function<bool(rg_elem_type<Rg>)>        >>	operator|  (Rg&& rg,  std::function<bool(rg_elem_type<Rg>)>        pred){ return   predicated_range<Rg&&,std::function<bool(rg_elem_type<Rg>)>       > (std::forward<Rg>(rg),  pred); };
template<class Rg>		eIF<is_range<Rg>::value,  predicated_range<Rg&&,bool(*)(const rg_elem_type<Rg>&)             >>	operator|  (Rg&& rg,  bool(pred)(const rg_elem_type<Rg>&)              ){ return   predicated_range<Rg&&,bool(*)(const rg_elem_type<Rg>&)            > (std::forward<Rg>(rg),  pred); };
template<class Rg>		eIF<is_range<Rg>::value,  predicated_range<Rg&&,bool(*)(rg_elem_type<Rg>)                    >>	operator|  (Rg&& rg,  bool(pred)(rg_elem_type<Rg>)                     ){ return   predicated_range<Rg&&,bool(*)(rg_elem_type<Rg>)                   > (std::forward<Rg>(rg),  pred); };
template<class Rg, class F>	eIF<is_range<Rg>::value && is_callable<F, bool(rg_elem_type<Rg>)>::value, 
							  predicated_range<Rg&&, F>>						operator|  (Rg&& rg,  F pred)						{ return   predicated_range<Rg&&,F> (std::forward<Rg>(rg),  pred); };
		// Overload is better than SFINAE selection. With OL we do not need to specify functor template arguments
						};
						#endif //  STO_MAPPED_RANGE_H

