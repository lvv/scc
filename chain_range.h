
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include "scc/meta.h"
						#include "scc/stl.h"
						namespace sto {

/////////////////////////////////////////////////////////////////////////////////////////  REF PROVIDER

template<typename T>	struct  ref_container;
template<typename T>	struct  ref_container<T& >  { T& value;  explicit ref_container(T&  x) : value(x)            {} };
template<typename T>	struct  ref_container<T&&>  { T  value;  explicit ref_container(T&& x) : value(std::move(x)) {} };

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE

//template <class Rn, bool CONST_IT=is_const_iterator<cl_iterator<Rn>>()>
template <class Rn, bool CONST_IT>
struct chain_range_iterator {

	// MEMBERS
		typedef    typename std::conditional<
			CONST_IT,
			//std::is_const<rm_ref<Rn>>::value,
			cl_const_iterator<Rn>,
			cl_iterator<Rn>
		>::type   org_iterator;


	org_iterator current;


	// STL ITERATOR TYPES
	typedef		std::forward_iterator_tag			iterator_category;

	typedef		chain_range_iterator<Rn, false>			iterator;
	typedef		chain_range_iterator<Rn, true>			const_iterator;
	typedef		cl_elem_type<Rn>				value_type;

	typedef		const value_type*				const_pointer;
	typedef		typename std::conditional<CONST_IT, const_pointer, value_type*>::type
									pointer;

	typedef		const value_type&				const_reference;
	typedef		typename std::conditional<CONST_IT, const_reference, value_type&>::type
									reference;

	typedef		size_t						size_type;
	typedef		ptrdiff_t					difference_type;

	typedef		chain_range_iterator				self;

	////// CTOR
	chain_range_iterator ()                             : current()            {};  // default
	chain_range_iterator (const org_iterator& current)  : current(current)     {};
	chain_range_iterator (const self& rhs)              : current(rhs.current) {};	// copy 

	////// IFACE
	reference	operator*()		{ return   *current; }
	const_reference	operator*()	const	{ return   *current; }

	pointer		operator->()		{ return  &*current; }
	const_pointer	operator->()	const	{ return  &*current; }

	self&		operator++()		{ ++current;  return *this;  }
	self		operator++(int)		{  static int i=0;  self tmp=*this;  ++current;  return std::move(tmp); }

	bool		operator==(const const_iterator& rhs)	const	{ return   current == rhs.current; }
	bool		operator!=(const const_iterator& rhs)	const	{ return   ! (*this == rhs); }
 };


/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE
	template<typename Rn>
struct  chain_range : ref_container<Rn&&> {

		typedef		cl_elem_type<Rn>  						value_type;
		typedef		value_type							T;
		typedef		chain_range_iterator<      Rn, false>     			iterator;
		typedef		chain_range_iterator<const Rn, true >				const_iterator;
		typedef		size_t  							size_type;
		typedef		typename std::iterator_traits<cl_iterator<Rn>>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<cl_iterator<Rn>>::pointer		pointer ;
		typedef		typename std::iterator_traits<cl_iterator<Rn>>::reference	reference ;

	// MEMBERS
	//using ref_container<Rn&&>::rn;
	Rn& rn;

	       std::function<bool(const value_type&)>		default_pred = [](const value_type& x) {return true;};
	const  std::function<bool(const value_type&)>&		pred;

	// CTOR
	template<class Pred>
	explicit chain_range(Rn&& rn, Pred pred)  : ref_container<Rn&&>(std::forward<Rn>(rn)), rn(ref_container<Rn&&>::value), pred(pred)         {};
	explicit chain_range(Rn&& rn)             : ref_container<Rn&&>(std::forward<Rn>(rn)), rn(ref_container<Rn&&>::value), pred(default_pred) {};



	// ASSIGNMENT
	chain_range&   operator= (value_type x) { std::fill(std::begin(rn), sto::endz(rn), x);  return *this; };

	template<typename rhsRn>
	eIF <have_same_elem<Rn,rhsRn>(), chain_range&>
	operator= (const rhsRn& rhs) { sto::clear(rn); for (const auto &x: rhs)  detail::append_elem(std::forward<Rn>(rn), x);    return *this; };


	// ITERATOR
	iterator	begin()		{ return iterator(std::begin(rn)); }
	iterator	end()		{ return iterator(std::end(rn)); }
	const_iterator	begin() const	{ return const_iterator(std::begin(rn)); }
	const_iterator	end()   const	{ return const_iterator(std::end(rn)); }

	void		increment(iterator& it) { while (!pred(*++it.current)  &&  it.current != it.end() ); }


	// CT MANAGMENT
	size_t		size  () const	{ return  sto::size (rn); }
	bool		empty () const	{ return  sto::empty(rn); }
	explicit operator bool() const	{ return !sto::empty(rn); }


	// ELEM ACCESS
	value_type  	front()  const	{ return  *std::begin(rn); }  
	reference  	front()		{ return  *std::begin(rn); }  

	value_type  	back()  const	{ return  *(std::prev(sto::endz(rn))); }  
	reference  	back()		{ return  *(std::prev(sto::endz(rn))); }  

	// INPORT CT METHODS
	template<class U=Rn>   eIF<has_size<U>(), size_type>	size()					{return rn.size();}
	template<class U=Rn>   eIF<has_empty<U>(), bool>	empty()					{return rn.empty();}

	template<class U=Rn>   eIF<has_push_back<U>()>		push_back( const value_type& value)	{rn.push_back(value);}
	template<class U=Rn>   eIF<has_push_back<U>()>		push_back( value_type&& value)		{rn.push_back(std::move(value));}

	template<class U=Rn>   eIF<has_push_front<U>()>		push_front( const value_type& value)	{rn.push_front(value);}
	template<class U=Rn>   eIF<has_push_front<U>()>		push_front( value_type&& value)		{rn.push_front(std::move(value));}

	template<class U=Rn>   eIF<has_1arg_insert<U>()>	insert( const value_type& value)	{rn.insert(value);}
	template<class U=Rn>   eIF<has_1arg_insert<U>()>	insert( value_type&& value)		{rn.insert(std::move(value));}

	template<class U=Rn>   eIF<has_pop_back<U>()>		pop_back()				{rn.pop_back();}
	template<class U=Rn>   eIF<has_pop_front<U>()>		pop_front()				{rn.pop_front();}

	template<class U=Rn>   eIF<has_back<U>(), value_type>	back()					{return rn.back();}
	template<class U=Rn>   eIF<has_front<U>(), value_type>	front()					{return rn.front();}
 };


////////////////////////////////////////////////////////////////  FUNCTION RANGE() -- range maker

	template<class Rn>   
	eIF<is_range<Rn>(), chain_range<Rn&&>>   
range(Rn&& rn)  {
	return  std::move(chain_range<Rn&&>(std::forward<Rn>(rn)));
};


						}; 
						#endif //  STO_CHAIN_RANGE_H
