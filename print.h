
#ifndef  LVV_PRINT_H
#define  LVV_PRINT_H
////////////////////////////////////////////////////////////////////  OUT, OUTLN
#include <type_traits>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <tuple>
#include <sstream>
	using	std::cout;
	using	std::cout;
	using	std::endl;
	using	std::string;
	using	std::ostream;
	using	std::flush;

struct  out {
	bool  first_use;
	const char*	sep;
	const char*	paren;

	out ()					      : first_use(true), sep(0),   paren(0)     {init(); };
	out (const char* sep, const char* paren=0) : first_use(true), sep(sep), paren(paren) {init();};
	void init() { if (sep   && !*sep)	sep   = 0; }

	void send_sep() { if (sep && !first_use) cout << sep;  first_use = false; };

	template<typename T>	out&  operator<<  (T x)	{ send_sep();  cout <<         x;	return *this; };
	template<typename T>	out&  operator,   (T x)	{ send_sep();  cout <<         x;	return *this; };
	//template<typename T>	out&  operator|   (T x)	{ send_sep();  cout << " "  << x;	return *this; };
	template<typename T>	out&  operator^   (T x)	{ send_sep();  cout << " " << x;	return *this; };

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

std::ostream&    operator<<      (ostream& os, out) {return os; };    // NOP


#define		_    out()   <<
#define		__   outln() <<
//#define		_    
//#define		__  


///////////////////////////////////////////////////////////////////// PRINT ANY CONTAINER

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
//template<typename T>		struct is_container : public ::std::integral_constant<bool, has_const_iterator<T>::value && has_begin_end<T>::beg_value && has_begin_end<T>::end_value> { };

template<typename T, size_t N>	struct  is_container <T[N]> 	: std::true_type { };
template<size_t N>		struct  is_container <char[N]>	: std::false_type { };
template<>			struct  is_container <std::basic_string<char>> : std::false_type { };




// print any std::containter<printable>
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
// 	tr1::tuple() used to be printable, but now with gcc460 - it is not.

	using	std::tuple;
	using	std::tuple_size;
	using	std::get;



			template< int RI, typename... TT>
	struct	print_tuple_elem  {
		print_tuple_elem (ostream& os, const tuple<TT...>& tup)  {
			const size_t  tsize = tuple_size<tuple<TT...>>::value;
			const size_t  i = tsize - RI;
			os <<  get<i>(tup);
			if  (i != tsize-1)   cout << ", ";
			print_tuple_elem<RI-1, TT...>(os, tup);
		};
	};

			template<typename... TT>
	struct	print_tuple_elem <0, TT...> {
		print_tuple_elem (ostream& os, const tuple<TT...>& tup)  {};
	};


		template<typename... TT>
		std::ostream&
operator<<      (ostream& os, const tuple<TT...>& tup) {
	const size_t  tsize = tuple_size<tuple<TT...>>::value;
	os << "⟨";     print_tuple_elem<tsize, TT...>(os, tup);    os << "⟩";
	return os;
};
	// Using C++0x Variadic Templates to Pretty-Print Types
	// 	-- http://mlangc.wordpress.com/2010/04/18/using-c0x-variadic-templates-to-pretty-print-types/

#endif	// LVV_PRINT_H

