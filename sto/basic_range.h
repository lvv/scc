
						#ifndef  STO_CHAIN_RANGE_H
						#define  STO_CHAIN_RANGE_H

						#include <sto/meta.h>
						#include <sto/stl.h>

						/*
						#ifndef NDEBUG
						#include <iostream>
						#include <sto/debug.h>
						#endif
						*/

						namespace sto {
						//template<class Ch> class basic_string<Ch>;

/////////////////////////////////////////////////////////////////////////////////////////  CHAIN_RANGE_ITERATOR
	template<class Rg>  struct  basic_range;

	template <class Rg, bool RO>
struct basic_range_iterator {
				

		// TYPES
		typedef SEL <
			RO,
			rg_const_iterator<Rg>,
			rg_iterator<Rg>
		>  org_iterator;

		typedef	SEL <
			RO,
			basic_range<Rg> const,
			basic_range<Rg>
		>  parent_t;


	// MEMBERS
	parent_t*	parent_p;
	org_iterator	current;


	// STL ITERATOR TYPES
	typedef		typename std::iterator_traits<org_iterator>::iterator_category 	iterator_category;

	typedef		typename parent_t::value_type			value_type;
	typedef		typename parent_t::const_iterator		const_iterator;
	typedef		basic_range_iterator<Rg,RO>			iterator;

	typedef		size_t  					size_type;
	typedef		ptrdiff_t 					difference_type;
	typedef		SEL <RO, const rm_ref<value_type>*, rm_ref<value_type>*>   	pointer;

	typedef         rg_const_reference<Rg>     			const_reference;
	typedef		typename std::conditional <
				std::is_const<Rg>::value || RO,
				rg_const_reference<Rg>,
				rg_reference<Rg>
			>::type reference;


	// non-STL
	typedef		rg_elem_type<Rg>  				elem_type;
	typedef		rm_ref<basic_range_iterator>			self_type;
	typedef		self_type					type;

	////// CTOR
	basic_range_iterator ()				: parent_p(0)           			   {};	// default
	basic_range_iterator ( const self_type& rhs)	: parent_p(rhs.parent_p), current(rhs.current) {};	// copy 
	basic_range_iterator ( parent_t* parent_p,  const org_iterator current) 
							: parent_p(parent_p), current(current)         {};

	////// CONVERSION  non-const --> const
	operator basic_range_iterator<Rg&&,true>() { return basic_range_iterator<Rg&&,true>(parent_p, current); };

	////// IFACE
	reference	operator*()  		{ return  *current; };
	const_reference operator*() const 	{ return  *current; };

	pointer		operator->()		{ return  &(operator*()); }
	pointer	const 	operator->() const	{ return  &(operator*()); }

	// ++ It
	self_type&	operator++()		{ ++current;  return *this; }


	// ++ It
	self_type	operator++(int)		{
		org_iterator e = endz(parent_p->rg);
		assert(current !=e);
		self_type tmp=*this;
		++current;
		return std::move(tmp);
	}

	bool	operator==(const_iterator rhs)	const	{ return   current == rhs.current; }
	bool	operator!=(const_iterator rhs)	const	{ return   current != rhs.current; }

	///////////////////////////////////////////////////////////////////// INPORT ORG_ITERATOR METHODS
	
	//  bidiractional
	template<class U=org_iterator, class=decltype(std::declval<U>()--)> 			self_type&	operator--()			{ --current;  return *this; }
	template<class U=org_iterator, class=decltype(std::declval<U>()--)> 			self_type	operator--(int)			{ self_type tmp=*this;  --current;   return std::move(tmp); }
	                                                          
	// random access
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
	template<class Rg>
struct  basic_range : ref_container<Rg&&> {


	// STL IFACE
	typedef		rg_elem_type<Rg>  				value_type;	// post-f type
	typedef		basic_range_iterator<Rg,false>     		iterator;
	typedef		basic_range_iterator<Rg,true>			const_iterator;

	typedef		size_t  					size_type;
	typedef		ptrdiff_t 					difference_type ;
	typedef		rm_ref<value_type>*				pointer;

	typedef         rg_const_reference<Rg>     			const_reference;  // non-STL
	typedef		typename std::conditional <
				std::is_const<Rg>::value /* || RO*/,      // <-- different from interator
				rg_const_reference<Rg>,
				rg_reference<Rg>
			>::type reference;


	// non-STL
	typedef		rg_elem_type<Rg>  				elem_type;	// pre-f type
	typedef		basic_range					self_type;

	// MEMBERS
	Rg&	rg;

	////  CTOR
	explicit basic_range(Rg&& rg)  : ref_container<Rg&&>(std::forward<Rg>(rg)), rg(this->value)  {};

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


	      iterator	begin()		{ return        iterator(this, std::begin(rg)); };
	const_iterator	begin()	const	{ return  const_iterator(this, std::begin(rg)); };


	////  RG PROPERTIES
	size_t		size  () const	{ return  sto::size (rg); };
	bool		empty () const	{ return  sto::empty(rg); }
	explicit operator bool() const	{ return !sto::empty(rg); }


	////  ELEM ACCESS
	reference const	front()  const	{ return  *std::begin(rg); }
	reference  	front()		{ return  *std::begin(rg); }

	reference const back()  const	{ return  *std::prev(sto::endz(rg)); }  
	reference  	back()		{ return  *std::prev(sto::endz(rg)); } 


	////  INPORTED RG METHODS
	template<class U=Rg>   eIF<has_push_back<U>::value>	push_back(const elem_type&  value)	{ rg.push_back(value);}
	template<class U=Rg>   eIF<has_push_back<U>::value>	push_back(      elem_type&& value)	{ rg.push_back(std::move(value));}

	template<class U=Rg>   eIF<has_push_front<U>::value>	push_front(const elem_type&  value)	{ rg.push_front(value);}
	template<class U=Rg>   eIF<has_push_front<U>::value>	push_front(      elem_type&& value)	{ rg.push_front(std::move(value));}

	template<class U=Rg>   eIF<has_1arg_insert<U>::value>	insert(const elem_type&  value)		{ rg.insert(value);}
	template<class U=Rg>   eIF<has_1arg_insert<U>::value>	insert(      elem_type&& value)		{ rg.insert(std::move(value));}

	template<class U=Rg>   eIF<has_pop_back<U>::value>	pop_back()				{ rg.pop_back();}
	template<class U=Rg>   eIF<has_pop_front<U>::value>	pop_front()				{ rg.pop_front();}

	// erase
	template<class U=Rg>   eIF<has_erase2<U>::value>	erase(rg_iterator<Rg> b, rg_iterator<Rg> e)	{ rg.erase(b,e);}
	template<class U=Rg>   eIF<has_erase1<U>::value>	erase(rg_iterator<Rg> p)			{ rg.erase(p);  }

	// cstr
	template<class U=Rg>   eIF<is_cstr<U>::value>		push_back(const elem_type&  value)	{ auto e=endz(rg);  *e=value; *++e='\0';}
	template<class U=Rg>   eIF<is_cstr<U>::value>		push_front(const elem_type&  value)	{ std::copy(rg, endz(rg)+1, rg+1); *rg=value;}
	template<class U=Rg>   eIF<is_cstr<U>::value>		pop_back()				{ *(endz(rg)-1) = '\0';}
	template<class U=Rg>   eIF<is_cstr<U>::value>		pop_front()				{ std::copy((rg+1), endz(rg)+1, rg);}
	template<class U=Rg>   eIF<is_cstr<U>::value>		erase(rg_iterator<Rg> b, rg_iterator<Rg> e)	{ std::copy(e,endz(rg)+1,b); }
	template<class U=Rg>   eIF<is_cstr<U>::value>		erase(rg_iterator<Rg> p)			{ std::copy(p+1,endz(rg)+1,p); }


	
	template<class U=Rg>  auto  operator[] (difference_type n) -> decltype(std::declval<U>()[0])   		{ return  rg[n]; } // FIXME for pred
 };



////////////////////////////////////////////////////////////////  TRAITS

template<class Rg>		struct is_range_t<basic_range<Rg>>		: std::true_type  {};
template<class Rg, bool RO>	struct is_range_t<basic_range_iterator<Rg,RO>>	: std::false_type {};

template<class Rg>		struct is_sto_range               		: std::false_type {};
template<class Rg>		struct is_sto_range<basic_range<Rg>>		: std::true_type {};

template<class It>		struct is_sto_range_iterator      		: std::false_type {};
template<class Rg, bool RO>	struct is_sto_range_iterator <basic_range_iterator<Rg,RO>> 	: std::true_type {};



////////////////////////////////////////////////////////////////  FUNCTION RANGE() -- range maker

	template<class Rg>   
	eIF<is_range<Rg>::value, basic_range<Rg&&>>   
range(Rg&& rg)  {
	return  basic_range<Rg&&>(std::forward<Rg>(rg));  // there is no copy on return
 };

//////////////////////////////////////////////////////////////////////  SIMPLE FOLD

// Rg || F   ---  accumulate(+C+1,-C, ++C, F) -> D  		 

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
 }
	
	template< typename Rg, typename T = rg_elem_type<Rg>, typename R = T > 
	eIF <is_range<Rg>::value, R>							// overload for: lambda, std::plus
operator ||       (Rg&& rg, identity<std::function<T(const T&, const T&)>> f )    {
	auto i = std::next(std::begin(rg));
	const T init = front(rg);
	return  std::accumulate(i, endz(rg), init, f);
 }

//////////////////////////////////////////////////////////////////////////////////////////  SIMPLE PIPE

//   Rg  |  void f(it,it) 		-- for std::sort, reverse, random_shuffle, ...

	template<class Rg> 
	eIF <is_range<Rg>::value,  Rg&&>
operator| (Rg&& rg, void (*f)(rg_iterator<Rg> b, rg_iterator<Rg> e) )    {
	f(std::begin(rg),std::end(rg));
	return  std::forward<Rg>(rg);
 }
	
						}; 
						#endif //  STO_CHAIN_RANGE_H
