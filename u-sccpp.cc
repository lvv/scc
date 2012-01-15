
#include <iostream>
	using std::cout;
	using std::endl;
#include <string>
	using std::string;
#include <vector>
	using std::vector;
//using namespace std;

#include <boost/xpressive/xpressive.hpp>
using namespace boost::xpressive;

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

struct  test {
	test(bool valid,  string s) : valid(valid), s(s) {};
	bool	valid;
	string	s;
};


int main() {

	std::vector<test> C;
		C.push_back(test(1,	""					));
		C.push_back(test(1,	"aa;"					));
		C.push_back(test(1,	"bb"					));
		C.push_back(test(1,	"aa;bb;"				));
		C.push_back(test(1,	"aa;bb"					));
		C.push_back(test(1,	"aa;bb;cc"				));
		C.push_back(test(1,	"aa;{ bb+ +  ; } - cc  "		));
		C.push_back(test(1,	"aa;{bb+;} - cc  "			));
		C.push_back(test(0,	"(()"					));
		C.push_back(test(0,	"([)]"					));
		C.push_back(test(0,	"(;)"					));
		C.push_back(test(1,	"aa[[(1+2)[]]()]"			));

		C.push_back(test(0,	"\""					));
		C.push_back(test(0,	"\"\\\""				));
		C.push_back(test(1,	"\"\""					));
		C.push_back(test(1,	"\"\\\"\""				));
		C.push_back(test(0,	"''"					));
		C.push_back(test(1,	"';'"					));
		C.push_back(test(1,	"'\"'"					));
		C.push_back(test(1,	"\";})'{(\""				));

		C.push_back(test(1,	"last; /* ;)[\" */"			));
		C.push_back(test(1,	"last; // ;)[\" "			));
		C.push_back(test(1,	"ab; // ;)[\"\n last "			));

	smatch	what;
	string fmt("$1 << $2 >> ;");
	#include "scc/sccpp.h"


	for (unsigned i=0;  i<C.size();  i++) {
		//output_nested_results(0,last_expr.regex_id())(what);
		bool match = regex_match(C[i].s, what, valid_snippet);
		cout	<< (C[i].valid == match ? "OK     " : "ERROR  ") << (match ? "  valid" : "invalid") << "   ";
		cout	<< ">" << C[i].s << "<";

		if (match) cout << "   --->   " <<  ">" << regex_replace(C[i].s, with_last_snippet, fmt) << "<";
		cout << '\n';
	}
}
