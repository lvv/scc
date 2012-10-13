
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include "scc/meta.h"
						#include "scc/stl.h"

						#ifndef NDEBUG
						#include <iostream>
						#include <scc/debug.h>
						#endif

						namespace sto {
						//template<class Ch> class basic_string<Ch>;

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE_ITERATOR

	template<class Rg, class O = rg_elem_type<Rg>, bool MAPPED = false> struct  chain_range;


	template <class Rg, class O,  bool RO, bool MAPPED>
struct chain_range_iterator {
				
		//static_assert(!MAPPED || (RO && MAPPED), "bad combination of RO and MAPPED");


		// TYPES
		typedef SEL <
			RO,
			rg_const_iterator<Rg>,
			rg_iterator<Rg>
		>	org_iterator;

		typedef	SEL <
			RO,
			chain_range<Rg,O,MAPPED> const,
			chain_range<Rg,O,MAPPED>
		>*	parent_t;


	// MEMBERS
	parent_t	parent;
	org_iterator	current;


	// STL ITERATOR TYPES
	//typedef		SEL <MAPPED, std::input_iterator_tag, std::forward_iterator_tag> iterator_category;

	//typedef		std::bidirectional_iterator_tag  	iterator_category;
	typedef		typename std::iterator_traits<org_iterator>::iterator_category 	iterator_category;

	typedef		O						value_type;
	typedef		chain_range_iterator<Rg, O, RO,   MAPPED>	iterator;
	typedef		chain_range_iterator<Rg, O, true, MAPPED>	const_iterator;

	typedef		size_t  					size_type;
	typedef		ptrdiff_t 					difference_type ;
	//typedef		const value_type*			const_pointer;  // non-STL, not-used?
	typedef		SEL <RO, const value_type*, value_type*>   	pointer;


	typedef         SEL <MAPPED, value_type, const value_type&>     const_reference;	// non-STL
	//typedef		SEL <MAPPED, value_type, SEL<RO, const reference, value_type&>> reference;
	typedef		SEL <
				MAPPED,
				value_type,
				SEL <
					RO,
					//typename std::iterator_traits<rg_const_iterator<Rg>>::reference,
					//typename std::iterator_traits<rg_iterator<Rg>>::reference
					rg_const_reference<Rg>,
					rg_reference<Rg>
				>
			>  reference;
	/*
	*/

	// non-STL
	typedef		rg_elem_type<Rg>  				elem_type;
	typedef		rm_ref<chain_range_iterator>			self_type;

	////// CTOR
	chain_range_iterator ()				: parent(0)           			   {};	// default
	chain_range_iterator ( const self_type& rhs)		: parent(rhs.parent), current(rhs.current) {};	// copy 
	chain_range_iterator ( parent_t parent,  const org_iterator current) 
							: parent(parent), current(current)         {};
	// ASSIGNMENT
		/* implicit */

	////// CONVERSION 
	operator chain_range_iterator<Rg&&,O,true,MAPPED>() { return chain_range_iterator<Rg&&,O,true,MAPPED>(parent, current); };

	////// IFACE
	
	reference	operator*()  		{ return  parent->get_value(current, std::integral_constant<bool,MAPPED>()); };
	const_reference operator*() const 	{ return  parent->get_value(current, std::integral_constant<bool,MAPPED>()); };

	pointer		operator->()		{ return  &(operator*()); }
	pointer	const 	operator->() const	{ return  &(operator*()); }


	self_type&		operator++()		{
		org_iterator e = endz(parent->rg);
		assert(current !=e);
		current = std::find_if(++current, e, parent->pred);
		return *this; 
	}

	self_type		operator++(int)		{
		org_iterator e = endz(parent->rg);
		assert(current !=e);
		self_type tmp=*this;
		current = std::find_if(++current, e, parent->pred);
		return std::move(tmp);
	}

	bool	operator==(const_iterator rhs)	const	{ return   current == rhs.current; }
	bool	operator!=(const_iterator rhs)	const	{ return   current != rhs.current; }

	///////////////////////////////////////////////////////////////////// INPORT ORG_ITERATOR METHODS
	
	#define dcv(x)   std::declval<x>()
	
	//  bidiractional  (FIXME for pred)
	template<class U=org_iterator, class R=decltype(std::declval<U>()--)> 				self_type&	operator--()			{ --current;  return *this; }
	template<class U=org_iterator, class R=decltype(std::declval<U>()--)> 				self_type	operator--(int)			{ self_type tmp=*this;  --current;   return std::move(tmp); }
                                                                     
	                                                            
	// random access  (FIXME for pred)                         
	template<class U=org_iterator, class R=decltype(std::declval<U>()+=1)>				iterator	operator+= (difference_type n)	{ current+=n;  return *this; }
	template<class U=org_iterator, class R=decltype(std::declval<U>()-=1)>				iterator	operator-= (difference_type n)	{ current-=n;  return *this; }
	template<class U=org_iterator, class R=decltype(std::declval<U>()[1])>				reference	operator[] (difference_type n)	{ return current[n]; }
	template<class U=org_iterator, class R=decltype(std::declval<U>() <  std::declval<U>())>	bool		operator<  (self_type other)	{ return current <  other.current; } 
	template<class U=org_iterator, class R=decltype(std::declval<U>() <= std::declval<U>())>	bool		operator<= (self_type other)	{ return current <= other.current; } 
	template<class U=org_iterator, class R=decltype(std::declval<U>() >  std::declval<U>())>	bool		operator>  (self_type other)	{ return current >  other.current; } 
	template<class U=org_iterator, class R=decltype(std::declval<U>() >= std::declval<U>())>	bool		operator>= (self_type other)	{ return current >= other.current; } 
 };

template <class RgI>  auto  operator+  (RgI it, typename RgI::difference_type n) -> rm_ref<decltype(it.current+n, std::declval<RgI>())>    { it.current+=n;  return std::move(it); }
template <class RgI>  auto  operator-  (RgI it, typename RgI::difference_type n) -> rm_ref<decltype(it.current-n, std::declval<RgI>())>   { it.current-=n;  return std::move(it); }
template <class RgI>  auto  operator+  (typename RgI::difference_type n, RgI it) -> rm_ref<decltype(it.current+n, std::declval<RgI>())>   { it.current+=n;  return std::move(it); }

// error: recursive template
//template <class RgI>  auto  operator-  (RgI it1, RgI it2)    -> rm_ref<decltype(it1.current-it2.current)>              { return it1.current-it2.current; }

template <class RgI>  auto  operator-  (RgI it1, RgI it2)	-> typename RgI::difference_type	{ return it1.current-it2.current; }


/////////////////////////////////////////////////////////////////////////////////////////  REF CONTAINER

template<class T>	struct  ref_container;
template<class T>	struct  ref_container<T& >  { T& value;  explicit ref_container(T&  x) : value(x)            {} };
template<class T>	struct  ref_container<T&&>  { rm_ref<T>  value;  explicit ref_container(T&& x) : value(x) {} };

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE
	template<class Rg, class O, bool MAPPED>
struct  chain_range : ref_container<Rg&&> {


		// STL IFACE
		typedef		O  						value_type;
		typedef		chain_range_iterator<Rg, O, false, MAPPED>     	iterator;
		typedef		chain_range_iterator<Rg, O, true,  MAPPED>	const_iterator;

		typedef		size_t  					size_type;
		typedef		ptrdiff_t 					difference_type ;
		typedef		value_type*					pointer;
		//typedef		const value_type*				const_pointer; // non-stl, not-used?

		typedef         SEL <MAPPED, value_type, const value_type&>     const_reference;  // non-STL
		//typedef		rg_reference<Rg>				reference ;
		typedef		SEL <
					MAPPED,
					value_type,
					SEL <
						//RO,
						//typename std::iterator_traits<rg_const_iterator<Rg>>::reference,
						//typename std::iterator_traits<rg_iterator<Rg>>::reference
						std::is_const<Rg>::value,
						rg_const_reference<Rg>,
						rg_reference<Rg>
					>
				>  reference;

	
		// non-STL
		typedef		rg_elem_type<Rg>  				elem_type;
		typedef		chain_range<Rg>					self_type;
		typedef		void						range_category;

	// MEMBERS
	Rg& rg;

	std::function<bool(elem_type)>	static  		nop_pred;	// predicate
	std::function<bool(elem_type)>				pred = nop_pred;;

	//std::function<const value_type&(const value_type&)>  static	nop_tran;	// transform
	std::function<value_type(elem_type)>  static		nop_tran;	// transform
	std::function<value_type(elem_type)>			tran; // = nop_tran;

	// default CTOR
	explicit chain_range(Rg&& rg)  : ref_container<Rg&&>(std::forward<Rg>(rg)), rg(this->value)  {};

	// full CTOR
	
		template <class Pred, class Tran>
		explicit 
	chain_range (
		Rg&& rg,
		Pred pred,
		Tran tran
	)
	:  ref_container<Rg&&>(std::forward<Rg>(rg)),  rg(this->value),  pred(pred), tran(tran)
	{};


	// ASSIGNMENT
	chain_range&   operator= (elem_type x) { std::fill(begin(), end(), x);  return *this; };

		template<class Rg2>			// TODO specialize for seq containers self-assignemet
		eIF <have_same_elem<Rg,Rg2>::value, self_type&>
	operator= (const Rg2& rhs) {
		sto::clear(rg);
		auto e = endz(rhs);
		for (auto it = std::begin(rhs);   it != e;  ++it)  {
			detail::append_elem(std::forward<Rg>(rg), *it);
		}
		return *this;
	};

	// ITERATOR
	      iterator	end()		{ return        iterator(this, endz(rg)); }
	const_iterator	end()   const	{ return  const_iterator(this, endz(rg)); }

	      iterator	begin()		{ return        iterator(this, std::find_if(std::begin(rg), endz(rg), pred)); };
	const_iterator	begin()	const	{ return  const_iterator(this, std::find_if(std::begin(rg), endz(rg), pred)); };


	// RG PROPERTIES
	size_t		size  () const	{ return  std::count_if(std::begin(rg), endz(rg), pred); }	
	bool		empty () const	{ return  sto::empty(rg); }
	explicit operator bool() const	{ return !sto::empty(rg); }


	// ELEM ACCESS
	reference const	front()  const	{ return  get_value(std::begin(rg), std::integral_constant<bool,MAPPED>()); }
	reference  	front()		{ return  get_value(std::begin(rg), std::integral_constant<bool,MAPPED>()); }

	reference const back()  const	{ return  get_value(std::prev(sto::endz(rg)), std::integral_constant<bool,MAPPED>()); }  
	reference  	back()		{ return  get_value(std::prev(sto::endz(rg)), std::integral_constant<bool,MAPPED>()); } 


	// INPORTED RG METHODS
	template<class U=Rg>   eIF<has_push_back<U>::value>		push_back(const elem_type&  value)	{rg.push_back(value);}
	template<class U=Rg>   eIF<has_push_back<U>::value>		push_back(      elem_type&& value)	{rg.push_back(std::move(value));}

	template<class U=Rg>   eIF<has_push_front<U>::value>		push_front(const elem_type&  value)	{rg.push_front(value);}
	template<class U=Rg>   eIF<has_push_front<U>::value>		push_front(      elem_type&& value)	{rg.push_front(std::move(value));}

	template<class U=Rg>   eIF<has_1arg_insert<U>::value>		insert(const elem_type&  value)		{rg.insert(value);}
	template<class U=Rg>   eIF<has_1arg_insert<U>::value>		insert(      elem_type&& value)		{rg.insert(std::move(value));}

	template<class U=Rg>   eIF<has_pop_back<U>::value>		pop_back()				{rg.pop_back();}
	template<class U=Rg>   eIF<has_pop_front<U>::value>		pop_front()				{rg.pop_front();}
	// why error ??? 
	// template<class U=Rg>   auto  operator[] (difference_type n) -> decltype(rg[0])   { return  rg[n]; } // FIXME for pred
	// auto  operator[] (difference_type n) -> decltype(std::declval<Rg>()[0])   { return  rg[n]; } // FIXME for pred
	
	template<class U=Rg>  auto  operator[] (difference_type n) -> decltype(std::declval<U>()[0])   { return  rg[n]; } // FIXME for pred

	// ADDED RG METHODS
		template<class U=Rg>  
		eIF<is_c_string_t<U>::value>	
	push_back(char value)			{
		auto e=endz(rg);  
		assert(e < (rg + std::extent<rm_qualifier<U>>::value-1)); 
		*e = value; 
		*++e='\0';
	}

	O			get_value(rg_iterator      <Rg> it, std::integral_constant<bool,true> )		{ return  tran(*it); };
	O			get_value(rg_const_iterator<Rg> it, std::integral_constant<bool,true> ) const	{ return  tran(*it); };
	reference		get_value(rg_iterator      <Rg> it, std::integral_constant<bool,false>) 	{ return  *it; };
	rg_const_reference<Rg>	get_value(rg_const_iterator<Rg> it, std::integral_constant<bool,false>) const	{ return  *it; };
 };

 // CHAIN_RANGE  STATIC MEMBERS

	template<class Rg, class O, bool MAPPED >
	std::function<bool(rg_elem_type<Rg>)>   
	chain_range<Rg,O,MAPPED>::
nop_pred = [](rg_elem_type<Rg> x) -> bool  { return true; };


template<class T>  T nop_tran(T x) { return x; }

	template<class Rg, class O, bool MAPPED>
	std::function<O(rg_elem_type<Rg>)>
	chain_range<Rg,O,MAPPED>::
//nop_tran =  (O(*)(rg_elem_type<Rg>)) (nop_tran<rg_elem_type<Rg>);
//nop_tran =  std::function<O(rg_elem_type<Rg>)> (nop_tran<rg_elem_type<Rg>>);
nop_tran =  [](rg_elem_type<Rg> x)   { return x; };

// TRAITS

template<class Rg, class O, bool MAPPED >
struct is_range_t<chain_range<Rg,O,MAPPED>>               : std::true_type  {};

template <class Rg, class O,  bool RO, bool MAPPED>
struct is_range_t<chain_range_iterator<Rg,O,RO,MAPPED>>   : std::false_type {};

////////////////////////////////////////////////////////////////  FUNCTION RANGE() -- range maker

	template<class Rg>   
	eIF<is_range<Rg>::value, chain_range<Rg&&>>   
range(Rg&& rg)  {
	return  chain_range<Rg&&>(std::forward<Rg>(rg));  // there is no copy on return
 };
////////////////////////////////////////////////////////////////  PIPE


//  Rg1 | Pred    --> range
template<class Rg> eIF<is_range<Rg>::value,  chain_range<Rg&&>>  operator|  (Rg&& rg,  std::function<bool(const rg_elem_type<Rg>&)> pred) { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
template<class Rg> eIF<is_range<Rg>::value,  chain_range<Rg&&>>  operator|  (Rg&& rg,  std::function<bool(rg_elem_type<Rg>)> pred)        { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
template<class Rg> eIF<is_range<Rg>::value,  chain_range<Rg&&>>  operator|  (Rg&& rg,  bool(pred)(const rg_elem_type<Rg>&))               { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
template<class Rg> eIF<is_range<Rg>::value,  chain_range<Rg&&>>  operator|  (Rg&& rg,  bool(pred)(rg_elem_type<Rg>))                      { return   chain_range<Rg&&> (std::forward<Rg>(rg),  pred,  chain_range<Rg&&>::nop_tran); };
		// Overload is better than SFINAE selection. With OL we do not need to specify functor template arguments



//  Rg1 | Rg2   ---  search() --> range	   
/*
	template<typename Rg>
	typename std::enable_if <is_range<Rg>::value,  iterator_range&>::type
operator |       (Rg& rg1, const Rg& rg2)    { 
	auto it = search(rg1.begin(), rg1.end(), rg2.begin(), rg2.end());
	return  iterator_range(it, advance(it, distance(rg2.end(), rg2.begin())));
 };

//  Rg1 / Rg2   ---  search() --> it
	template<typename Rg>
	typename std::enable_if <is_range<Rg>::value,  typename Rg::iterator>::type
operator /       (Rg& rg1, const Rg& rg2)    {  return  search(rg1.begin(), rg1.end(), rg2.begin(), rg2.end()); };
*/


////////////////////////////////////////////////////////////////////////////////////////////////// MAP / TRANSFORM
	
	
	/*
	namespace detail {
		template<typename T>	static void	cstr_zstop(const T&    ret) {};
		__attribute__((unused))	static void	cstr_zstop(      char* ret) { *++ret = '\0'; };
	};*/


//  Rg1 * F    --> range
	
	template<				// overload for generic Ret (lambdas, other)
		typename Rg,
		typename Tran,
		typename E = rg_elem_type<Rg>,
		//typename Ret=typename std::function<rm_qualifier<Tran>>::result_type,
		typename Ret= decltype(std::declval<Tran>()(std::declval<E>()))
	> 
	eIF <is_range<Rg>::value  &&  is_callable<Tran, Ret(E)>::value,   chain_range<Rg&&, Ret, true>>
operator*       (Rg&& rg,  const Tran& tran)    {
	return   chain_range<Rg&&, Ret, true> (std::forward<Rg>(rg),  chain_range<Rg&&, Ret, true>::nop_pred, tran);
 };
	
	template<		// overload for :  Ret == E   (needed for oveloaded functions like abs)
		typename Rg,
		typename E = rg_elem_type<Rg>,
		typename Ret = E
	> 
	eIF <is_range<Rg>::value,  chain_range<Rg&&,E,true>>
operator *       (Rg&& rg, E (*tran)(E) )    {
	return   chain_range<Rg&&, E, true> (std::forward<Rg>(rg),  chain_range<Rg&&, E, true>::nop_pred, tran);
 };


//////////////////////////////////////////////////////////////////////  Rg || F   ---  accumulate(+C+1,-C, ++C, F) -> D  		 

	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>::value, R>							// overload for plain functions
operator ||       (Rg&& C, const R& (*f)(const T&, const T&) )    {
	auto i = std::next(std::begin(C));
	return  std::accumulate(i, endz(C), front(C), f);
 };
	
	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>::value, R>							// overload for: lambda, std::plus
operator ||       (Rg&& C, identity<std::function<T(const T&, const T&)>> f )    {
	auto i = std::next(std::begin(C));
	const T init = front(C);
	return  std::accumulate(i, endz(C), init, f);
 };

						}; 
						#endif //  STO_CHAIN_RANGE_H
