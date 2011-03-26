#ifndef  LVV_SIMPLE_H
#define  LVV_SIMPLE_H

//////////////////////////////////////////////////////////////////// C
//#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cctype>
#include <cmath>

///////////////////////////////////////////////////////////////////// C++ IO
#include <iostream>
#include <iomanip>
#include <sstream> 

///////////////////////////////////////////////////////////////////// C++ STL
#include <algorithm>
#include <deque>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <bitset>

// local
#include <lvv/lvv.h>
#include <lvv/meta.h>
#include <lvv/array.h>
	using lvv::array;
//	using std::to_binary;

using namespace std;

// FOREACH
//#include <boost/foreach.hpp>
//#define         foreach         BOOST_FOREACH  
//#define reverse_foreach		BOOST_REVERSE_FOREACH



///////////////////////////////////////////////////////////////////// LINE INPUT

	static std::istringstream		lin_sstream;
	static char __attribute__((unused))	lin_line[1000];	

	
	#define		nlin   		( \
						cin.getline(lin_line,sizeof(lin_line)-1),  \
						lin_sstream.clear(),  \
						lin_sstream.str(lin_line),  \
						lin_sstream \
	)

	#define		lin  lin_sstream

	#define		NL      		cin.ignore(1000,'\n');
	#define		nl      		cin.ignore(1000,'\n');


	#define		IS_SPACE                (cin.peek()==' '  || cin.peek()=='\t')
	#define		IS_EOL                  (cin.peek()=='\n' || cin.peek()=='\r')
	#define		IS_COMMA                (cin.peek()==',')
	#define		SKIP_SPACE              while ( IS_SPACE             )    cin.ignore(1);
	#define		SKIP_SPACE_N_COMMA      while ( IS_SPACE || IS_COMMA )    cin.ignore(1);

	/*  OBSOLETE:  use bitset
	 
	//////// integral to binary string 

			template<typename T> inline
	const string binstr (T v) {
		string binstr(sizeof(T)*8,'#') ;
		for (int i=0; i<sizeof(T)*8; i++) {
			binstr[sizeof(T)*8-1-i] = (v>>i) & 1 ? '1' : '0' ;
			//v = v / 2 ;
		}
		//return std::move(binstr) ;
		return binstr ;
	}

	template<typename T> struct list_t;
	*/

// OSI -- output stream iterator 
// 	shorthand for:	ostream_iterator<T>(cout, " ")
// 	used as:	copy(V.begin(), V.end(), osi<T>());
// 	also DTOR adds '\n'

	template<typename T=int>
struct	osi : ostream_iterator<T> {
	osi(): ostream_iterator<T>(cout, " ") { self_addr = (void*) this; }; 
	void* self_addr;	// to check if we are original instance of osi
	~osi() { if (self_addr == (void*) this)   cout << endl; };	
};

	
///////////////////////////////////////////////////////////////////// PRINT ANY CONTAINER

// print any C-array —  T[]
/*  does not work.  Impossible?
template<std::size_t N>
std::ostream&                                              
operator<<      (ostream& os, int A[N]) {              

        if (!A) return os;

	//os << *A;
	//for (size_t i=1;  i < sizeof(A)/sizeof(*A);  i++)  
        //        os <<  ", " << *(A+i);
        //os << "   size:" << sizeof(A)/sizeof(*A) <<"  ";
	os << *A;
	for (size_t i=1;  i < N;  i++)  
                os <<  ", " << *(A+i);

        os << "   size:" << N <<"  ";
        return os;
};
*/


// print any std::sequance-containter<printable>
template<typename E, template<typename E, typename L> class L > std::ostream&                                              
operator<<      (ostream& os, const L<E, std::allocator<E> >& LL) {              

        if (LL.empty()) return os;

        //for (size_t i=0; i<LL.size()-1; i++)
        //        os<<LL[i]<<", ";
	auto it=LL.begin();
	os  <<  *it++;
        for (; it !=LL.end();   it++)
                os <<  ", " << *it;
        os << "   size:" << LL.size() <<"  ";
        return os;
};

// SET -- print any std::set<printable>  with std comparator and allocator
template<typename K> inline std::ostream&                                              
operator<<      (ostream& os, const set<K, std::less<K>, std::allocator<K> >& C) {              

        if (C.empty()) return os;

	auto it=C.begin();
	os  <<  *it++;
        for (; it !=C.end();   it++)
                os <<  ", " << *it;
        os << "   size:" << C.size() << "  ";
        return os;
};



// MAP -- print any std::map<printable, printable>  with std comparator and allocator
template<typename K, typename V> inline std::ostream&                                              
operator<<      (ostream& os, const map<K, V, std::less<K>, std::allocator<std::pair<const K,V> > > & C) {              

        if (C.empty()) return os;

	auto it = C.begin();
	os  <<  *it++;
        for (; it !=C.end();   it++)
                os <<  ", " << *it;

        os << "   size:" << C.size() <<"  ";
        return os;
};
	

// PAIR -- print any std::pair<printable1, printable2>
template<typename T, typename U> inline std::ostream&  
operator<<      (ostream& os, const typename std::pair<T,U>& p) {               
	os << "⟨" << p.first << "," << p.second <<"⟩";
	return os;
};


	// Using C++0x Variadic Templates to Pretty-Print Types 
	// 	-- http://mlangc.wordpress.com/2010/04/18/using-c0x-variadic-templates-to-pretty-print-types/

// TUPLE -- print any std::tuple<printable ...>

			template< int I, typename... TT>
	struct	print_tuple_elem  {
		print_tuple_elem (ostream& os, const tuple<TT...>& tup)  {               
			const size_t  tsize = tuple_size<tuple<TT...>>::value;
			os <<  get<tsize-I>(tup) << " ";
			print_tuple_elem<I-1, TT...>(os, tup);
		};
	};

			template<typename... TT>
	struct	print_tuple_elem <0, TT...> {
		print_tuple_elem(ostream& os, const tuple<TT...>& tup)  {};
	};

		template<typename... TT> inline
		std::ostream&  
operator<<      (ostream& os, const tuple<TT...>& tup) {               
	const size_t  tsize = tuple_size<tuple<TT...>>::value;
	os << "<";     print_tuple_elem<tsize, TT...>(os, tup);    os << ">";
	return os;
};

/*  THIS WORKED BEFORE.  WHAT CHANGED? 
//		template<typename T0, typename REST> inline
//		std::ostream&  
//operator<<      (ostream& os, const std::tuple<T0, REST>&& tup) {               

		template<class Ch,class Tr, typename T0, typename REST>
		basic_ostream<Ch,Tr>&
operator<<	(basic_ostream<Ch,Tr>& os, tuple<T0, REST>&& tup)  {
	tuple<REST> sub_tup;
	T0 t0;
	os <<  get<0> << " ";
	tie(ignore, sub_tup) = tup;
	//os << sub_tup; 
	return os;
};

//			template<typename T0> inline
//			std::ostream&  
//	operator<<      (ostream& os, tuple<T0>&& tup) {               
			template<class Ch,class Tr, typename T0>
			basic_ostream<Ch,Tr>&
	operator<<	(basic_ostream<Ch,Tr>& os, tuple<T0>&& tup)  {
		os <<  get<0>(tup) << "⟩";
		return os;
	};
*/


#endif
