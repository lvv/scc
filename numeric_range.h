#ifndef  STO_NUMERIC_RANGE_H
#define  STO_NUMERIC_RANGE_H

#include "scc/meta.h"
#include "scc/iterator_range.h"


/////////////////////////////////////////////////////////////////////////////////////////  NUMERIC_RANGE


	template<typename T>
struct  numeric_range {

		typedef		T		value_type;
		typedef		size_t		difference_type;
		typedef		size_t		size_type;
		typedef		const T*	const_pointer;
		typedef		const_pointer	pointer;
		typedef		const T&	const_reference;
		typedef		const_reference	reference;

	struct	const_iterator {
		explicit const_iterator (const numeric_range<T>& range, T current)
			:	range		(range), 
				current		(current),
				i		(0)
		{};



			typedef		std::input_iterator_tag		iterator_category;

			
			typedef		T		value_type;
			typedef		size_t		difference_type ;
			typedef		size_t		size_type ;
			typedef		const T*	const_pointer ;
			typedef		const_pointer	pointer ;
			typedef		const T&	const_reference ;
			typedef		const_reference	reference ;
		

		const numeric_range<T>&		range;
		T				current;
		size_t				i;	

		const_reference	operator*()	const	{ return   current; }
		const_pointer	operator->()	const	{ return  &current; } // what is this for?
		const_iterator&	operator++()		{ current+=range.step; ++i;  return *this; }
		const_iterator&	operator++(int)		{ auto tmp=*this;  current+=range.step;  ++i; return tmp; }

				// we take assumpation that comparission is done only with  end()
		bool		operator==(const const_iterator &rhs)	const	{ return   std::abs(rhs.current-current) < std::abs(range.step); }
		bool		operator!=(const const_iterator &rhs)	const	{ return   ! (*this == rhs); }
	};

		typedef		const_iterator		iterator;

	T from, to, step;

	// CTOR
	numeric_range()  			: from(T()),  to(T()), step(T())  {};
	numeric_range(T from, T to, T step=1)	: from(from), to(to), step(step) {};

	const_iterator	cbegin() const	{ return const_iterator(*this, from); };
	const_iterator	cend()   const	{ return const_iterator(*this, to); };
	const_iterator	begin()	 const	{ return cbegin(); };
	const_iterator	end()    const	{ return cend(); };

 };
////////////////////////////////////////////////////////////////  TRAITS

template<typename T>	struct  is_range_t     <numeric_range<T>>	: std::true_type  {};
template<typename T>	struct  is_iterable_t  <numeric_range<T>>	: std::true_type  {};


////////////////////////////////////////////////////////////////  RANGE() -- range maker

	template<class T1, class T2, class T3=T1, class T=decltype(T1()+T2()+T3())>
	eIF<std::is_arithmetic<T>::value,  numeric_range<T>>
range(T1 from,  T2 to,  T3 step=1) { return numeric_range<T>(from, to, step); };

#endif //  STO_NUMERIC_RANGE_H
