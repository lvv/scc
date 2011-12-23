#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <utility>


// print std::pair
                template<typename T, typename U> std::ostream&
operator<<      (std::ostream& os, const typename std::pair<T,U>& p) {
        os << "(" << p.first << "," << p.second <<")";
        return os;
 };  

// output iterator for any type

	template<typename U, typename V, template<typename U, typename V> class CL>  void
outi_print(const CL<U,V>& v) { std::cout << v; };

namespace outi_space {  

	struct	outi_any_t {
			template<typename T>		
		outi_any_t (const T& v)				{ std::cout << v; };

			template<typename U, typename V, template<typename U, typename V> class CL>    
		outi_any_t (const CL<U,V>& v)	{ outi_print<U,V>(v); };
	};

	// NOP to make acceptable for ostream<<
	std::ostream&   operator<<      (std::ostream& os, const outi_any_t& s) { return os; };

	struct	outi_t  : std::ostream_iterator<outi_any_t> {
		outi_t(): std::ostream_iterator<outi_any_t>(std::cout, " ") {}; 
	};

};

using namespace std;

int main() {

	outi_space::outi_t outi;

	vector<int>	A{1,2,3}; 
	*outi = 1;			 cout << endl;
	copy(A.begin(), A.end(), outi);  cout << endl;
	
	string		S("ABC");
	*outi = 'A';			 cout << endl;		
	copy(S.begin(), S.end(), outi);  cout << endl;

	pair<int,int>	p(11,22);
	cout << p << endl;					// ok
	*outi = p; 						// (was) out of memory

	cout << endl;
}
