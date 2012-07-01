
#ifndef  SCC_IO_H
#define  SCC_IO_H
////////////////////////////////////////////////////////////////////  OUT, OUTLN
//#include <x86_64-pc-linux-gnu/bits/stdc++.h>

#include <type_traits>
#include <iterator>

#include <utility>	// pair
#include <tuple>

#include <iostream>
#include <iomanip>
#include <fstream>
	using	std::cout;
	using	std::cout;
	using	std::endl;
	using	std::ostream;

#include "meta.h"

struct  io_t {
	std::streambuf  *sb;
	std::ofstream    ofs;
	std::ostream	*osp;

	io_t() :
		sb(std::cout.rdbuf()),
		osp(new std::ostream(sb))
		{}

	~io_t() {
		if ( ofs.is_open()) {
			ofs.close();
		}
		delete  osp;
	}

	bool out(const char* path) {
		if (ofs.is_open())  ofs.close();
		ofs.open (path);
		sb = ofs.rdbuf();
		delete osp;
		osp = new std::ostream(sb);
		return true;
	}

	// docs http://stackoverflow.com/questions/366955/obtain-a-stdostream-either-from-stdcout-or-stdofstreamfile
};


static io_t io;

struct  out {

	/*
	bool  first_use;
	const char*	sep;
	const char*	paren;

	out ()					      : first_use(true), sep(0),   paren(0)     {init(); };
	out (const char* sep, const char* paren=0) : first_use(true), sep(sep), paren(paren) {init();};
	void init() { if (sep   && !*sep)	sep   = 0; }

	void send_sep() { if (sep && !first_use) cout << sep;  first_use = false; };
	*/

	template<typename T>		out&  operator<<  (T x)				{ *io.osp <<        x;	return *this; };
	template<typename T>		out&  operator,   (T x)				{ *io.osp << " " << x;	return *this; };
	template<typename T, size_t N>	out&  operator<<  (const T (&x)[N])		{ *io.osp <<        x;	return *this; };
	template<typename T, size_t N>	out&  operator,   (const T (&x)[N])		{ *io.osp << " " << x;	return *this; };
	/* endl, hex, ..  */	out&  operator<< (std::ostream&  (*x) (std::ostream& ))	{ *io.osp << x;		return *this; };
				out&  operator<< (std::ios&      (*x) (std::ios&     ))	{ *io.osp << x;		return *this; };
				out&  operator<< (std::ios_base& (*x) (std::ios_base&))	{ *io.osp << x;		return *this; };
				out&  operator,  (std::ostream&  (*x) (std::ostream& ))	{ *io.osp << x;		return *this; };
				out&  operator,  (std::ios&      (*x) (std::ios&     ))	{ *io.osp << x;		return *this; };
				out&  operator,  (std::ios_base& (*x) (std::ios_base&))	{ *io.osp << x;		return *this; };

	operator bool   () {  return true; }
 };

struct  outln : out  {
	//outln(const char* sep=0, const char* paren=0)	:out(sep, paren)	{};
	~outln()				{ *io.osp << endl; }
 };


// NOP, but scc's print-last will send endl
std::ostream& operator<<      (ostream& os, const  ostream& )		{return os; };
std::ostream& operator<<      (ostream& os, const out&)			{return os; };

// NOP, but scc' print-last will send endl
	template<typename IT, typename Unused = typename IT::iterator_category >  // for stl::containers::iterator
	std::ostream&
operator<<      (ostream& os, const IT&) { return os; }; 


#define		_    out()   <<
#define		__   outln() <<


// SEQUANCE CONTAINTER or C-ARRAY
	template<typename Ct >
	eIF<is_container<Ct>()  &&  !is_ioable_t<Ct>::value, std::ostream&>
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


// STACK
	template<typename Ct >
	eIF <is_stack<Ct>(), std::ostream> &
operator<<      (ostream& os, Ct C) {

	Ct CC; 
	while(!C.empty()) { auto x = C.top();  C.pop();  CC.push(std::move(x)); }

	cout << "[";
		if    ( !CC.empty() )  { os         << CC.top();  CC.pop(); }
		while ( !CC.empty() )  { os << ", " << CC.top();  CC.pop(); }
	cout << "]";
        return os;
};

// QUEUE
	template<typename Ct >
	eIF <is_queue<Ct>(), std::ostream> &
operator<<      (ostream& os, Ct C) {
	cout << "[";
		if    ( !C.empty() )  { os         << C.front();  C.pop(); }
		while ( !C.empty() )  { os << ", " << C.front();  C.pop(); }
	cout << "]";
        return os;
};



// PAIR -- print any std::pair<printable1, printable2>

		template<typename T, typename U>
		std::ostream&
operator<<      (ostream& os, const std::pair<T,U>& p) {
	os << u8"⟨" << p.first << "," << p.second << u8"⟩";
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
	os << u8"⟨";     print_tuple_elem<tsize, TT...>(os, tup);    os << u8"⟩";
	return os;
};
	// Using C++0x Variadic Templates to Pretty-Print Types
	//	-- http://mlangc.wordpress.com/2010/04/18/using-c0x-variadic-templates-to-pretty-print-types/

