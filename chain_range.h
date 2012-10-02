
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

	template<class Rn, class O = rn_elem_type<Rn>> struct  chain_range;

	template <class Rn, class O,  bool CONST_IT>
struct chain_range_iterator {


		// TYPES
		typedef    typename std::conditional<
			CONST_IT,
			rn_const_iterator<Rn>,
			rn_iterator<Rn>
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

	typedef		chain_range_iterator<Rn, O, false>		iterator;
	typedef		chain_range_iterator<Rn, O, true>		const_iterator;
	//typedef		rn_elem_type<Rn>				value_type;
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
	operator chain_range_iterator<Rn&&,O,true>() { return chain_range_iterator<Rn&&,O,true>(parent, current); };

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
		org_iterator e = endz(parent->rn);
		assert(current !=e);
		current = std::find_if(++current, e, parent->pred);
		return *this; 
	}

	self		operator++(int)		{
		org_iterator e = endz(parent->rn);
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
	template<class Rn, class O /*= rn_elem_type<Rn>*/ >
struct  chain_range : ref_container<Rn&&> {

		typedef		rn_elem_type<Rn>  						value_type;
		typedef		value_type							T;
		typedef		chain_range_iterator<Rn, O, false>     				iterator;
		typedef		chain_range_iterator<Rn, O, true >				const_iterator;
		typedef		size_t  							size_type;
		typedef		typename std::iterator_traits<rn_iterator<Rn>>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<rn_iterator<Rn>>::pointer		pointer ;
		typedef		typename std::iterator_traits<rn_iterator<Rn>>::reference	reference ;

		typedef		chain_range<Rn>							self_type;

	// MEMBERS
	Rn& rn;

	std::function<bool(value_type)>	static  	nop_pred;	// predicate
	std::function<bool(value_type)>			pred = nop_tran;;

	//std::function<const value_type&(const value_type&)>  static	nop_tran;	// transform
	std::function<value_type(value_type)>  static		nop_tran;	// transform
	std::function<value_type(value_type)>			tran = nop_tran;

	// default CTOR
	explicit chain_range(Rn&& rn)		  : ref_container<Rn&&>(std::forward<Rn>(rn)), rn(this->value)              {};

	// full CTOR
	
		template <class Pred, class Tran>
		explicit 
	chain_range (
		Rn&& rn,
		Pred pred,
		Tran tran
		//eIF<is_callable<Pred, bool(value_type)>::value, int> unused=0
		//eIF<is_callable<Tran, O(value_type)>::value  &&  ! std::is_same<bool, O>::value, int> unused=0
	)
	:  ref_container<Rn&&>(std::forward<Rn>(rn)),  rn(this->value),  pred(pred), tran(tran)
	{};


	// ASSIGNMENT
	chain_range&   operator= (value_type x) { std::fill(begin(), end(), x);  return *this; };

		template<class Rn2>			// FIXME specialize for seq containers self-assignemet
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
	//size_t		size  () const	{ return  sto::size (rn); }	// TOFIX
	size_t		size  () const	{ return  std::count_if(std::begin(rn), endz(rn), pred); }	// TOFIX
	bool		empty () const	{ return  sto::empty(rn); }	// TOFIX
	explicit operator bool() const	{ return !sto::empty(rn); }	// TOFIX


	// ELEM ACCESS
	value_type  	front()  const	{ return  *std::begin(rn); }  	// TOFIX
	reference  	front()		{ return  *std::begin(rn); }  	// TOFIX

	value_type  	back()  const	{ return  *(std::prev(sto::endz(rn))); }  	// TOFIX
	reference  	back()		{ return  *(std::prev(sto::endz(rn))); }  	// TOFIX

	// INPORTED CT METHODS
	template<class U=Rn>   eIF<has_push_back<U>()>		push_back(const value_type& value)	{rn.push_back(value);}
	template<class U=Rn>   eIF<has_push_back<U>()>		push_back(value_type&& value)		{rn.push_back(std::move(value));}

	template<class U=Rn>   eIF<has_push_front<U>()>		push_front(const value_type& value)	{rn.push_front(value);}
	template<class U=Rn>   eIF<has_push_front<U>()>		push_front(value_type&& value)		{rn.push_front(std::move(value));}

	template<class U=Rn>   eIF<has_1arg_insert<U>()>	insert(const value_type& value)	{rn.insert(value);}
	template<class U=Rn>   eIF<has_1arg_insert<U>()>	insert(value_type&& value)		{rn.insert(std::move(value));}

	template<class U=Rn>   eIF<has_pop_back<U>()>		pop_back()				{rn.pop_back();}
	template<class U=Rn>   eIF<has_pop_front<U>()>		pop_front()				{rn.pop_front();}

	template<class U=Rn>   eIF<has_back<U>(), value_type>	back()					{return rn.back();}
	template<class U=Rn>   eIF<has_front<U>(), value_type>	front()					{return rn.front();}

	// ADDED CT METHODS
		template<class U=Rn>   eIF<is_c_string<U>()>	
	push_back(char value)			{
		auto e=endz(rn);  
		assert(e < (rn + std::extent<rm_qualifier<U>>::value-1)); 
		*e = value; 
		*++e='\0';
	}

 };

 // CHAIN_RANGE  STATIC MEMBERS

	template<class Rn, class O /*= rn_elem_type<Rn>*/ >
	std::function<bool(typename chain_range<Rn,O>::value_type)>   
	chain_range<Rn,O>::
nop_pred = [](const typename chain_range<Rn,O>::value_type& x) -> bool  {return true;};

	template<class Rn, class O /*= rn_elem_type<Rn>*/ >
	std::function<typename chain_range<Rn,O>::value_type(typename chain_range<Rn,O>::value_type)>
	chain_range<Rn,O>::
nop_tran =  [](typename chain_range<Rn,O>::value_type x)   {return x;};


////////////////////////////////////////////////////////////////  FUNCTION RANGE() -- range maker

	template<class Rn>   
	eIF<is_range<Rn>(), chain_range<Rn&&>>   
range(Rn&& rn)  {
	return  chain_range<Rn&&>(std::forward<Rn>(rn));  // there is no copy on return
 };
////////////////////////////////////////////////////////////////  PIPE


//  Ct1 | Pred    --> range
template<class Rn> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator|  (Rn&& rn,  std::function<bool(const rn_elem_type<Rn>&)> pred) { return   chain_range<Rn&&> (std::forward<Rn>(rn),  pred,  chain_range<Rn&&>::nop_tran); };
template<class Rn> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator|  (Rn&& rn,  std::function<bool(rn_elem_type<Rn>)> pred)        { return   chain_range<Rn&&> (std::forward<Rn>(rn),  pred,  chain_range<Rn&&>::nop_tran); };
template<class Rn> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator|  (Rn&& rn,  bool(pred)(const rn_elem_type<Rn>&))               { return   chain_range<Rn&&> (std::forward<Rn>(rn),  pred,  chain_range<Rn&&>::nop_tran); };
template<class Rn> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator|  (Rn&& rn,  bool(pred)(rn_elem_type<Rn>))                      { return   chain_range<Rn&&> (std::forward<Rn>(rn),  pred,  chain_range<Rn&&>::nop_tran); };
		// Overload is better than SFINAE selection. With OL we do not need to specify functor template arguments



//  Ct1 | Ct2   ---  search() --> range	   
/*
	template<typename Ct>
	typename std::enable_if <is_range<Ct>(),  iterator_range&>::type
operator |       (Ct& C1, const Ct& C2)    { 
	auto it = search(C1.begin(), C1.end(), C2.begin(), C2.end());
	return  iterator_range(it, advance(it, distance(C2.end(), C2.begin())));
 };

//  Ct1 / Ct2   ---  search() --> it
	template<typename Ct>
	typename std::enable_if <is_range<Ct>(),  typename Ct::iterator>::type
operator /       (Ct& C1, const Ct& C2)    {  return  search(C1.begin(), C1.end(), C2.begin(), C2.end()); };
*/


////////////////////////////////////////////////////////////////////////////////////////////////// MAP / TRANSFORM
	
	
	namespace detail {
		template<typename T>	static void	cstr_zstop(const T&    ret) {};
		__attribute__((unused))	static void	cstr_zstop(      char* ret) { *++ret = '\0'; };
	};


//  Ct * F   ---  transform(+C,-C,+D,F) -> D   (temporary demo, should really return  collection, not a container)
//  Ct1 | Pred    --> range
template<class Rn /*,class ET=rn_elem_type<Rn>*/> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator*  (Rn&& rn,  std::function<rn_elem_type<Rn>(const rn_elem_type<Rn>&)> tran) { return   chain_range<Rn&&> (std::forward<Rn>(rn),  chain_range<Rn&&,rn_elem_type<Rn>>::nop_pred, tran); };
template<class Rn /*,class ET=rn_elem_type<Rn>*/> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator*  (Rn&& rn,  std::function<rn_elem_type<Rn>(rn_elem_type<Rn>)> tran)        { return   chain_range<Rn&&> (std::forward<Rn>(rn),  chain_range<Rn&&,rn_elem_type<Rn>>::nop_pred, tran); };
template<class Rn /*,class ET=rn_elem_type<Rn>*/> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator*  (Rn&& rn,  rn_elem_type<Rn>(*tran)(const rn_elem_type<Rn>&))               { return   chain_range<Rn&&> (std::forward<Rn>(rn),  chain_range<Rn&&,rn_elem_type<Rn>>::nop_pred, tran); };
template<class Rn /*,class ET=rn_elem_type<Rn>*/> eIF<is_range<Rn>(),  chain_range<Rn&&>>  operator*  (Rn&& rn,  rn_elem_type<Rn>(*tran)(rm_ref<rn_elem_type<Rn>>))                      { return   chain_range<Rn&&> (std::forward<Rn>(rn),  chain_range<Rn&&,rn_elem_type<Rn>>::nop_pred, tran); };

/*
	// overload for generic Ret 
	template<
		typename Ct,
		typename F,
		typename T = rn_elem_type<Ct>,
		//typename Ret=typename std::function<rm_qualifier<F>>::result_type,
		typename Ret= decltype(std::declval<F>()(std::declval<T>()))
	> 
	eIF <is_range<Ct>()  &&  is_callable<F, Ret(T)>::value, std::vector<Ret>>
operator *       (Ct&& C, const F& f)    {
	//std::vector<Ret> D;
	//auto ret = std::transform(std::begin(C), endz(C), back_inserter(D), f);
	//detail::cstr_zstop(ret);
	std::vector<Ret> D;
	auto ret = std::transform(std::begin(C), endz(C), back_inserter(D), f);
	detail::cstr_zstop(ret);
	return  D;
 };


	// overload for :  Ret == T   (needed for oveloaded functions like abs)
	template<
		typename Ct,
		typename T = rn_elem_type<Ct>,
		typename Ret= T
	> 
	eIF <is_range<Ct>(), std::vector<Ret>>
operator *       (Ct&& C, T (*f)(T) )    {
	//std::vector<Ret> D;
	//auto ret = std::transform(std::begin(C), endz(C), std::back_inserter(D), f);
	//detail::cstr_zstop(ret);
	//return  D;
	std::vector<Ret> D;
	auto ret = std::transform(std::begin(C), endz(C), std::back_inserter(D), f);
	detail::cstr_zstop(ret);
	return  D;
 };


	// overload for :  lambdas
	template<
		typename Ct,
		typename T = rn_elem_type<Ct>,
		typename Ret= T
	> 
	eIF <is_range<Ct>(), std::vector<Ret>>
operator *       (Ct&& C, std::function<T(T)> f )    {
	std::vector<Ret> D;
	auto ret = std::transform(std::begin(C), endz(C), std::begin(D), f);
	detail::cstr_zstop(ret);
	return  D;
 };


//////////////////////////////////////////////////////////////////////  Ct || F   ---  accumulate(+C+1,-C, ++C, F) -> D  		 

	// overload for plain functions
	template< typename Ct, typename T = rn_elem_type<Ct>, typename R = T > 
	eIF <is_range<Ct>(), R>
operator ||       (Ct&& C, const R& (*f)(const T&, const T&) )    {
	auto i = std::next(std::begin(C));
	return  std::accumulate(i, endz(C), front(C), f);
 };


	// overload for: lambda, std::plus
	template< typename Ct, typename T = rn_elem_type<Ct>, typename R = T > 
	eIF <is_range<Ct>(), R>
operator ||       (Ct&& C, identity<std::function<T(const T&, const T&)>> f )    {
	auto i = std::next(std::begin(C));
	const T init = front(C);
	return  std::accumulate(i, endz(C), init, f);
 };
*/


						}; 
						#endif //  STO_CHAIN_RANGE_H
