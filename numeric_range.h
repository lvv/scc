						#ifndef  STO_NUMERIC_RANGE_H
						#define  STO_NUMERIC_RANGE_H

						#include "scc/meta.h"
						#include "scc/functor.h"
						#include "scc/iterator_range.h"

						namespace sto {

/////////////////////////////////////////////////////////////////////////////////////////  NUMERIC_RANGE


	template<typename T>
struct  numeric_range {

			// stl types
			typedef		rm_ref<T>		value_type;
			typedef		size_t			difference_type ;
			typedef		size_t			size_type;
			typedef		const value_type*	const_pointer;
			typedef		const_pointer		pointer;
			typedef		value_type		const_reference;
			typedef		value_type		reference;


	struct	const_iterator {

		// CTOR
		explicit const_iterator (const numeric_range<T>* range, size_t current)
			:	range		(range), 
				current		(current)
		{};
			typedef		const_iterator		self_type;

		// STL TYPES
		typedef		rm_ref<T>		value_type;
		typedef		size_t			difference_type ;
		typedef		size_t			size_type;
		typedef		const value_type*	const_pointer;
		typedef		const_pointer		pointer;
		typedef		value_type		const_reference;
		typedef		value_type		reference;

		// 
		
		T get_value(int i) 		const	{  assert( 0 <= i && i <= range->range_end);  return range->from  +  i * range->step; }

		// forward  iter
		const_reference	operator*()	const	{ return   get_value(current); }
		const_pointer	operator->()	const	{ return  &(operator*()); }
		const_iterator&	operator++()		{ ++current;   return *this; }
		const_iterator&	operator++(int)		{ auto tmp=*this;  ++current;  return tmp; }

		bool		operator==(const const_iterator &rhs)	const	{ return   rhs.current == current; }
		bool		operator!=(const const_iterator &rhs)	const	{ return   ! (*this == rhs); }

		#ifndef NR_INPUT_ITERATOR
			typedef		std::input_iterator_tag			iterator_category;
		#else 
			typedef		std::random_access_iterator_tag		iterator_category;
				// we make assumpation that comparission is done only with  end()
		// bidi iter 
		const_iterator&	operator--()		{ --current;   assert(current>=0); return *this; }
		const_iterator&	operator--(int)		{ auto tmp=*this;  --current;   assert(current>=0); return tmp; }

		// random access iter
		const_iterator	operator+= (difference_type n)	{ current+=n;  assert(current<=range->range_end);  return *this; }
		const_iterator	operator-= (difference_type n)	{ current-=n;  assert(current=>0);           return *this; }
		value_type	operator[] (difference_type n)	{ return get_value(n); }
		bool		operator<  (self_type other)	{ return current <  other.current; } 
		bool		operator<= (self_type other)	{ return current <= other.current; } 
		bool		operator>  (self_type other)	{ return current >  other.current; } 
		bool		operator>= (self_type other)	{ return current >= other.current; } 
		#endif


	   private:
		const numeric_range<T>*		range;
		size_t				current;	

	};

		typedef		const_iterator		iterator;

	// MEMBERS
	T from, to, step;
	size_t range_end;

	// CTOR
	numeric_range()  			: from(T()),  to(T()), step(T())  {};
	numeric_range(T from, T to, T step)	: from(from), to(to),  step(step),  range_end((to-from)/step)  { assert((to-from)*step > 0);};

	const_iterator	cbegin() const	{ return const_iterator(this, 0); };
	const_iterator	cend()   const	{ return const_iterator(this, range_end); };
	const_iterator	begin()	 const	{ return cbegin(); };
	const_iterator	end()    const	{ return cend(); };


	// RG PROPERTIES
	size_t		size  () const	{ return range_end; };
	bool		empty () const	{ return size() == 0; }
	explicit operator bool() const	{ return !empty(); }


	// ELEM ACCESS
	value_type  	front()  const	{ return  from; }
	value_type  	back()   const	{ return  size() * step; }  
	value_type	operator[] (difference_type n)	{ return from+step*n; }


 };
////////////////////////////////////////////////////////////////  ADD-TO: TRAITS

template<class T>	struct  is_range_t  <numeric_range<T>>	: std::true_type  {};


////////////////////////////////////////////////////////////////  RANGE() -- range maker

	template<class T1, class T2, class T=decltype(T1()+T2())>
	eIF<std::is_arithmetic<T>::value,  numeric_range<T>>
range(T1 from,  T2 to) { return numeric_range<T>(from, to, from<to ? 1 : -1); };

	template<class T1, class T2, class T3, class T=decltype(T1()+T2()+T3())>
	eIF<std::is_arithmetic<T>::value,  numeric_range<T>>
range(T1 from,  T2 to,  T3 step) { return numeric_range<T>(from, to, step); };

	template<class T>
	eIF<std::is_arithmetic<T>::value,  numeric_range<T>>
range(T to) { return numeric_range<T>(0, to, 1); };

						};
						#endif //  STO_NUMERIC_RANGE_H
