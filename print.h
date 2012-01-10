
#ifndef  LVV_PRINT_H
#define  LVV_PRINT_H
////////////////////////////////////////////////////////////////////  OUT, OUTLN
#include <type_traits>
#include <iterator>

#include <utility>	// pair
#include <tuple>

#include <iostream>
#include <iomanip>
	using	std::cout;
	using	std::cout;
	using	std::endl;
	using	std::ostream;


struct  out {
	bool  first_use;
	const char*	sep;
	const char*	paren;

	out ()					      : first_use(true), sep(0),   paren(0)     {init(); };
	out (const char* sep, const char* paren=0) : first_use(true), sep(sep), paren(paren) {init();};
	void init() { if (sep   && !*sep)	sep   = 0; }

	void send_sep() { if (sep && !first_use) cout << sep;  first_use = false; };

	template<typename T>	out&  operator<<  (T x)	{ send_sep();  cout <<        x;	return *this; };
	template<typename T>	out&  operator,   (T x)	{ send_sep();  cout << " " << x;	return *this; };
	template<typename T, size_t N>	out&  operator<<  (const T (&x)[N])	{ send_sep();  cout <<        x;	return *this; };
	template<typename T, size_t N>	out&  operator,   (const T (&x)[N])	{ send_sep();  cout <<        x;	return *this; };

	// endl, hex, ..
				out&  operator<< (std::ostream&  (*pf) (std::ostream& ) ) { cout << pf;  return *this; };
				out&  operator<< (std::ios&      (*pf) (std::ios&     ) ) { cout << pf;  return *this; };
				out&  operator<< (std::ios_base& (*pf) (std::ios_base&) ) { cout << pf;  return *this; };
				out&  operator,  (std::ostream&  (*pf) (std::ostream& ) ) { cout << pf;  return *this; };
				out&  operator,  (std::ios&      (*pf) (std::ios&     ) ) { cout << pf;  return *this; };
				out&  operator,  (std::ios_base& (*pf) (std::ios_base&) ) { cout << pf;  return *this; };

	operator bool   () {  return true; }
 };

struct  outln : out  {
	outln(const char* sep=0, const char* paren=0)	:out(sep, paren)	{};
	~outln()				{ cout << endl; }
 };


// NOP, but scc's print-last will send endl
std::ostream& operator<<      (ostream& os,  ostream&) {return os; };
std::ostream& operator<<      (ostream& os, const out&) {return os; };

// NOP, but scc' sprint-last will send endl
	template<typename IT, typename Unused = typename IT::iterator_category >  // for stl::containers::iterator
	std::ostream&
operator<<      (ostream& os, const IT&) { return os; }; 


#define		_    out()   <<
#define		__   outln() <<

/////////////////////////////////////////////////////////////////////  IS_CONTAINER

	template <typename T>
struct is_container {	// from http://stackoverflow.com/questions/4347921/sfinae-compiler-troubles
	template <typename U>
	static char test(
		U* u,
		typename U::const_iterator b = ((U*)0)->begin(),
		typename U::const_iterator e = ((U*)0)->end()
	);
	template <typename U> static long test(...);

	enum { value = sizeof test<T>(0) == 1 };
};

template<typename T, size_t N>	struct  is_container <T[N]> 	: std::true_type { };
template<typename T, size_t N>	struct  is_container <std::array<T,N>> 	: std::true_type { };
template<size_t N>		struct  is_container <char[N]>	: std::false_type { };
template<>			struct  is_container <std::basic_string<char>> : std::false_type { };



// print any std::containter<printable> or c-array
	template<typename Ct >
	typename std::enable_if <is_container<Ct>::value, std::ostream&>::type
operator<<      (ostream& os, const Ct& C) {
	cout << "{";
		auto I=std::begin(C);
		while (I != std::end(C)) {
			os  << *I;
			if (++I == std::end(C))  break;
			os << ", ";
		}
	cout << "}";
        return os;
};



// PAIR -- print any std::pair<printable1, printable2>

		template<typename T, typename U>
		std::ostream&
operator<<      (ostream& os, const std::pair<T,U>& p) {
	os << "⟨" << p.first << "," << p.second <<"⟩";
	return os;
};


// TUPLE -- print any std::tuple<printable ...>

			template< int RI, typename... TT>
	struct	print_tuple_elem  {
		print_tuple_elem (ostream& os, const std::tuple<TT...>& tup)  {
			const size_t  tsize = std::tuple_size<std::tuple<TT...>>::value;
			const size_t  i = tsize - RI;
			os <<  std::get<i>(tup);
			if  (i != tsize-1)   cout << ", ";
			print_tuple_elem<RI-1, TT...>(os, tup);
		};
	};

			template<typename... TT>
	struct	print_tuple_elem <0, TT...> {
		print_tuple_elem (ostream& os, const std::tuple<TT...>& tup)  {};
	};


		template<typename... TT>
		std::ostream&
operator<<      (ostream& os, const std::tuple<TT...>& tup) {
	const size_t  tsize = std::tuple_size<std::tuple<TT...>>::value;
	os << "⟨";     print_tuple_elem<tsize, TT...>(os, tup);    os << "⟩";
	return os;
};
	// Using C++0x Variadic Templates to Pretty-Print Types
	// 	-- http://mlangc.wordpress.com/2010/04/18/using-c0x-variadic-templates-to-pretty-print-types/

///////////////////////////////////////////////////////////////////////////////////////////////////////////  OUTI
// OUTI -- Output Iterator
// 	similar to ostream_iterator<T>(cout, " ")
// 	used as:	copy(V.begin(), V.end(), oi);

	template<typename U, typename V, template<typename U, typename V> class CL>  void
oi_print(const CL<U,V>& v) { std::cout << v; };

namespace oi_space {

		struct	oi_any_t {
				template<typename T>								// POD
			oi_any_t (const T& v)				{ std::cout << v; };

				template<typename U, typename V, template<typename U, typename V> class CL>	// std::pair
			oi_any_t (const CL<U,V>& v)	{ oi_print<U,V>(v); };
		};

		// NOP to make acceptable for ostream<<
		std::ostream&   operator<<      (std::ostream& os, const oi_any_t& s) { return os; };

	struct	oi_t  : std::ostream_iterator<oi_any_t> {
		oi_t(): std::ostream_iterator<oi_any_t>(std::cout, " ") {};
	};

};

static oi_space::oi_t oi;


#endif	// LVV_PRINT_H

