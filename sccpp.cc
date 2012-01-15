
#include <iostream>
	using std::cout;
	using std::endl;
#include <string>
	using std::string;
#include <vector>
	using std::vector;
#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;
//using namespace std;

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

	sregex	ws, snippet, expr, last_expr, code, block, statement, op, word, paran, str, ch, esc,
		comment_cpp, comment_c, comment,
		valid_snippet, with_last_snippet;

		ws		= *_s;
		comment_cpp	= "//" >> *~_ln >> (_ln | eos);
		comment_c	= "/*" >> *_ >> "*/";
		comment		= comment_c | comment_cpp;
		op		= (set = '+', '-', '*', '-');
		word		= _b >> +_w >> _b;
		esc		= as_xpr('\\') >>
					(
						(set= '\"',  '0', 'a', 'b', 'f', 'n', 'r', 't', 'v')
						|         repeat<3,3>(_d)
					//	| (as_xpr('x') << _d << _d )		// xpressive: invalid regex
					//	| ('u' << repeat<4,4>(_d))
					//	| ('U' << repeat<8,8>(_d))
					);


		str		= as_xpr('\"') >> *(~(set='\"','\\') |  esc) >> '\"';
		ch		= as_xpr('\'') >> +(~as_xpr('\'') |  "\\\'") >> '\'';
		expr		= ws >> +((word|comment|op|str|ch|by_ref(paran)) >> ws);

		paran		= ('(' >> !by_ref(expr) >> ')') |
				  ('[' >> !by_ref(expr) >> ']');
		last_expr	= expr >> eos;
		statement	= expr >> ';' >> ws;
		code		= +( statement | by_ref(block) );
		block		= ws >> '{' >> by_ref(code) >> '}' >> ws;
		valid_snippet		= bos >> !(s1 = code) >> !(s2 = last_expr) >> eos;
		with_last_snippet	= bos >> !(s1 = code) >>  (s2 = last_expr) >> eos;

	for (unsigned i=0;  i<C.size();  i++) {
		//output_nested_results(0,last_expr.regex_id())(what);
		bool match = regex_match(C[i].s, what, valid_snippet);
		cout	<< (C[i].valid == match ? "OK     " : "ERROR  ") << (match ? "  valid" : "invalid") << "   ";
		cout	<< ">" << C[i].s << "<";

		if (match) cout << "   --->   " <<  ">" << regex_replace(C[i].s, with_last_snippet, fmt) << "<";
		cout << '\n';

	}
}
