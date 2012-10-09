						#ifndef  STO_NUMERIC_RANGE_H
						#define  STO_NUMERIC_RANGE_H

						#include "scc/meta.h"
						#include "scc/functor.h"
						#include "scc/iterator_range.h"

						namespace sto {

/////////////////////////////////////////////////////////////////////////////////////////  NUMERIC_RANGE


	template<typename T>
struct  numeric_range {


			typedef		rm_ref<T>	value_type;
			typedef		size_t		difference_type ;
			typedef		size_t		size_type;
			typedef		const T*	const_pointer;
			typedef		const_pointer	pointer;
			typedef		value_type	const_reference;
			typedef		value_type	reference;

	struct	const_iterator {
		explicit const_iterator (const numeric_range<T>* range, T cur)
			:	range		(range), 
				cur		(cur),
				i		(0)
		{};



			typedef		std::input_iterator_tag		iterator_category;

			
			typedef		rm_ref<T>	value_type;
			typedef		size_t		difference_type ;
			typedef		size_t		size_type;
			typedef		const T*	const_pointer;
			typedef		const_pointer	pointer;
			typedef		value_type	const_reference;
			typedef		value_type	reference;
		

		const_reference	operator*()	const	{ return   cur; }
		const_pointer	operator->()	const	{ return  &(operator*()); }
		const_iterator&	operator++()		{ cur+=range->step;  ++i;   return *this; }
		const_iterator&	operator++(int)		{ auto tmp=*this;  cur+=range->step;  ++i;  return tmp; }

				// we make assumpation that comparission is done only with  end()
		bool		operator==(const const_iterator &rhs)	const	{ return   sto::abs(rhs.cur-cur) < sto::abs(range->step); }
		bool		operator!=(const const_iterator &rhs)	const	{ return   ! (*this == rhs); }

	   private:
		const numeric_range<T>*		range;
		T				cur;
		size_t				i;	

	};

		typedef		const_iterator		iterator;

	T from, to, step;

	// CTOR
	numeric_range()  			: from(T()),  to(T()), step(T())  {};
	numeric_range(T from, T to, T step=1)	: from(from), to(to),  step(step) {};

	const_iterator	cbegin() const	{ return const_iterator(this, from); };
	const_iterator	cend()   const	{ return const_iterator(this, to); };
	const_iterator	begin()	 const	{ return cbegin(); };
	const_iterator	end()    const	{ return cend(); };


	// RG PROPERTIES
	size_t		size  () const	{ return (to - from)/step; };
	bool		empty () const	{ return size() == 0; }
	explicit operator bool() const	{ return !empty(); }


	// ELEM ACCESS
	value_type  	front()  const	{ return  from; }
	value_type  	back()   const	{ return  size() * step; }  


 };
////////////////////////////////////////////////////////////////  ADD-TO: TRAITS

template<class T>	struct  is_range_t  <numeric_range<T>>	: std::true_type  {};


////////////////////////////////////////////////////////////////  RANGE() -- range maker

	template<class T1, class T2, class T3=T1, class T=decltype(T1()+T2()+T3())>
	eIF<std::is_arithmetic<T>::value,  numeric_range<T>>
range(T1 from,  T2 to,  T3 step=1) { return numeric_range<T>(from, to, step); };

	template<class T>
	eIF<std::is_arithmetic<T>::value,  numeric_range<T>>
range(T to) { return numeric_range<T>(0, to, 1); };

						};
						#endif //  STO_NUMERIC_RANGE_H
