
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include "scc/meta.h"
						#include "scc/stl.h"

						#ifndef NDEBUG
						#include <iostream>
						#endif

						namespace sto {
						//template<class Ch> class basic_string<Ch>;

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE_ITERATOR

	template<class Rg, class O = rg_elem_type<Rg>> struct  chain_range;

	template <class Rg, class O,  bool CONST_IT>
struct chain_range_iterator {


		// TYPES
		typedef    typename std::conditional<
			CONST_IT,
			rg_const_iterator<Rg>,
			rg_iterator<Rg>
		>::type   org_iterator;

		typedef typename std::conditional<
			CONST_IT,
			chain_range<Rg> const,
			chain_range<Rg>
		>::type*   parent_t;


	// MEMBERS
	parent_t	parent;
	org_iterator	current;


	// STL ITERATOR TYPES
	typedef		std::forward_iterator_tag			iterator_category;

	typedef		chain_range_iterator<Rg, O, false>		iterator;
	typedef		chain_range_iterator<Rg, O, true>		const_iterator;
	//typedef		rg_elem_type<Rg>				value_type;
	typedef		O						value_type;

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
	operator chain_range_iterator<Rg&&,O,true>() { return chain_range_iterator<Rg&&,O,true>(parent, current); };

	////// IFACE
	reference	operator*()		{ return   *current; }
	const_reference	operator*()	const	{ return   *current; }
	//reference	operator*()		{ return   tran(*current); }
	//const_reference	operator*()	const	{ return   tran(*current); }

	pointer		operator->()		{ return  &*current; }
	const_pointer	operator->()	const	{ return  &*current; }
	//pointer		operator->()		{ return  &tran(*current); }
	//const_pointer	operator->()	const	{ return  &tran(*current); }

	self&		operator++()		{
		org_iterator e = endz(parent->rg);
		assert(current !=e);
		current = std::find_if(++current, e, parent->pred);
		return *this; 
	}

	self		operator++(int)		{
		org_iterator e = endz(parent->rg);
		assert(current !=e);
		self tmp=*this;
		current = std::find_if(++current, e, parent->pred);
		return std::move(tmp);
	}

	bool		operator==(const_iterator rhs)	const	{ return   current == rhs.current; }
	bool		operator!=(const_iterator rhs)	const	{ return   current != rhs.current; }
 };


/////////////////////////////////////////////////////////////////////////////////////////  REF CONTAINER

template<class T>	struct  ref_container;
template<class T>	struct  ref_container<T& >  { T& value;  explicit ref_container(T&  x) : value(x)            {} };
template<class T>	struct  ref_container<T&&>  { rm_ref<T>  value;  explicit ref_container(T&& x) : value(x) {} };

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE
	template<class Rg, class O /*= rg_elem_type<Rg>*/ >
struct  chain_range : ref_container<Rg&&> {

		typedef		rg_elem_type<Rg>  						value_type;
		typedef		value_type							T;
		typedef		chain_range_iterator<Rg, O, false>     				iterator;
		typedef		chain_range_iterator<Rg, O, true >				const_iterator;
		typedef		size_t  							size_type;
		typedef		typename std::iterator_traits<rg_iterator<Rg>>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<rg_iterator<Rg>>::pointer		pointer ;
		typedef		typename std::iterator_traits<rg_iterator<Rg>>::reference	reference ;

		typedef		chain_range<Rg>							self_type;

	// MEMBERS
	Rg& rg;

	std::function<bool(value_type)>	static  	nop_pred;	// predicate
	std::function<bool(value_type)>			pred = nop_tran;;

	//std::function<const value_type&(const value_type&)>  static	nop_tran;	// transform
	std::function<value_type(value_type)>  static		nop_tran;	// transform
	std::function<value_type(value_type)>			tran = nop_tran;

	// default CTOR
	explicit chain_range(Rg&& rg)		  : ref_container<Rg&&>(std::forward<Rg>(rg)), rg(this->value)              {};

	// full CTOR
	
		template <class Pred, class Tran>
		explicit 
	chain_range (
		Rg&& rg,
		Pred pred,
		Tran tran
		//eIF<is_callable<Pred, bool(value_type)>::value, int> unused=0
		//eIF<is_callable<Tran, O(value_type)>::value  &&  ! std::is_same<bool, O>::value, int> unused=0
	)
	:  ref_container<Rg&&>(std::forward<Rg>(rg)),  rg(this->value),  pred(pred), tran(tran)
	{};


	// ASSIGNMENT
	chain_range&   operator= (value_type x) { std::fill(begin(), end(), x);  return *this; };

		template<class Rg2>			// FIXME specialize for seq containers self-assignemet
		eIF <have_same_elem<Rg,Rg2>(), self_type&>
	operator= (const Rg2& rhs) {
		sto::clear(rg);
		auto e = endz(rhs);
		for (auto it = std::begin(rhs);   it != e;  ++it)  {
			detail::append_elem(std::forward<Rg>(rg), *it);
		}
		return *this;
	};

	// ITERATOR
	      iterator	end()		{ return       iterator(this, endz(rg)); }
	const_iterator	end()   const	{ return const_iterator(this, endz(rg)); }

	      iterator	begin()		{ return        iterator(this, std::find_if(std::begin(rg), sto::endz(rg), pred)); };
	const_iterator	begin()	const	{ return  const_iterator(this, std::find_if(std::begin(rg), sto::endz(rg), pred)); };


	// RG MANAGMENT
	//size_t		size  () const	{ return  sto::size (rg); }	// TOFIX
	size_t		size  () const	{ return  std::count_if(std::begin(rg), endz(rg), pred); }	// TOFIX
	bool		empty () const	{ return  sto::empty(rg); }	// TOFIX
	explicit operator bool() const	{ return !sto::empty(rg); }	// TOFIX


	// ELEM ACCESS
	value_type  	front()  const	{ return  *std::begin(rg); }  	// TOFIX
	reference  	front()		{ return  *std::begin(rg); }  	// TOFIX

	value_type  	back()  const	{ return  *(std::prev(sto::endz(rg))); }  	// TOFIX
	reference  	back()		{ return  *(std::prev(sto::endz(rg))); }  	// TOFIX

	// INPORTED RG METHODS
	template<class U=Rg>   eIF<has_push_back<U>()>		push_back(const value_type& value)	{rg.push_back(value);}
	template<class U=Rg>   eIF<has_push_back<U>()>		push_back(value_type&& value)		{rg.push_back(std::move(value));}

	template<class U=Rg>   eIF<has_push_front<U>()>		push_front(const value_type& value)	{rg.push_front(value);}
	template<class U=Rg>   eIF<has_push_front<U>()>		push_front(value_type&& value)		{rg.push_front(std::move(value));}

	template<class U=Rg>   eIF<has_1arg_insert<U>()>	insert(const value_type& value)	{rg.insert(value);}
	template<class U=Rg>   eIF<has_1arg_insert<U>()>	insert(value_type&& value)		{rg.insert(std::move(value));}

	template<class U=Rg>   eIF<has_pop_back<U>()>		pop_back()				{rg.pop_back();}
	template<class U=Rg>   eIF<has_pop_front<U>()>		pop_front()				{rg.pop_front();}

	template<class U=Rg>   eIF<has_back<U>(), value_type>	back()					{return rg.back();}
	template<class U=Rg>   eIF<has_front<U>(), value_type>	front()					{return rg.front();}

	// ADDED RG METHODS
		template<class U=Rg>   eIF<is_c_string<U>()>	
	push_back(char value)			{
		auto e=endz(rg);  
		assert(e < (rg + std::extent<rm_qualifier<U>>::value-1)); 
		*e = value; 
		*++e='\0';
	}

 };

 // CHAIN_RANGE  STATIC MEMBERS

	template<class Rg, class O /*= rg_elem_type<Rg>*/ >
	std::function<bool(typename chain_range<Rg,O>::value_type)>   
	chain_range<Rg,O>::
nop_pred = [](const typename chain_range<Rg,O>::value_type& x) -> bool  {return true;};

	template<class Rg, class O /*= rg_elem_type<Rg>*/ >
	std::function<typename chain_range<Rg,O>::value_type(typename chain_range<Rg,O>::value_type)>
	chain_range<Rg,O>::
nop_tran =  [](typename chain_range<Rg,O>::value_type x)   {return x;};


////////////////////////////////////////////////////////////////  FUNCTION RANGE() -- range maker

	template<class Rg>   
	eIF<is_range<Rg>(), chain_range<Rg&&>>   
range(Rg&& rg)  {
	return  chain_range<Rg&&>(std::forward<Rg>(rg));  // there is no copy on return
 };
////////////////////////////////////////////////////////////////  PIPE


//  Rg1 | Pred    --> range
template<class Rg> eIF<is_range<Rg>(),  chain_range<Rg&&>>  operator|  (Rg&& rg,  std::function<bool(const rg_elem_type<Rg>&)> pred) { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
template<class Rg> eIF<is_range<Rg>(),  chain_range<Rg&&>>  operator|  (Rg&& rg,  std::function<bool(rg_elem_type<Rg>)> pred)        { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
template<class Rg> eIF<is_range<Rg>(),  chain_range<Rg&&>>  operator|  (Rg&& rg,  bool(pred)(const rg_elem_type<Rg>&))               { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
template<class Rg> eIF<is_range<Rg>(),  chain_range<Rg&&>>  operator|  (Rg&& rg,  bool(pred)(rg_elem_type<Rg>))                      { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
		// Overload is better than SFINAE selection. With OL we do not need to specify functor template arguments



//  Rg1 | Rg2   ---  search() --> range	   
/*
	template<typename Rg>
	typename std::enable_if <is_range<Rg>(),  iterator_range&>::type
operator |       (Rg& rg1, const Rg& rg2)    { 
	auto it = search(rg1.begin(), rg1.end(), rg2.begin(), rg2.end());
	return  iterator_range(it, advance(it, distance(rg2.end(), rg2.begin())));
 };

//  Rg1 / Rg2   ---  search() --> it
	template<typename Rg>
	typename std::enable_if <is_range<Rg>(),  typename Rg::iterator>::type
operator /       (Rg& rg1, const Rg& rg2)    {  return  search(rg1.begin(), rg1.end(), rg2.begin(), rg2.end()); };
*/


////////////////////////////////////////////////////////////////////////////////////////////////// MAP / TRANSFORM
	
	
	namespace detail {
		template<typename T>	static void	cstr_zstop(const T&    ret) {};
		__attribute__((unused))	static void	cstr_zstop(      char* ret) { *++ret = '\0'; };
	};


//  Rg1 * Pred    --> range
	
	template<				// overload for generic Ret (lambdas, other)
		typename Rg,
		typename Tran,
		typename T = rg_elem_type<Rg>,
		//typename Ret=typename std::function<rm_qualifier<Tran>>::result_type,
		typename Ret= decltype(std::declval<Tran>()(std::declval<T>()))
	> 
	eIF <is_range<Rg>()  &&  is_callable<Tran, Ret(T)>::value,   chain_range<Rg&&>>
operator *       (Rg&& rg, const Tran& tran)    {
	return   chain_range<Rg&&> (std::forward<Rg>(rg),  chain_range<Rg&&>::nop_pred, tran);
 };
	
	template<		// overload for :  Ret == T   (needed for oveloaded functions like abs)
		typename Rg,
		typename T = rg_elem_type<Rg>,
		typename Ret = T
	> 
	eIF <is_range<Rg>(),  chain_range<Rg&&>>
operator *       (Rg&& rg, T (*tran)(T) )    {
	return   chain_range<Rg&&> (std::forward<Rg>(rg),  chain_range<Rg&&>::nop_pred, tran);
 };


//////////////////////////////////////////////////////////////////////  Rg || F   ---  accumulate(+C+1,-C, ++C, F) -> D  		 

	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>(), R>							// overload for plain functions
operator ||       (Rg&& C, const R& (*f)(const T&, const T&) )    {
	auto i = std::next(std::begin(C));
	return  std::accumulate(i, endz(C), front(C), f);
 };
	
	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>(), R>							// overload for: lambda, std::plus
operator ||       (Rg&& C, identity<std::function<T(const T&, const T&)>> f )    {
	auto i = std::next(std::begin(C));
	const T init = front(C);
	return  std::accumulate(i, endz(C), init, f);
 };

						}; 
						#endif //  STO_CHAIN_RANGE_H
