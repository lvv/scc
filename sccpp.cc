
#include <iostream>
#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;
using namespace std;

// Displays nested results to std::cout with indenting
struct output_nested_results {
	int tabs_;

	output_nested_results( int tabs = 0 ) : tabs_( tabs ) {}

	        template<typename BidiIterT>
		void
	operator()  (match_results<BidiIterT> const &what) const {
		// first, do some indenting
		typedef typename std::iterator_traits< BidiIterT >::value_type char_type;
		char_type space_ch = char_type(' ');
		std::fill_n( std::ostream_iterator<char_type>( std::cout ), tabs_ * 4, space_ch );

		// output the match
		std::cout << what[0] << '\n';

		// output any nested matches
		std::for_each (
			what.nested_results().begin(),
			what.nested_results().end(),
			output_nested_results( tabs_ + 1 )
		);
	}
};

int main() {
	string s( "9*(10+3)-1/2" );

	smatch	what;
	sregex	group, factor, term, expression;

	group       = '(' >> by_ref(expression) >> ')';
	factor      = +_d | group;
	term        = factor >> *(('*' >> factor) | ('/' >> factor));
	expression  = term >> *(('+' >> term) | ('-' >> term));


	sregex	snippet;

	if (regex_match(s, what, expression)) {
		output_nested_results()(what);
	}
}
