
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include "scc/meta.h"
						#include "scc/stl.h"
						namespace sto {
						//template<class Ch> class basic_string<Ch>;

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE

template<typename Rn> struct  chain_range;

template <class Rn, bool CONST_IT>
struct chain_range_iterator {


		// TYPES
		typedef    typename std::conditional<
			CONST_IT,
			cl_const_iterator<Rn>,
			cl_iterator<Rn>
		>::type   org_iterator;

		typedef typename std::conditional<
			CONST_IT,
			chain_range<Rn> const,
			chain_range<Rn>
		>::type*   parent_t;


	// MEMBERS
	parent_t	parent;
	org_iterator	current;


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
	chain_range_iterator ()				: parent(0),      current()            {};	// default
	chain_range_iterator ( const self& rhs)		: parent(rhs.parent), current(rhs.current) {};	// copy 
	chain_range_iterator ( parent_t parent, const org_iterator& current) 
							: parent(parent), current(current)     {};

	////// CONVERSION 
	operator chain_range_iterator<Rn&&, true>() { return chain_range_iterator<Rn&&,true>(parent, current); };

	////// IFACE
	reference	operator*()		{ return   *current; }
	const_reference	operator*()	const	{ return   *current; }

	pointer		operator->()		{ return  &*current; }
	const_pointer	operator->()	const	{ return  &*current; }

	self&		operator++()		{
		org_iterator e = endz(parent->rn);
		assert(current !=e);
		current = std::find_if(std::next(current), e, parent->pred);
		return *this; 
	}

	self		operator++(int)		{
		org_iterator e = endz(parent->rn);
		assert(current !=e);
		self tmp=*this;
		current = std::find_if(std::next(current), e, parent->pred);
		return std::move(tmp);
	}

	bool		operator==(const_iterator rhs)	const	{ return   current == rhs.current; }
	bool		operator!=(const_iterator rhs)	const	{ return   current != rhs.current; }
 };


/////////////////////////////////////////////////////////////////////////////////////////  REF CONTAINER

template<typename T>	struct  ref_container;
template<typename T>	struct  ref_container<T& >  { T& value;  explicit ref_container(T&  x) : value(x)            {} };
template<typename T>	struct  ref_container<T&&>  { rm_ref<T>  value;  explicit ref_container(T&& x) : value(x) {} };

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE
	template<typename Rn>
struct  chain_range : ref_container<Rn&&> {

		typedef		cl_elem_type<Rn>  						value_type;
		typedef		value_type							T;
		typedef		chain_range_iterator<Rn, false>     				iterator;
		typedef		chain_range_iterator<Rn, true >					const_iterator;
		typedef		size_t  							size_type;
		typedef		typename std::iterator_traits<cl_iterator<Rn>>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<cl_iterator<Rn>>::pointer		pointer ;
		typedef		typename std::iterator_traits<cl_iterator<Rn>>::reference	reference ;

		typedef		chain_range<Rn>							self_type;

	// MEMBERS
	//using ref_container<Rn&&>::value;
	Rn& rn;

	std::function<bool(const value_type&)>		default_pred = [](const value_type& x) -> bool {return true;};
	std::function<bool(const value_type&)>		pred;

	// CTOR
	template<class Pred>
	explicit chain_range(Rn&& rn, Pred pred)  : ref_container<Rn&&>(std::forward<Rn>(rn)), rn(this->value), pred(pred)         {};
	explicit chain_range(Rn&& rn)             : ref_container<Rn&&>(std::forward<Rn>(rn)), rn(this->value), pred(default_pred) {};


	// ASSIGNMENT
	chain_range&   operator= (value_type x) { std::fill(std::begin(rn), sto::endz(rn), x);  return *this; };

		template<class Rn2>
		eIF <have_same_elem<Rn,Rn2>(), self_type&>
	operator= (const Rn2& rhs) {
		sto::clear(rn);
		auto e = endz(rhs);
		for (auto it = std::begin(rhs);   it != e;  ++it)  {
			detail::append_elem(std::forward<Rn>(rn), *it);
		}
		return *this;
	};

	// ITERATOR
	      iterator	end()		{ return       iterator(this, endz(rn)); }
	const_iterator	end()   const	{ return const_iterator(this, endz(rn)); }

	      iterator	begin()		{ return        iterator(this, std::find_if(std::begin(rn), sto::endz(rn), pred)); };
	const_iterator	begin()	const	{ return  const_iterator(this, std::find_if(std::begin(rn), sto::endz(rn), pred)); };


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
	return  chain_range<Rn&&>(std::forward<Rn>(rn));  // there is no copy on return
};


						}; 
						#endif //  STO_CHAIN_RANGE_H
