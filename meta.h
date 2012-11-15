					#ifndef  STO_META_H
					#define  STO_META_H

					#include <type_traits>
					#include <functional>
					#include <iterator>
					#include <array>
					#include <list>
					#include <forward_list>
					#include <map>
					#include <set>
					#include <unordered_set>
					#include <unordered_map>
					#include <stack>
					#include <queue>
					#include <tuple>
					#include <algorithm>
					#include <string>

					namespace sto {

// TODO
// 	SFNIE with NOEXCEPT  --- http://nonchalantlytyped.net/blog/2012/06/27/yet-another-sfinae/

////////////////////////////////////////////////////////////////////////////////////////  META META

struct no_type{};
template<class T> struct identity_t{ typedef T type; };
template<class T> using  identity  = typename identity_t<T>::type;

template<class From, class To> struct copy_rcv			           { typedef To type; };
template<class From, class To> struct copy_rcv<From const            , To> { typedef typename copy_rcv<From, To> ::type const           type; };
template<class From, class To> struct copy_rcv<From volatile         , To> { typedef typename copy_rcv<From, To> ::type volatile        type; };
template<class From, class To> struct copy_rcv<From const volatile   , To> { typedef typename copy_rcv<From, To> ::type const volatile  type; };
template<class From, class To> struct copy_rcv<From &                , To> { typedef typename copy_rcv<From, To> ::type&                type; };
template<class From, class To> struct copy_rcv<From const&           , To> { typedef typename copy_rcv<From, To> ::type const&          type; };
template<class From, class To> struct copy_rcv<From volatile&        , To> { typedef typename copy_rcv<From, To> ::type volatile&       type; };
template<class From, class To> struct copy_rcv<From const volatile&  , To> { typedef typename copy_rcv<From, To> ::type const volatile& type; };
template<class From, class To> struct copy_rcv<From &&               , To> { typedef typename copy_rcv<From, To> ::type&&               type; };
template<class From, class To> struct copy_rcv<From const&&          , To> { typedef typename copy_rcv<From, To> ::type const&&         type; };
template<class From, class To> struct copy_rcv<From volatile&&       , To> { typedef typename copy_rcv<From, To> ::type volatile&&      type; };
template<class From, class To> struct copy_rcv<From const volatile&& , To> { typedef typename copy_rcv<From, To> ::type const volatile&& type; };


template<class T>     typename std::add_lvalue_reference<const T>::type const   decllval();

// shortcuts
template<class Rg>     using	rm_qualifier     = typename std::remove_cv<typename std::remove_reference<Rg>::type>::type;
template<class Rg>     using	rm_ref           = typename std::remove_reference<Rg>::type;
#define 			mk_type(x)	typename std::integral_constant<int,x>


////////////////////////////////////////////////////////////////////////////////////////  CL_TRAITS


template <typename T>		struct rg_traits      {
		template <typename U, typename VT = typename rm_ref<U>::value_type>	static VT	vt(rm_ref<U>* u);
		template <typename U>							static no_type	vt(...);
	typedef   decltype(vt<T>(0))   elem_type ;

		template <typename U, typename IT = typename rm_ref<U>::iterator>	static IT       it(rm_ref<U>* u);
		template <typename U>							static no_type  it(...);
	typedef   decltype(it<T>(0))   iterator;

		template <typename U, typename IT = typename rm_ref<U>::const_iterator>	static IT       cit(rm_ref<U>* u);
		template <typename U>							static no_type  cit(...);
	typedef   decltype(cit<T>(0))   const_iterator;

		template <typename U, typename RF = typename rm_ref<U>::reference>	static RF       rf(rm_ref<U>* u);
		template <typename U>                                          		static no_type  rf(...);
	typedef     decltype(rf<T>(0))     reference ;

		template <typename U, typename RF = typename rm_ref<U>::const_reference>static RF       crf(rm_ref<U>* u);
		template <typename U>                                          		static no_type  crf(...);
	typedef     decltype(crf<T>(0))     const_reference ;
};


template <typename T, size_t N> struct rg_traits<T[N]>     { typedef  T  elem_type;   typedef  T*  iterator;  typedef  const T*  const_iterator;   typedef  T&  reference;  typedef  const T&  const_reference; };
template <typename T, size_t N> struct rg_traits<T(&)[N]>  { typedef  T  elem_type;   typedef  T*  iterator;  typedef  const T*  const_iterator;   typedef  T&  reference;  typedef  const T&  const_reference; };


template<typename Rg>   using rg_elem_type      	= typename rg_traits<Rg>::elem_type;
template<typename Rg>   using rg_iterator       	= typename rg_traits<Rg>::iterator;
template<typename Rg>   using rg_const_iterator 	= typename rg_traits<Rg>::const_iterator;
template<typename Rg>   using rg_reference      	= typename rg_traits<Rg>::reference;
template<typename Rg>   using rg_const_reference	= typename rg_traits<Rg>::const_reference;


/////////////////////////////////////////////////////////////////////////////////////////////////  ERASABPLE_CATEGORY

struct non_erasable{};
struct cstr_erasable{};
struct vector_erasable{};
struct list_erasable{};
struct map_erasable{};

								non_erasable		erasable_category(...)                                 { return non_erasable(); }; 

template<size_t N>						cstr_erasable		erasable_category(char(&)[N])                          { return cstr_erasable(); }; 

template<class T, class A>					vector_erasable		erasable_category(std::vector<T,A>)                    { return vector_erasable(); }; 
template<class T, class A>					vector_erasable		erasable_category(std::deque<T,A>)                     { return vector_erasable(); }; 

template<class T, class A>					list_erasable		erasable_category(std::list<T,A>)                      { return list_erasable(); }; 
template<class T, class A>					list_erasable		erasable_category(std::forward_list<T,A>)              { return list_erasable(); }; 

template<class T, class C, class A>				map_erasable		erasable_category(std::set<T,C,A>)                     { return map_erasable(); }; 
template<class T, class C, class A>				map_erasable		erasable_category(std::multiset<T,C,A>)                { return map_erasable(); }; 
template<class T, class C, class A>				map_erasable		erasable_category(std::unordered_set<T,C,A>)           { return map_erasable(); }; 
template<class T, class C, class A>				map_erasable		erasable_category(std::unordered_multiset<T,C,A>)      { return map_erasable(); }; 

template<class K, class V, class C, class A>			map_erasable		erasable_category(std::map<K,V,C,A>)                   { return map_erasable(); }; 
template<class K, class V, class C, class A>			map_erasable		erasable_category(std::multimap<K,V,C,A>)              { return map_erasable(); }; 
template<class K, class V, class H, class KE, class A>		map_erasable		erasable_category(std::unordered_map<K,V,H,KE,A>)      { return map_erasable(); }; 
template<class K, class V, class H, class KE, class A>		map_erasable		erasable_category(std::unordered_multimap<K,V,H,KE,A>) { return map_erasable(); }; 


/////////////////////////////////////////////////////////////////////////////////////////////////  STD SHORTCUTS

template<bool Cnd, class T=void>     	using  eIF		= typename std::enable_if <Cnd,T>::type;
template<bool Cnd, class T1, class T2>	using  SEL		= typename std::conditional <Cnd,T1,T2>::type;
template<typename Rg>	                using  rg_elem_fwd	= typename  copy_rcv<Rg&&, rg_elem_type<Rg>>::type;
template<typename Rg>	                using  rg_iterator_fwd	= typename  copy_rcv<Rg&&, rg_iterator<Rg>>::type;

///template<class T, class TT=rm_qualifier<T>>  constexpr bool 
///is_cstr() { return std::is_array<TT>::value  &&  std::is_same<char, typename std::remove_extent<TT>::type>::value; }

template<class T, class TT=rm_qualifier<T>>
struct is_cstr { enum { value = std::is_array<TT>::value  &&  std::is_same<char, typename std::remove_extent<TT>::type>::value }; };




/////////////////////////////////////////////////////////////////////////////////////////////////  DEF_HAS_ ...


/*
#define DEF_HAS_MEMBER(NAME,MEMBER)										\
	namespace detail {											\
		template <class T>                                std::false_type	NAME##_ol(...);		\
		template <class T, class M = typename T::MEMBER>  std::true_type	NAME##_ol(T* t);	\
	}; 													\
	template<class T> constexpr bool NAME(const T& t)  { return  decltype(detail::NAME##_ol<rm_qualifier<T>>(0))::value; }; \
	template<class T> constexpr bool NAME()            { return  decltype(detail::NAME##_ol<rm_qualifier<T>>(0))::value; };



#define DEF_HAS_METHOD(NAME,METHOD)										\
	namespace detail {											\
		template <class T>					std::false_type	NAME##_ol(...);		\
		template <class T, class F = decltype (((T*)0)->METHOD)>std::true_type	NAME##_ol(T* u);	\
	}; 													\
	template<class T> constexpr bool NAME(T t)   { return  decltype(detail::NAME##_ol<rm_qualifier<T>>(0))::value; };\
	template<class T> constexpr bool NAME()      { return  decltype(detail::NAME##_ol<rm_qualifier<T>>(0))::value; };
*/

#define DEF_HAS_MEMBER(NAME,MEMBER)										\
	namespace detail {											\
		template <class T>                                std::false_type	NAME##_ol(...);		\
		template <class T, class M = typename T::MEMBER>  std::true_type	NAME##_ol(T* t);	\
	}; 													\
	template<class T> struct  NAME { enum { value = decltype(detail::NAME##_ol<rm_qualifier<T>>(0))::value }; };



#define DEF_HAS_METHOD(NAME,METHOD)										\
	namespace detail {											\
		template <class T>					std::false_type	NAME##_ol(...);		\
		template <class T, class F = decltype (((T*)0)->METHOD)>std::true_type	NAME##_ol(T* u);	\
	}; 													\
	template<class T> struct  NAME { enum { value = decltype(detail::NAME##_ol<rm_qualifier<T>>(0))::value }; };

DEF_HAS_MEMBER(has_iterator,iterator)
DEF_HAS_MEMBER(has_iterator_category,iterator_category)
DEF_HAS_MEMBER(has_result_type,result_type)
DEF_HAS_MEMBER(is_map,mapped_type)

DEF_HAS_METHOD(has_push_front,push_front(typename T::value_type()))
DEF_HAS_METHOD(has_push_back,push_back(typename T::value_type()))
DEF_HAS_METHOD(has_push,push(typename rm_ref<T>::value_type()))
DEF_HAS_METHOD(has_1arg_insert,insert(typename T::value_type()))
DEF_HAS_METHOD(has_insert,insert(typename T::iterator(), typename T::value_type()))
DEF_HAS_METHOD(has_pop_back,pop_back())
DEF_HAS_METHOD(has_pop_front,pop_front())
DEF_HAS_METHOD(has_pop,pop())
DEF_HAS_METHOD(has_size,size())
DEF_HAS_METHOD(has_empty,empty())
DEF_HAS_METHOD(has_resize,resize(size_t()))
DEF_HAS_METHOD(has_back,back())
DEF_HAS_METHOD(has_front,front())
DEF_HAS_METHOD(has_top,top())
DEF_HAS_METHOD(has_clear,clear())
DEF_HAS_METHOD(has_erase2,erase(rg_iterator<T>(), rg_iterator<T>()))
DEF_HAS_METHOD(has_erase1,erase(rg_iterator<T>()))


//////////////////////////////////////////////////////////////////////////////////////// IS_ITERABLE

	template <typename T>
struct is_range_t {

		template <
			class U,
			class I = typename U::const_iterator
		>
		static int8_t
	test(U* u);

		template <typename U>
		static int16_t
	test(...);

	//enum { value  =  sizeof test <rm_qualifier<T>> (0) == 1 };
	enum { value  =  sizeof test <T> (0) == 1 };
};



template<typename T, size_t N>	struct  is_range_t <T[N]>		: std::true_type {};
template<typename T, size_t N>	struct  is_range_t <std::array<T,N>>	: std::true_type {};

template<class T>	struct  is_range { enum { value = is_range_t<rm_qualifier<T>>::value };};
//template<typename T>     constexpr bool   is_range()        { return  is_range_t<rm_qualifier<T>>::value; };


//////////////////////////////////////////////////////////////////////////////////////  IS STRING
template<class T>	struct  is_string_t				: std::false_type {};
template<class CharT>	struct  is_string_t <std::basic_string<CharT>>	: std::true_type  {};
template<size_t N>	struct  is_string_t <char[N]>			: std::true_type  {};
template<class T>	struct  is_string { enum { value = is_string_t<rm_qualifier<T>>::value };};

//template<class T>     constexpr bool   is_string()        { return  is_string_t<rm_qualifier<T>>::value; };

//////////////////////////////////////////////////////////////////////////////////////  IS_IOABLE
			// alt impl:  http://stackoverflow.com/questions/257288/is-it-possible-to-write-a-c-template-to-check-for-a-functions-existence/9154394#9154394
template<typename T>	struct  is_ioable_t 		: std::conditional<std::is_arithmetic<T>::value, std::true_type, std::false_type>::type  {};
template<typename T,typename CT,typename AL>
			struct  is_ioable_t <std::basic_string<T,CT,AL>>	: std::true_type  {};
template<size_t N>	struct  is_ioable_t <char[N]>	: std::true_type  {};
template<>		struct  is_ioable_t <char*>	: std::true_type  {};
template<>		struct  is_ioable_t <const char*>	: std::true_type  {};

template<class T>	struct  is_ioable { enum { value = is_ioable_t<rm_qualifier<T>>::value };};
//template<typename T>     constexpr bool   is_ioable()        { return  is_ioable_t<rm_qualifier<T>>::value; };


//////////////////////////////////////////////////////////////////////////////////////  IS_STACK
	template <typename T>
struct is_stack {

		template <
			typename U,
			typename POP	= decltype (((U*)0)->pop()),
			typename TOP	= decltype (((U*)0)->top())
		>
		static int8_t
	test(U* u);

		template <typename U>
		static int16_t
	test(...);

	enum { value = sizeof test<rm_qualifier<T>>(0) == 1 };
};
//template<typename T>     constexpr bool   is_stack()        { return  is_stack_t<rm_qualifier<T>>::value; };


//////////////////////////////////////////////////////////////////////////////////////  IS_QUEUE
	template <typename T>
struct is_queue {

		template <
			typename U,
			typename POP	= decltype (((U*)0)->pop()),
			typename FRONT	= decltype (((U*)0)->front()),
			typename BACK	= decltype (((U*)0)->back())
		>
		static int8_t
	test(U* u);

		template <typename U>
		static int16_t
	test(...);

	enum { value = sizeof test<rm_qualifier<T>>(0) == 1 };
};
//template<typename T>     constexpr bool   is_queue()        { return  is_queue_t<rm_qualifier<T>>::value; };



//////////////////////////////////////////////////////////////////////////////////////  IS_ITERATOR

// TO CHECK: better(?) is_iterator --
// 	http://stackoverflow.com/questions/12161109/stdenable-if-or-sfinae-for-iterator-or-pointer
//	http://gcc.gnu.org/bugzilla/show_bug.cgi?id=40497#c23

/*
	template<typename T>    
	constexpr bool  
is_iterator()        {
	return  has_iterator_category<T>() 
		|| (std::is_pointer<T>::value  &&  ! std::is_function<typename std::remove_pointer<T>::type>::value);
};*/

	template<typename T>    
struct is_iterator   {
	enum { value =
		has_iterator_category<T>::value 
		|| (std::is_pointer<T>::value  &&  ! std::is_function<typename std::remove_pointer<T>::type>::value)
	};
};

	template<typename T>
struct is_input_iterator_t {
					static int16_t	test (...);					// no match
	template<typename  U>		static int8_t	test (decltype(std::declval<U>()++)**);		// Pointer
	template<typename  U, size_t N>	static int8_t	test (decltype(std::declval<U>()++)(*)[N]);	// C-array
	template<typename  U>		static 
		eIF<std::is_base_of<std::input_iterator_tag, typename U::iterator_category>::value, int8_t>
							test (U*);					// Iterator 

	static const bool value = sizeof(test((typename std::remove_reference<T>::type*)nullptr)) == 1;
};

	template<class T, class TAG> 	
struct is_iterator_of {
				static int16_t	test (...);					// no match
	template<typename U>	static eIF<std::is_pointer<U>::value && ! std::is_function<typename std::remove_pointer<T>::type>::value,
										std::random_access_iterator_tag>	test (U*);	// Pointer
	template<typename U>	static eIF<std::is_array<U>::value,		std::random_access_iterator_tag>	test (U*);	// C-array
	template<typename U>	static eIF<has_iterator_category<U>::value,	typename U::iterator_category>		test (U*);	// Iterator 

	enum { value = std::is_base_of<TAG, decltype(test((rm_ref<T>*)nullptr))>::value };
	typedef is_iterator_of	type;
};

template<class T> using  is_input_iterator		= typename is_iterator_of<T,std::input_iterator_tag>::type;
template<class T> using  is_output_iterator		= typename is_iterator_of<T,std::output_iterator_tag>::type;
template<class T> using  is_forward_iterator		= typename is_iterator_of<T,std::forward_iterator_tag>::type;
template<class T> using  is_bidirectional_iterator	= typename is_iterator_of<T,std::bidirectional_iterator_tag>::type;
template<class T> using  is_random_access_iterator	= typename is_iterator_of<T,std::random_access_iterator_tag>::type;


	template<class IT, class T=decltype(*std::declval<IT>())>    
	constexpr bool  
is_const_iterator() {	// does not answer if this is CI, but if IT is const or not
	return  ! std::is_assignable <
		decltype( *std::declval<IT>() ),
		T
	>::value;
}


////////////////////////////////////////////////////////////////////////////////////////  IS_CALLABLE

// to check  ---  http://stackoverflow.com/questions/5100015/c-metafunction-to-determine-whether-a-type-is-callable

template<typename F, typename Signature> struct is_callable;

		template<typename F, typename R, typename... Args>
struct is_callable<F, R(Args...)> {
		template<typename>   static int8_t
	test(...);
		template<typename U> static
		eIF<
			std::is_same<decltype(std::declval<U>()(std::declval<Args>()...)), R>::value,
			int16_t
		>
	test(int);
	static const bool value = (sizeof(test<F>(0)) == sizeof(int16_t));
};
	// can not make is_foo<R<Args...>()  constexpr func - needs partial specialization

/////////////////////////////////////////////////////////////////// RANGE GENERICS: ENDZ, SIZE, CLEAR
									// not really a meta functions

/////  ENDZ - like std::end() but type const char[] is assumed to be C-string and its corresponding correct end (at '\0') is returned
template<typename Rg>	auto  endz(Rg&& rg)                  -> decltype(std::end(rg))    { return  std::end(rg); };
template<size_t N>	auto  endz( const char (&array)[N] ) -> decltype(std::end(array)) { return  std::find(std::begin(array), std::end(array),'\0'); };
template<size_t N>	auto  endz(       char (&array)[N] ) -> decltype(std::end(array)) { return  std::find(std::begin(array), std::end(array),'\0'); };

/////  SIZE

struct size_fo {
		typedef 	size_t 	result_type;

	template<class Rg>    eIF<has_size<Rg>::value, size_t>	size_impl (const Rg& rg)  const		   { return rg.size(); };
	//template<class Rg>		auto	size_impl (const Rg& rg) ->decltype(rg.size())  const      { return rg.size(); };
	template<class T, size_t N>	size_t	size_impl (const T (&C)[N]) const                          { return sto::endz(C) - std::begin(C); };
	template<class T, size_t N>	size_t	size_impl (const std::array<T,N>& A) const                 { return N; };
	template<class... Types>	size_t	size_impl (const typename std::tuple<Types...>& Tpl) const { return  std::tuple_size<std::tuple<Types...> >::value; };
	template<class U, class V>	size_t	size_impl (const std::pair<U,V>& P) const                  { return 2; };

	template<class X>		size_t	operator() (const X& x)  const                             { return size_impl(x); };
};

size_fo  size;


//template<class X>   		size_t			size 	(const X& x)  { return size_impl(x); };


/////  EMPTY
template<typename Rg>	eIF< has_empty<Rg>::value,bool>	empty(const Rg& rg)	{ return  rg.empty(); }
template<typename Rg>	eIF<!has_empty<Rg>::value,bool>	empty(const Rg& rg)	{ return  sto::size(rg)==0; }

/////  CLEAR
template<typename Rg>	eIF< has_clear<Rg>::value>	clear(Rg&& rg) 		{ rg.clear(); }
template<typename Rg>	eIF<!has_clear<Rg>::value>	clear(Rg&& rg) 		{}
                                              void	clear(char*rg) 		{ *rg = '\0'; }
/////  RESIZE
template<typename Rg>	eIF< has_resize<Rg>::value>	resize(Rg&& rg, size_t n) 		{ rg.resize(n); }
template<typename Rg>	eIF<!has_resize<Rg>::value>	resize(Rg&& rg, size_t n) 		{}
                                              void	resize(char*rg, size_t n) 		{ *(rg+n) = '\0'; }

/////  FRONT/BACK
//template<typename Rg>	eIF<!has_clear<Rg>::value, rg_elem_type<Rg>>		front(Rg&& rg) 		{ return *std::begin(rg); }

	// TODO: spceialization for c-str, arrays


/////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>  constexpr bool   is_collection()     {
	return      is_range<T>::value 
		||  is_stack<T>::value 
		||  is_queue<T>::value 
		||  is_range<T>::value
	;
 };

//template<typename T, typename Rg>   constexpr bool   is_elem_of()        { return  is_collection<Rg>()  &&  std::is_same<rm_ref<T>, rm_ref<rg_elem_type<Rg>>>::value; }
template<typename T, typename Rg>                 struct is_elem_of { enum { value = is_collection<Rg>()  &&  std::is_same<rm_qualifier<T>, rm_qualifier<rg_elem_type<Rg>>>::value }; };

//template<class Rg1, class Rg2>      constexpr bool  have_same_elem()      { return  is_range<Rg1>::value  &&  is_range<Rg2>::value  &&  std::is_convertible< rm_qualifier<rg_elem_type<Rg1>>,  rm_qualifier<rg_elem_type<Rg2>> >::value; }
  template<class Rg1, class Rg2>              struct  have_same_elem { enum { value = is_range<Rg1>::value  &&  is_range<Rg2>::value  &&  std::is_convertible< rm_qualifier<rg_elem_type<Rg1>>,  rm_qualifier<rg_elem_type<Rg2>> >::value }; };

					};
					#endif
