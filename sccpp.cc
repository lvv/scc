
#include <iostream>
#include <vector>
#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;
using namespace std;

// Displays nested results to std::cout with indenting
struct output_nested_results {
	int tabs_;
	regex_id_type id_;

	output_nested_results( int tabs, regex_id_type id) : tabs_( tabs ), id_(id) {}

	        template<typename BidiIterT>
		void
	operator()  (match_results<BidiIterT> const &what) const {
		// first, do some indenting
		typedef typename std::iterator_traits< BidiIterT >::value_type char_type;
		char_type space_ch = char_type(' ');
		std::fill_n( std::ostream_iterator<char_type>( std::cout ), tabs_ * 4, space_ch );

		// output the match
		std::cout << what[0];
		if (what.regex_id() == id_) std::cout << "   *** id ***";
		std::cout <<  '\n';

		// output any nested matches
		std::for_each (
			what.nested_results().begin(),
			what.nested_results().end(),
			output_nested_results( tabs_ + 1, id_)
		);
	}
};

int main() {

	vector<string> S;
		S.push_back("");
		S.push_back("aa;");
		S.push_back("bb");
		S.push_back("aa;bb;");
		S.push_back("aa;bb");
		S.push_back("aa;bb;cc");
		S.push_back("aa;{bb;}cc");

	smatch	what;
	string fmt("$1 << $2 >> ;");
	sregex	snippet, expr, last_expr, code, block, comment, statment;

		comment		= "//" >> *~_ln >> (_ln | eos);
		expr		= +_w;
		last_expr	= expr >> eos;
		statment	= expr >> ';';
		code		= +( statment | by_ref(block) );
		block		= '{' >> by_ref(code) >> '}';
		snippet		= (s1 = !code) >> (s2 = last_expr);

	for (unsigned i=0;  i<S.size();  i++) {
		cout	<< "-------------------------------------   "
			<< (regex_match(S[i], what, snippet) ? "match" : "NO-match") << "\n";
		output_nested_results(0,last_expr.regex_id())(what);
		cout	<< S[i] << "  -->  "
			<<  regex_replace(S[i], snippet, fmt) << '\n';

	}
}
