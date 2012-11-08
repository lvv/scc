
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include "scc/meta.h"
						#include "scc/stl.h"

						/*
						#ifndef NDEBUG
						#include <iostream>
						#include <scc/debug.h>
						#endif
						*/

						namespace sto {
						//template<class Ch> class basic_string<Ch>;

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE_ITERATOR

	enum { NO_F = 0, MAPPED = 1,  PREDICATED = 2,  BAD_F = MAPPED | PREDICATED };

	template< class Rg, int FTP=NO_F, class F = void*, class O = rg_elem_type<Rg> > struct  chain_range;


	template <class Rg, int FTP, class F, class O, bool RO>
struct chain_range_iterator {
				
		static_assert(FTP != BAD_F, "bad F");

		// TYPES
		typedef SEL <
			RO,
			rg_const_iterator<Rg>,
			rg_iterator<Rg>
		>	org_iterator;

		typedef	SEL <
			RO,
			chain_range<Rg,FTP,F,O> const,
			chain_range<Rg,FTP,F,O>
		>*	parent_t;


	// MEMBERS
	parent_t	parent;
	org_iterator	current;


	// STL ITERATOR TYPES
	typedef		typename std::iterator_traits<org_iterator>::iterator_category 	iterator_category;

	typedef		O					value_type;
	typedef		chain_range_iterator<Rg,FTP,F,O,RO  >	iterator;
	typedef		chain_range_iterator<Rg,FTP,F,O,true>	const_iterator;

	typedef		size_t  					size_type;
	typedef		ptrdiff_t 					difference_type ;
	//typedef		const value_type*			const_pointer;  // non-STL, not-used?
	typedef		SEL <RO, const rm_ref<value_type>*, rm_ref<value_type>*>   	pointer;

	typedef         typename std::conditional <FTP & MAPPED, value_type, rg_const_reference<Rg>>::type     const_reference;  // non-STL
	typedef		typename std::conditional <
				FTP & MAPPED,
				value_type,
				typename std::conditional <
					std::is_const<Rg>::value || RO,
					rg_const_reference<Rg>,
					rg_reference<Rg>
				>::type
			>::type reference;


	// non-STL
	typedef		rg_elem_type<Rg>  				elem_type;
	typedef		rm_ref<chain_range_iterator>			self_type;
	typedef		self_type					type;

	////// CTOR
	chain_range_iterator ()				: parent(0)           			   {};	// default
	chain_range_iterator ( const self_type& rhs)	: parent(rhs.parent), current(rhs.current) {};	// copy 
	chain_range_iterator ( parent_t parent,  const org_iterator current) 
							: parent(parent), current(current)         {};
	// ASSIGNMENT
		/* implicit */

	////// CONVERSION  non-const --> const
	operator chain_range_iterator<Rg&&,FTP,F,O,true>() { return chain_range_iterator<Rg&&,FTP,F,O,true>(parent, current); };

	////// IFACE
	reference	operator*()  		{ return  parent->get_value(current, mk_type(FTP)() ); };
	const_reference operator*() const 	{ return  parent->get_value(current, mk_type(FTP)() ); };

	pointer		operator->()		{ return  &(operator*()); }
	pointer	const 	operator->() const	{ return  &(operator*()); }

	// ++ It

	self_type&	operator++()		{ next_impl( mk_type(FTP & PREDICATED)() );  return *this; }

	self_type&	next_impl(...)		{ ++current; return *this; }

	self_type&	next_impl(mk_type(PREDICATED))	{
		org_iterator e = endz(parent->rg);
		assert(current !=e);
		current = std::find_if(++current, e, parent->f);
		return *this; 
	}

	// ++ It

	self_type	operator++(int)		{
		org_iterator e = endz(parent->rg);
		assert(current !=e);
		self_type tmp=*this;
		current = std::find_if(++current, e, parent->f);
		return std::move(tmp);
	}

	bool	operator==(const_iterator rhs)	const	{ return   current == rhs.current; }
	bool	operator!=(const_iterator rhs)	const	{ return   current != rhs.current; }

	///////////////////////////////////////////////////////////////////// INPORT ORG_ITERATOR METHODS
	
	#define dcv(x)   std::declval<x>()
	
	//  bidiractional  (FIXME for pred)
	template<class U=org_iterator, class=decltype(std::declval<U>()--)> 			self_type&	operator--()			{ --current;  return *this; }
	template<class U=org_iterator, class=decltype(std::declval<U>()--)> 			self_type	operator--(int)			{ self_type tmp=*this;  --current;   return std::move(tmp); }
                                                                   
	                                                          
	// random access  (FIXME for pred)                       
	template<class U=org_iterator, class=decltype(std::declval<U>()+=1)>			iterator	operator+= (difference_type n)	{ current+=n;  return *this; }
	template<class U=org_iterator, class=decltype(std::declval<U>()-=1)>			iterator	operator-= (difference_type n)	{ current-=n;  return *this; }
	template<class U=org_iterator, class=decltype(std::declval<U>()[1])>			reference	operator[] (difference_type n)	{ return current[n]; }
	template<class U=org_iterator, class=decltype(std::declval<U>() <  std::declval<U>())>	bool		operator<  (self_type other)	{ return current <  other.current; } 
	template<class U=org_iterator, class=decltype(std::declval<U>() <= std::declval<U>())>	bool		operator<= (self_type other)	{ return current <= other.current; } 
	template<class U=org_iterator, class=decltype(std::declval<U>() >  std::declval<U>())>	bool		operator>  (self_type other)	{ return current >  other.current; } 
	template<class U=org_iterator, class=decltype(std::declval<U>() >= std::declval<U>())>	bool		operator>= (self_type other)	{ return current >= other.current; } 
 };


/////////////////////////////////////////////////////////////////////////////////////////  REF CONTAINER

template<class T>	struct  ref_container;
template<class T>	struct  ref_container<T& >  { T& value;  explicit ref_container(T&  x) : value(x)            {} };
template<class T>	struct  ref_container<T&&>  { rm_ref<T>  value;  explicit ref_container(T&& x) : value(x) {} };

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE
	template<class Rg, int FTP, class F, class O>
struct  chain_range : ref_container<Rg&&> {


	// STL IFACE
	typedef		O  						value_type;
	typedef		chain_range_iterator<Rg,FTP,F,O,false>     	iterator;
	typedef		chain_range_iterator<Rg,FTP,F,O,true>		const_iterator;

	typedef		size_t  					size_type;
	typedef		ptrdiff_t 					difference_type ;
	typedef		rm_ref<value_type>*					pointer;

	typedef         typename std::conditional <FTP & MAPPED, value_type, rg_const_reference<Rg>>::type     const_reference;  // non-STL
	typedef		typename std::conditional <
				FTP & MAPPED,
				value_type,
				typename std::conditional <
					std::is_const<Rg>::value /* || RO*/,      // <-- different from interator
					rg_const_reference<Rg>,
					rg_reference<Rg>
				>::type
			>::type  reference;


	// non-STL
	typedef		rg_elem_type<Rg>  				elem_type;
	typedef		chain_range					self_type;
	typedef		void						range_category;


	// MEMBERS
	Rg&	rg;
	F	f;

	/*
	std::function<bool(elem_type)>	static  		nop_pred;	// predicate
	std::function<bool(elem_type)>				pred; // = nop_pred;;

	//std::function<const value_type&(const value_type&)>  static	nop_tran;	// transform
	std::function<value_type(elem_type)>  static		nop_tran;	// transform
	std::function<value_type(elem_type)>			tran; // = nop_tran;
	*/

	////////////////////////////////////////////////////////////////  CTOR SPECIALIZATION

	// default CTOR
	explicit chain_range(Rg&& rg)  : ref_container<Rg&&>(std::forward<Rg>(rg)), rg(this->value)  {};

	// full
	explicit chain_range (Rg&& rg, F f)
		:  ref_container<Rg&&>(std::forward<Rg>(rg)),  rg(this->value),  f(f)
	{};

	// full CTOR
	
	/*
		template <class Pred, class Tran>
		explicit 
	chain_range (
		Rg&& rg,
		Pred pred,
		Tran tran
	)
	:  ref_container<Rg&&>(std::forward<Rg>(rg)),  rg(this->value),  pred(pred), tran(tran)
	{};
	*/


	////  ASSIGNMENT
	
	self_type&   operator= (elem_type x) { std::fill(begin(), end(), x);  return *this; };


		template<class Rg2>			// TODO specialize for seq containers self-assignemet
		eIF <have_same_elem<Rg,Rg2>::value, self_type>
	operator= (const Rg2& rhs) { 			//std:: cout << " SSIGNMENT \n";
		sto::clear(rg);
		auto e = endz(rhs);
		for (auto it = std::begin(rhs);   it != e;  ++it)  {
			detail::append_elem(std::forward<Rg>(rg), *it);
		}
		return *this;
	};


	////  ITERATOR
	      iterator	end()		{ return        iterator(this, endz(rg)); }
	const_iterator	end()   const	{ return  const_iterator(this, endz(rg)); }


	      iterator	begin()		{ return  begin_impl(mk_type(FTP & PREDICATED)()); };

		      iterator	begin_impl(...)	                { return  iterator(this, std::begin(rg)); };
		      iterator	begin_impl(mk_type(PREDICATED))	{ return  iterator(this, std::find_if(std::begin(rg), endz(rg), f)); };

	//const_iterator	begin()	const	{ return  begin_impl(this, std::find_if(std::begin(rg), endz(rg), f)); };
	const_iterator	begin()	const	{ return  begin_impl(mk_type(FTP & PREDICATED)()); };

		      const_iterator	begin_impl(...)			const { return  const_iterator(this, std::begin(rg)); };
		      const_iterator	begin_impl(mk_type(PREDICATED))	const { return  const_iterator(this, std::find_if(std::begin(rg), endz(rg), f)); };


	/*
	      iterator	begin()		{ return        iterator(this, std::find_if(std::begin(rg), endz(rg), f)); };
	const_iterator	begin()	const	{ return  const_iterator(this, std::find_if(std::begin(rg), endz(rg), f)); };
	*/


	////  RG PROPERTIES
	//size_t		size  () const	{ return  std::count_if(std::begin(rg), endz(rg), f); }	
	size_t		size() const	{ return  size_impl(mk_type(FTP & PREDICATED)()); }	
		size_t		size_impl(...) 			const { return  sto::size(rg); }	
		size_t		size_impl(mk_type(PREDICATED))  const { return  std::count_if(std::begin(rg), endz(rg), f); }	

	bool		empty () const	{ return  sto::empty(rg); }
	explicit operator bool() const	{ return !sto::empty(rg); }


	////  ELEM ACCESS
	reference const	front()  const	{ return  get_value(std::begin(rg),           mk_type(FTP & MAPPED)()); }
	reference  	front()		{ return  get_value(std::begin(rg),           mk_type(FTP & MAPPED)()); }

	reference const back()  const	{ return  get_value(std::prev(sto::endz(rg)), mk_type(FTP & MAPPED)()); }  
	reference  	back()		{ return  get_value(std::prev(sto::endz(rg)), mk_type(FTP & MAPPED)()); } 


	////  INPORTED RG METHODS
	template<class U=Rg>   eIF<has_push_back<U>::value>		push_back(const elem_type&  value)	{rg.push_back(value);}
	template<class U=Rg>   eIF<has_push_back<U>::value>		push_back(      elem_type&& value)	{rg.push_back(std::move(value));}

	template<class U=Rg>   eIF<has_push_front<U>::value>		push_front(const elem_type&  value)	{rg.push_front(value);}
	template<class U=Rg>   eIF<has_push_front<U>::value>		push_front(      elem_type&& value)	{rg.push_front(std::move(value));}

	template<class U=Rg>   eIF<has_1arg_insert<U>::value>		insert(const elem_type&  value)		{rg.insert(value);}
	template<class U=Rg>   eIF<has_1arg_insert<U>::value>		insert(      elem_type&& value)		{rg.insert(std::move(value));}

	template<class U=Rg>   eIF<has_pop_back<U>::value>		pop_back()				{rg.pop_back();}
	template<class U=Rg>   eIF<has_pop_front<U>::value>		pop_front()				{rg.pop_front();}
	
	template<class U=Rg>  auto  operator[] (difference_type n) -> decltype(std::declval<U>()[0])   { return  rg[n]; } // FIXME for pred

	////  ADDED RG METHODS
		template<class U=Rg>  
		eIF<is_c_string_t<U>::value>	
	push_back(char value)			{
		auto e=endz(rg);  
		assert(e < (rg + std::extent<rm_qualifier<U>>::value-1)); 
		*e = value; 
		*++e='\0';
	}

	//reference		get_value(rg_iterator      <Rg> it, ...) 			{ return  *it; };
	//const_reference		get_value(rg_const_iterator<Rg> it, ...) 		const	{ return  *it; };

	reference		get_value(rg_iterator      <Rg> it, ...) 		{ return  *it; };
	const_reference		get_value(rg_const_iterator<Rg> it, ...) 	const	{ return  *it; };

	reference		get_value(rg_iterator      <Rg> it, mk_type(MAPPED))		{ return  f(*it); };
	const_reference		get_value(rg_const_iterator<Rg> it, mk_type(MAPPED))	const	{ return  f(*it); };
 };



////////////////////////////////////////////////////////////////  TRAITS

template<class Rg, int FTP, class F, class O>		struct is_range_t<chain_range<Rg,FTP,F,O>>		: std::true_type  {};
template<class Rg, int FTP, class F, class O, bool RO>	struct is_range_t<chain_range_iterator<Rg,FTP,F,O,RO>>	: std::false_type {};


template<class Rg>					struct is_chain_range               			: std::false_type {};
template<class Rg, int FTP, class F, class O>		struct is_chain_range<chain_range<Rg,FTP,F,O>>		: std::true_type {};

template<class It>					struct is_chain_range_iterator      			: std::false_type {};
template<class Rg, int FTP, class F, class O, bool RO>	struct is_chain_range_iterator <chain_range_iterator<Rg,FTP,F,O,RO>> 		: std::true_type {};


////////////////////////////////////////////////////////////////  FUNCTION RANGE() -- range maker

	template<class Rg>   
	eIF<is_range<Rg>::value, chain_range<Rg&&>>   
range(Rg&& rg)  {
	return  chain_range<Rg&&>(std::forward<Rg>(rg));  // there is no copy on return
 };
////////////////////////////////////////////////////////////////  PIPE


//  Rg1 | Pred    --> range
template<class Rg>		eIF<is_range<Rg>::value,  chain_range<Rg&&,PREDICATED,std::function<bool(const rg_elem_type<Rg>&)> >>	operator|  (Rg&& rg,  std::function<bool(const rg_elem_type<Rg>&)> pred) { return   chain_range<Rg&&,PREDICATED,std::function<bool(const rg_elem_type<Rg>&)>> (std::forward<Rg>(rg),  pred); };
template<class Rg>		eIF<is_range<Rg>::value,  chain_range<Rg&&,PREDICATED,std::function<bool(rg_elem_type<Rg>)>        >>	operator|  (Rg&& rg,  std::function<bool(rg_elem_type<Rg>)>        pred) { return   chain_range<Rg&&,PREDICATED,std::function<bool(rg_elem_type<Rg>)>       > (std::forward<Rg>(rg),  pred); };
template<class Rg>		eIF<is_range<Rg>::value,  chain_range<Rg&&,PREDICATED,bool(*)(const rg_elem_type<Rg>&)             >>	operator|  (Rg&& rg,  bool(pred)(const rg_elem_type<Rg>&)              ) { return   chain_range<Rg&&,PREDICATED,bool(*)(const rg_elem_type<Rg>&)            > (std::forward<Rg>(rg),  pred); };
template<class Rg>		eIF<is_range<Rg>::value,  chain_range<Rg&&,PREDICATED,bool(*)(rg_elem_type<Rg>)                    >>	operator|  (Rg&& rg,  bool(pred)(rg_elem_type<Rg>)                     ) { return   chain_range<Rg&&,PREDICATED,bool(*)(rg_elem_type<Rg>)                   > (std::forward<Rg>(rg),  pred); };
template<class Rg, class F>	eIF<is_range<Rg>::value && is_callable<F, bool(rg_elem_type<Rg>)>::value,  chain_range<Rg&&,PREDICATED,F>> 
								 		operator|  (Rg&& rg,  F pred)                      { return   chain_range<Rg&&,PREDICATED,F> (std::forward<Rg>(rg),  pred); };
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
	
	

////////////////////////////////////////////////////////////////////////////////  MAP:  Rg<T> * F    --> Rg<U>

//// generic overload (O!=E) (lambdas, other)


	template<
		class Rg,
		class E = rg_elem_type<Rg>,
		class F,
		class O= rm_ref<decltype(std::declval<F>()(std::declval<E>()))>
	> 
	eIF <is_range<Rg>::value  &&  is_callable<F, O(E)>::value  && !has_result_type<F>::value,   chain_range<Rg&&,MAPPED,F,O>>
operator*       (Rg&& rg,  F f)    {
	return   chain_range<Rg&&,MAPPED,F,O> (std::forward<Rg>(rg),  f);
 };


//// FO 

	template<
		class Rg,
		class F,
		class E = rg_elem_type<Rg>,
		class O = typename F::result_type
	> 
	eIF <is_range<Rg>::value  &&  is_callable<F, O(E)>::value  && has_result_type<F>::value,   chain_range<Rg&&,MAPPED,F,O>>
operator*       (Rg&& rg,  F f)    {
	return   chain_range<Rg&&,MAPPED,F,O> (std::forward<Rg>(rg),  f);
 };

///////////////////////////////////  TUPLES


						// limitation: max N must equal 2, used tuple-arg N's must be >= 2
#define MK_TUPLE_OVERLOAD(N,CONST)       	                                                              	\
													\
	template<											\
		class Rg,										\
		class E=rg_elem_type<Rg>,								\
		class O=typename std::tuple_element<N,E>::type						\
	>												\
													\
	eIF <												\
		is_range<Rg>::value  &&  ( N==0  || 							\
			!std::is_same<typename std::tuple_element<0,E>::type, typename std::tuple_element<N,E>::type>::value  \
		), 											\
		chain_range<Rg&&,MAPPED, O CONST&(*)(E CONST&), O>					\
	>												\
													\
	operator*	(Rg&& rg, typename std::tuple_element<N,E>::type CONST &(*f)(E CONST &))    { 	\
		return   chain_range<Rg&&,MAPPED, O CONST& (*)(E CONST&), O> (std::forward<Rg>(rg), f);	\
	};


MK_TUPLE_OVERLOAD(0,)
MK_TUPLE_OVERLOAD(0,const)
MK_TUPLE_OVERLOAD(1,)
MK_TUPLE_OVERLOAD(1,const)


//// non-converting overload  (O == E),   needed for functions like std::abs()

	template<	
		class Rg,
		class E = rg_elem_type<Rg>,
		class O = E
	> 
	eIF <is_range<Rg>::value  &&  std::is_same<rm_qualifier<O>,rm_qualifier<E>>::value,  chain_range<Rg&&,MAPPED, O(*)(E), E>>
operator *       (Rg&& rg, O (*f)(E) )    {
	return   chain_range<Rg&&,MAPPED, O(*)(E), E>  (std::forward<Rg>(rg), f);
 };



//////////////////////////////////////////////////////////////////////  Rg || F   ---  accumulate(+C+1,-C, ++C, F) -> D  		 

	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>::value, R>					// const T&(cont T&,cont T&) -- plain functions
operator ||       (Rg&& rg, const R& (*f)(const T&, const T&) )    {
	auto i = std::next(std::begin(rg));
	return  std::accumulate(i, endz(rg), front(rg), f);
 };
	
	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>::value, R>					// T(cont T&,cont T&) -- plain functions
operator ||       (Rg&& rg, R (*f)(const T&, const T&) )    {
	auto i = std::next(std::begin(rg));
	return  std::accumulate(i, endz(rg), front(rg), f);
 };
	
	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>::value, R>							// overload for: lambda, std::plus
operator ||       (Rg&& rg, identity<std::function<T(const T&, const T&)>> f )    {
	auto i = std::next(std::begin(rg));
	const T init = front(rg);
	return  std::accumulate(i, endz(rg), init, f);
 };



						}; 
						#endif //  STO_CHAIN_RANGE_H
