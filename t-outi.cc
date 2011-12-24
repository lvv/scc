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
oi_print(const CL<U,V>& v) { std::cout << v; };

namespace oi_space {

		struct	oi_any_t {
				template<typename T>
			oi_any_t (const T& v)				{ std::cout << v; };

				template<typename U, typename V, template<typename U, typename V> class CL>
			oi_any_t (const CL<U,V>& v)	{ oi_print<U,V>(v); };
		};

		// NOP to make acceptable for ostream<<
		std::ostream&   operator<<      (std::ostream& os, const oi_any_t& s) { return os; };

	struct	oi_t  : std::ostream_iterator<oi_any_t> {
		oi_t(): std::ostream_iterator<oi_any_t>(std::cout, " ") {};
	};

};

using namespace std;

int main() {

	oi_space::oi_t oi;

	vector<int>	A{1,2,3};
	*oi = 1;			 cout << endl;
	copy(A.begin(), A.end(), oi);  cout << endl;

	string		S("ABC");
	*oi = 'A';			 cout << endl;
	copy(S.begin(), S.end(), oi);  cout << endl;

	pair<int,int>	p(11,22);
	cout << p << endl;					// ok
	*oi = p; 						// (was) out of memory

	cout << endl;
}
