
						#ifndef  STO_MAPPED_RANGE_H
						#define  STO_MAPPED_RANGE_H

						#include "scc/basic_range.h"

						namespace sto {

	// forward dcl
	template< class Rg, class F = void*, class O = rg_elem_type<Rg> >  struct  mapped_range;

	template <class Rg, class F, class O, bool RO>
struct mapped_range_iterator : basic_range_iterator<Rg,RO> {

	typedef   basic_range_iterator<Rg,RO>  b;

	typedef	SEL <
		RO,
		mapped_range<Rg,F,O> const,
		mapped_range<Rg,F,O>
	>  parent_t;

	// if this line is uncommented - clang ICE in pre 2012-11-11 versions
	// parent_t * const & parent_p = (parent_t*)(b::parent_p);

	// STL ITERATOR TYPES
	
	// to edit
	typedef		mapped_range_iterator<Rg,F,O,RO>	iterator;
	typedef		mapped_range_iterator<Rg,F,O,true>	const_iterator;
	typedef		rm_ref<mapped_range_iterator>		self_type;

	typedef		typename b::iterator_category 		iterator_category;
	typedef		typename b::org_iterator 		org_iterator;
	typedef		O					value_type;

	using							typename b::size_type;
	using							typename b::difference_type;
	using							typename b::pointer;

	typedef         value_type				const_reference;
	typedef		value_type				reference;

	// non-STL
	using 							typename b::elem_type;

	////// MEMBERS

	
	////// CTOR
	mapped_range_iterator (const self_type& rhs)				: b(rhs)  		{};  // copy 
	mapped_range_iterator (parent_t* parent_p,  const org_iterator current)	: b(parent_p, current)	{};


	////// CONVERSION  non-const --> const
	//operator mapped_range_iterator<Rg&&,F,O,true>() { return mapped_range_iterator<Rg&&,F,O,true>(parent_p, b::current); };
	operator mapped_range_iterator<Rg&&,F,O,true>() { return mapped_range_iterator<Rg&&,F,O,true>((parent_t*)b::parent_p, b::current); };

	////// IFACE
	//reference	operator*()  		{ return  (parent_p->f)(*b::current); };
	//const_reference operator*() const 	{ return  (parent_p->f)(*b::current); };
	reference	operator*()  		{ return  ((parent_t*)b::parent_p)->f(*b::current); };
	const_reference operator*() const 	{ return  ((parent_t*)b::parent_p)->f(*b::current); };

	pointer		operator->()		{ return  &(operator*()); }
	pointer	const 	operator->() const	{ return  &(operator*()); }
	// ++ It
	using 		b::operator++;

	bool		operator==(const_iterator rhs)	const	{ return   b::current == rhs.current; }
	bool		operator!=(const_iterator rhs)	const	{ return   b::current != rhs.current; }

	///////////////////////////////////////////////////////////////////// INPORT ORG_ITERATOR METHODS
	
	//  bidiractional 
	using 		b::operator--;
	                                                          
	// random access
	using		b::operator+=;
	using		b::operator-=;
	using		b::operator[];
	using		b::operator<;
	using		b::operator<=;
	using		b::operator>;
	using		b::operator>=;
 };



/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE
	template<class Rg, class F, class O>
struct  mapped_range : basic_range<Rg> {

	typedef   basic_range<Rg>  b;

	// STL IFACE
	typedef		O  						value_type;
	typedef		mapped_range_iterator<Rg,F,O,false>    		iterator;
	typedef		mapped_range_iterator<Rg,F,O,true>		const_iterator;

	typedef		size_t  					size_type;
	typedef		ptrdiff_t 					difference_type ;
	typedef		rm_ref<value_type>*				pointer;

	typedef         rg_const_reference<Rg>     const_reference;  // non-STL
	typedef		typename std::conditional <
				std::is_const<Rg>::value /* || RO*/,      // <-- different from interator
				rg_const_reference<Rg>,
				rg_reference<Rg>
			 >::type					reference;

	// non-STL
	typedef		rg_elem_type<Rg>  				elem_type;
	typedef		mapped_range					self_type;


	// MEMBERS
	F f;

	////  CTOR 
	explicit mapped_range (Rg&& rg, F f) :   b(std::forward<Rg>(rg)),   f(f) {};


	////  ASSIGNMENT
	using b::operator=;


	////  ITERATOR
	      iterator	end()		{ return        iterator(this, endz(b::rg)); }
	const_iterator	end()   const	{ return  const_iterator(this, endz(b::rg)); }

	      iterator	begin()		{ return        iterator(this, std::begin(b::rg)); };
	const_iterator	begin()	const	{ return  const_iterator(this, std::begin(b::rg)); };


	////  RG PROPERTIES
	using b::size;
	using b::empty;
	using b::operator bool;

	////  ELEM ACCESS
	reference const	front()  const	{ return  *std::begin(b::rg); }
	reference  	front()		{ return  *std::begin(b::rg); }

	reference const back()  const	{ return  *std::prev(sto::endz(b::rg)); }  
	reference  	back()		{ return  *std::prev(sto::endz(b::rg)); } 


	////  INPORTED RG METHODS
	using b::push_front;
	using b::push_back;
	using b::insert;
	using b::pop_front;
	using b::pop_back;
	using b::operator[];
 };



////////////////////////////////////////////////////////////////  TRAITS

template<class Rg, class F, class O>		struct is_range_t<mapped_range<Rg,F,O>>			: std::true_type  {};
template<class Rg, class F, class O, bool RO>	struct is_range_t<mapped_range_iterator<Rg,F,O,RO>>	: std::false_type {};

template<class Rg, class F, class O>		struct is_sto_range<mapped_range<Rg,F,O>>		: std::true_type {};

template<class Rg, class F, class O, bool RO>	struct is_sto_range_iterator <mapped_range_iterator<Rg,F,O,RO>> 		: std::true_type {};


////////////////////////////////////////////////////////////////////////////////  MAP:  Rg<T> * F    --> Rg<U>

//// generic overload (O!=E) (lambdas, other)


	template<
		class Rg,
		class E = rg_elem_type<Rg>,
		class F,
		class O= rm_ref<decltype(std::declval<F>()(std::declval<E>()))>
	> 
	eIF <is_range<Rg>::value  &&  is_callable<F, O(E)>::value  && !has_result_type<F>::value,   mapped_range<Rg&&,F,O>>
operator*       (Rg&& rg,  F f)    {
	return   mapped_range<Rg&&,F,O> (std::forward<Rg>(rg),  f);
 };


//// FO 

	template<
		class Rg,
		class F,
		class E = rg_elem_type<Rg>,
		class O = typename F::result_type
	> 
	eIF <is_range<Rg>::value  &&  is_callable<F, O(E)>::value  && has_result_type<F>::value,   mapped_range<Rg&&,F,O>>
operator*       (Rg&& rg,  F f)    {
	return   mapped_range<Rg&&,F,O> (std::forward<Rg>(rg),  f);
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
		mapped_range<Rg&&, O CONST&(*)(E CONST&), O>					\
	>												\
													\
	operator*	(Rg&& rg, typename std::tuple_element<N,E>::type CONST &(*f)(E CONST &))    { 	\
		return   mapped_range<Rg&&, O CONST& (*)(E CONST&), O> (std::forward<Rg>(rg), f);	\
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
	eIF <is_range<Rg>::value  &&  std::is_same<rm_qualifier<O>,rm_qualifier<E>>::value,  mapped_range<Rg&&, O(*)(E), E>>
operator *       (Rg&& rg, O (*f)(E) )    {
	return   mapped_range<Rg&&, O(*)(E), E>  (std::forward<Rg>(rg), f);
 };

						};
						#endif //  STO_MAPPED_RANGE_H