///////////////////////////////////////////////////////////////////////////////////////////////////////////  OUTI
// OUTI -- Output Iterator
//	similar to ostream_iterator<T>(cout, " ")
//	used as:	copy(V.begin(), V.end(), oi);

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

			template<typename Ct >
			eIF<is_container<Ct>(),  void>
		operator=(const Ct& C)  {
			copy(C.begin(),  C.end(),  *this);
		}
	};

};

static oi_space::oi_t  oi;

		// NOP 
		// gcc error: void*
// std::ostream& operator<<      (ostream& os, oi_space::oi_t&)	{return os; };

///////////////////////////////////////////////////////////////////////////////  INPUT


struct in_t {
	in_t (): n(0) {};

		// set container size
		size_t n;
	in_t& operator() (long N) { n=N;  return *this; }


		template<typename T>		// primary
	operator T() {
		T x;
		input<T>(x); 
		n = 0;
		return x;
	};


	// PRIMARY (directly inputable)
		template<typename T>	
		eIF< is_ioable_t<T>::value, void >
	input(T& x)	{ std::cin >> x; }

	// SEQ-CONT
		template<typename Ct>
		eIF<is_container<Ct>()  &&  has_push_back<Ct>()  &&  !is_ioable_t<Ct>::value,  void>
	input(Ct& C)	{
		typename Ct::value_type t;
		if (n>0) C.resize(n);
		if (!C.empty())		for (typename Ct::value_type&x : C)  { std::cin >> t;   if(!std::cin || n-- <= 0)  break;  x=t;}
		else			{ C.clear();  while  (std::cin >> t, std::cin)  C.push_back(t);}
	}

	// SET
		template<typename Ct>
		eIF<is_container<Ct>()  &&  has_insert<Ct>()  &&  !has_mapped_type<Ct>(),  void>
	input(Ct& C)	{
		typename Ct::value_type t;
		C.clear(); 
		n = n ? n : -1;
		while  (std::cin >> t,  std::cin && n--)   C.insert(t);
	}

	// MAP
		template<typename Ct>
		eIF<is_container<Ct>()  &&  has_insert<Ct>()  &&  has_mapped_type<Ct>(),  void>
	input(Ct& C)	{
		typename Ct::key_type	  k;
		typename Ct::mapped_type  m;
		C.clear(); 
		n = n ? n : -1;
		while(std::cin >> k >> m  && n--)  C[k] = m;
	}


	// C-ARRAY
	// impossible to return C-array 

	// STD::ARRAY
	// STD::PAIR
	// STD::TUPLE

};

static in_t in;


// SEQ-CONTAINER

		template<typename Ct>
		eIF<is_container<Ct>()  &&  has_push_back<Ct>()  &&  !is_ioable_t<Ct>::value, std::istream& >
operator>>      (std::istream& is, Ct& C)    {
	int n = C.size() ? C.size() : -1;
	C.clear(); 
	typename Ct::value_type c;
	while(is>>c && n--)  C.push_back(c);
	return is;
};



		template<typename T, size_t N>
		eIF<!std::is_same<T,char>::value,  std::istream&>
operator>>      (std::istream& is, T(&A)[N])    {
	T t;
	for(size_t i=0;  i<N  &&  std::cin;  i++)  {
		if(!(is>>t)) break;
		A[i] = t;
	}
	return is;
};



// STD::ARRAY
		template<typename T, size_t N>
		std::istream&
operator>>      (std::istream& is, std::array<T,N>& A) {
	T t;
	for (size_t i=0;  i<N;  i++)  {
		is >> t; if (!is) break;
		A[i] = t;
	}
	return is;
};

// PAIR
		template<typename T, typename U>
		std::istream&
operator>>      (std::istream& is, std::pair<T,U>& p) {
	is >> p.first >>  p.second;
	return is;
};


// TUPLE

			template< int RI, typename... TT>
	struct	input_tuple_elem  {
		input_tuple_elem (std::istream& is, std::tuple<TT...>& tup)  {
			const size_t  tsize = std::tuple_size<std::tuple<TT...>>::value;
			const size_t  i = tsize - RI;
			is >>  std::get<i>(tup);
			input_tuple_elem<RI-1, TT...>(is, tup);
		};
	};

			template<typename... TT>
	struct	input_tuple_elem <0, TT...> {
		input_tuple_elem (std::istream& is, std::tuple<TT...>& tup)  {};
	};


		template<typename... TT>
		std::istream&
operator>>      (std::istream& is, std::tuple<TT...>& tup) {
	const size_t  tsize = std::tuple_size<std::tuple<TT...>>::value;
	input_tuple_elem<tsize, TT...>(is, tup);
	return is;
};


// SET
		template<typename Ct>
		eIF<is_container<Ct>()  &&  has_insert<Ct>() && !has_mapped_type<Ct>(), std::istream& >
operator>>      (std::istream& is, Ct& C)    {
	typename Ct::value_type c;
	while(is>>c)  C.insert(c);
	return is;
};


// MAP
		template<typename Ct>
		eIF<is_container<Ct>()  &&  has_insert<Ct>() && has_mapped_type<Ct>(), std::istream& >
operator>>      (std::istream& is, Ct& C)    {
	typename Ct::key_type	  k;
	typename Ct::mapped_type  m;
	while(is >> k >> m)  C[k] = m;
	return is;
};


#endif	// SCC_IO_H

