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
namespace outi_space {  

	struct	outi_any_t {
		template<typename T>			outi_any_t (const T& v)				{ std::cout << v; };
		//template<typename U, typename V>       	outi_any_t (const typename std::pair<U,V>& v)	{ std::cout << v; };
		template<typename U, typename V>       	outi_any_t (const typename std::pair<U,V>& v)	{ std::cout << "(" << v.first << "," << v.second << ")"; };
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
	*outi = 1;						// Ok
	copy(A.begin(), A.end(), outi);  cout << endl;		// Ok
	
	string		S("ABC");
	*outi = 'A';						// Ok 
	copy(S.begin(), S.end(), outi);  cout << endl;		// Ok

	pair<int,int>	p(11,22);
	cout << p << endl;					// ok
	*outi = p; 						// out of memory
}
