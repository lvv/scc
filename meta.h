#ifndef  LVV_META_H
#define  LVV_META_H

#include <type_traits>
#include <array>
#include <stack>
#include <queue>


#define DEF_HAS_MEMBER(name,member)						\
		template <typename T>						\
	struct name {								\
			template <						\
				typename U,					\
				typename M = typename U::member			\
			>							\
			static char						\
		test(U* u);							\
			template <typename U>					\
			static long						\
		test(...);							\
		enum { value = sizeof test<T>(0) == 1 };			\
	}; 

#define DEF_HAS_MEMBER_FUNC(name,func)						\
		template <typename T>						\
	struct name {								\
			template <						\
				typename U,					\
				typename F = decltype (((U*)0)->func)		\
			>							\
			static char						\
		test(U* u);							\
			template <typename U>					\
			static long						\
		test(...);							\
		enum { value = sizeof test<T>(0) == 1 };			\
	}; 

DEF_HAS_MEMBER(has_iterator,iterator)

DEF_HAS_MEMBER_FUNC(has_size,size())
DEF_HAS_MEMBER_FUNC(has_push_front,push_front(typename T::value_type()))


//////////////////////////////////////////////////////////////////////////////////////// IS_CONTAINER

	template <typename T>
struct is_container {

		template <
			typename U,
			typename S = decltype (((U*)0)->size()),
			typename I = typename U::const_iterator
		>
		static char
	test(U* u);

		template <typename U>
		static long
	test(...);

	enum { value = sizeof test<T>(0) == 1 };
};


template <typename Ct>		struct container_iterator	{ typedef	typename Ct::iterator	type; };
template <typename T, size_t N>	struct container_iterator<T[N]>	{ typedef	T*			type; };

template<typename T, size_t N>	struct  is_container <T[N]>		: std::true_type { };
template<typename T, size_t N>	struct  is_container <std::array<T,N>>	: std::true_type { };
//template<>			struct	is_container<const char*>	: std::true_type { };

//////////////////////////////////////////////////////////////////////////////////////  IS STRING
template<typename T>	struct  is_string		: std::false_type {};
template<>		struct  is_string <std::string>	: std::true_type  {};

//////////////////////////////////////////////////////////////////////////////////////  IS_STACK
	template <typename T>
struct is_stack {

		template <
			typename U,
			//typename PUSH	= decltype (((U*)0)->push(XXX)),
			typename POP	= decltype (((U*)0)->pop()),
			typename TOP	= decltype (((U*)0)->top())
		>
		static char
	test(U* u);

		template <typename U>
		static long
	test(...);

	enum { value = sizeof test<T>(0) == 1 };
};


//////////////////////////////////////////////////////////////////////////////////////  IS_QUEUE
	template <typename T>
struct is_queue {

		template <
			typename U,
			typename POP	= decltype (((U*)0)->pop()),
			//typename PUSH	= decltype (((U*)0)->push(XXX)),
			typename FRONT	= decltype (((U*)0)->front()),
			typename BACK	= decltype (((U*)0)->back())
		>
		static char
	test(U* u);

		template <typename U>
		static long
	test(...);

	enum { value = sizeof test<T>(0) == 1 };
};


//////////////////////////////////////////////////////////////////////////////////////  IS_ITERATOR
// iterator_reference<T>::type operator*(void) const;
// iterator_pointer<T>::type operator->(void) const;
// T & operator++(void);
// T operator++(int);

	template<typename T>
struct is_iterator {
					static char				test (...);	// anything else
	template<typename  U>		static typename U::iterator_category*	test (U*);	// Iterator
	template<typename  U>		static void *				test (U**);	// Pointer
	template<typename  U, size_t N>	static void *				test (U(*)[N]);	// C-array

	static const bool value = sizeof(test((T*)nullptr)) == sizeof(void *);
};

#endif
