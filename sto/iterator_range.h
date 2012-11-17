
						#ifndef  STO_ITERATOR_RANGE_H
						#define  STO_ITERATOR_RANGE_H

						#include <sto/meta.h>
						namespace sto {

/////////////////////////////////////////////////////////////////////////////////////////  ITERATOR_RANGE

	template<typename I>
struct  iterator_range {
		typedef		      I							iterator;
		typedef		const I							const_iterator;
		typedef		typename std::iterator_traits<rm_ref<I>>::value_type		value_type;
		typedef		typename std::iterator_traits<I>::difference_type	difference_type ;
		typedef		typename std::iterator_traits<I>::pointer		pointer ;
		typedef		typename std::iterator_traits<I>::reference		reference ;
	iterator b_, e_;

	// CTOR
	iterator_range()  : b_(0), e_(0) {};
	iterator_range(iterator b, iterator e)  : b_(b), e_(e) {};

	// ASSIGNMENT
	iterator_range& operator= (value_type x) { std::fill(b_, e_, x);  return *this; };

		template<typename rhsRn>
		eIF <is_elem_of<value_type, rhsRn>::value, iterator_range&>
	operator= (const rhsRn& rhs) {
		auto it= b_;
		for (const auto &x: rhs)  {
			if (it==e_) break; 
			*it++ = x;
		}
		return *this;
	}




	//template<typename Rg>
	//iterator_range( typename std::enable_if<std::is_same<I, typename Rg::iterator>::value, Rg>::type&  C)  : b_(begin(C)), e_(end(C)) {};

	iterator	begin()		{ return b_; };
	iterator	end()		{ return e_; };
	const_iterator	begin() const	{ return b_; };
	const_iterator	end()   const	{ return e_; };



	/* to bool conversion --
	*/
	 
			struct PointerConversion { int valid; };
			typedef int PointerConversion::* datamemptr;

	operator datamemptr  () const {
		return  (b_ != e_) ? &PointerConversion::valid : 0;
	};

 };

////////////////////////////////////////////////////////////////  TRAITS

//template<typename T>	struct  is_range_t	<iterator_range<T>> 	: std::true_type  {};
template<typename I>	struct  is_range_t	<iterator_range<I>>	: std::true_type { };


////////////////////////////////////////////////////////////////  RANGE() -- range maker

	template<typename I>
	eIF<is_iterator<I>::value, iterator_range<I>>
range(I b, I e) { return iterator_range<I>(b,e); };

	
////////////////////////////////////////////////////////////////  SIMPLE PIPE

	template<class Rg> 					// for std::unique
	eIF <is_range<Rg>::value,  iterator_range<rg_iterator<Rg>>>
operator| (Rg&& rg, rg_iterator<Rg> (*f)(rg_iterator<Rg> b, rg_iterator<Rg> e) )    {
	auto b     = std::begin(rg);
	auto new_e = f(b,std::end(rg));
	// TODO: add erase	
	return iterator_range<rg_iterator<Rg>>(b,new_e);
 }

						};
						#endif //  STO_ITERATOR_RANGE_H
