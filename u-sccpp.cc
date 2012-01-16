
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
// even better display:  http://stackoverflow.com/questions/7657130/how-to-get-the-ast-of-a-regular-expression-string
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
	#define LVV_STR(x) __LVV_STR__(x)
	#define __LVV_STR__(x) #x
	#define		Q(r)		r,  LVV_STR(r)

struct  test {
	test(bool valid, sregex &r, string rname,  string s) : valid(valid), s(s), r(r), rname(rname) {};
	bool	valid;
	string	s;
	sregex	r;
	string	rname;
};


int main() {

	#include "scc/sccpp.h"

	std::vector<test> C;
		C.push_back(test(1, Q(valid_snippet),	""					));
		C.push_back(test(1, Q(valid_snippet),	" "					));
		C.push_back(test(1, Q(valid_snippet),	"aa;"					));
		C.push_back(test(1, Q(valid_snippet),	"bb"					));
		C.push_back(test(1, Q(valid_snippet),	"aa;bb;"				));
		C.push_back(test(1, Q(valid_snippet),	"aa;bb"					));
		C.push_back(test(1, Q(valid_snippet),	"aa;bb;cc"				));
		C.push_back(test(1, Q(valid_snippet),	"    aa;{++bb;} - LAST"			));
		C.push_back(test(1, Q(valid_snippet),	"int aa;{++bb;} - LAST"			));
		C.push_back(test(1, Q(valid_snippet),	"int/aa;{++bb;} - LAST"			));
		C.push_back(test(1, Q(valid_snippet),	" aa; bb; LAST"			));
		C.push_back(test(1, Q(valid_snippet),	"aa; bb; LAST"			));
		C.push_back(test(0, Q(valid_snippet),	"(()"					));
		C.push_back(test(0, Q(valid_snippet),	"([)]"					));
		C.push_back(test(0, Q(valid_snippet),	"(;)"					));
		C.push_back(test(1, Q(expr),	"1"					));
		C.push_back(test(0, Q(expr),	"1-"					));
		C.push_back(test(1, Q(expr),	"-a"					));
		C.push_back(test(1, Q(expr),	"-*$"					));
		C.push_back(test(0, Q(expr),	"==a"					));
		C.push_back(test(0, Q(expr),	"=="					));
		C.push_back(test(0, Q(expr),	"="					));
		C.push_back(test(1, Q(expr),	"b==a"					));
		C.push_back(test(0, Q(expr),	"b=="					));
		C.push_back(test(0, Q(expr),	"=a"					));
		C.push_back(test(0, Q(expr),	"=/a"					));
		C.push_back(test(0, Q(expr),	"=a/"					));

		C.push_back(test(0, Q(expr),	"/*0x1"					));
		C.push_back(test(0, Q(expr),		"/*aa"					));
		C.push_back(test(0, Q(expr),		" /*aa"					));
		C.push_back(test(0, Q(expr),		"/aa"					));
		C.push_back(test(1, Q(comment),		"//"					));
		C.push_back(test(1, Q(comment),		"/**/"					));
		C.push_back(test(0, Q(comment),		"/*/"					));
		C.push_back(test(0, Q(comment),		"/*"					));
		C.push_back(test(0, Q(expr),		"/"					));
		C.push_back(test(0, Q(expr),		" / "					));
		C.push_back(test(0, Q(comment),		"/*aa"					));
		C.push_back(test(0, Q(expr),		"/*aa"					));
		C.push_back(test(0, Q(expr),		"/*a"					));
		C.push_back(test(0, Q(expr),		"/aa"					));
		C.push_back(test(0, Q(expr),		"/+aa"					));
		C.push_back(test(0, Q(expr),		"(/aa)"					));
		C.push_back(test(0, Q(expr),		"(/+aa)"				));
		C.push_back(test(0, Q(expr),		"%aa"					));
		C.push_back(test(0, Q(expr),		"/*AA"					));
		C.push_back(test(0, Q(expr),		"/*AAAA"				));
		C.push_back(test(1, Q(expr),		"bbb/*AAAA"				));
		C.push_back(test(0, Q(expr),		"bbb/*"				));
		C.push_back(test(0, Q(expr),		"/ *aa"				));
		C.push_back(test(0, Q(expr),		" / *aa"				));
		C.push_back(test(1, Q(expr),		"bbb%/*AAAA"				));
		C.push_back(test(0, Q(expr),		"%*aa"					));
		C.push_back(test(1, Q(expr),		"*aa"					));
		C.push_back(test(0, Q(expr),		"/*aa"					));
		C.push_back(test(0, Q(expr),		"/1"					));
		C.push_back(test(0, Q(expr),		"+/1"					));
		C.push_back(test(0, Q(expr),		"/*aa"					));
		C.push_back(test(0, Q(expr),		"/*aa"					));
		C.push_back(test(0, Q(expr),		"/aa"					));
		C.push_back(test(0, Q(expr),		"aa*/"					));

		C.push_back(test(1, Q(valid_snippet),	"/*0x1*/"				));

		C.push_back(test(1, Q(valid_snippet),	"//"					));
		C.push_back(test(1, Q(valid_snippet),	"aa[[(1+2)[]]()]"			));
		C.push_back(test(1, Q(expr),		"aa[[(1+2)[]]()]"			));
		C.push_back(test(1, Q(paran),		"[[(1+2)[]]()]"				));
		C.push_back(test(0, Q(str),		"\""					));
		C.push_back(test(0, Q(str),		"\"\\\""				));
		C.push_back(test(1, Q(str),		"\"\""					));
		C.push_back(test(1, Q(valid_snippet),	"\"\\\"\""				));
		C.push_back(test(0, Q(valid_snippet),	"''"					));
		C.push_back(test(1, Q(valid_snippet),	"';'"					));
		C.push_back(test(1, Q(valid_snippet),	"'\"'"					));
		C.push_back(test(1, Q(valid_snippet),	"\";})'{(\""				));
		C.push_back(test(1, Q(valid_snippet),	"last; /* ;)[\" */"			));
		C.push_back(test(1, Q(valid_snippet),	"last; /* ;)[\" */ "			));
		C.push_back(test(1, Q(valid_snippet),	"last; /*  */ "				));
		C.push_back(test(1, Q(valid_snippet),	"last; // ;)[\" "			));
		C.push_back(test(1, Q(valid_snippet),	"ab; // ;)[\"\n last "			));
		C.push_back(test(1, Q(valid_snippet),	"ab; ({last1;last2;}) "			));
		C.push_back(test(1, Q(valid_snippet),	"int A[2] = {1,2}; A"			));
		C.push_back(test(1, Q(valid_snippet),	"$"					));
		C.push_back(test(1, Q(valid_snippet),	"$1=9;"					));
		C.push_back(test(1, Q(valid_snippet),	"WRL n+=$3;  n"				));
		C.push_back(test(1, Q(valid_snippet),	"vint A{1,2,3}; copy(A.bb, A.ee, oi); str S(\"ABC\"); copy(S.bb, S.ee, oi); cout<<endl;"));
		C.push_back(test(1, Q(valid_snippet),	"vint A{1,2,3};"			));
		C.push_back(test(1, Q(valid_snippet),	"copy(A.bb, A.ee, oi);"			));
		C.push_back(test(1, Q(valid_snippet),	"copy(A.bb, A.ee, oi)z;"		));
		C.push_back(test(1, Q(valid_snippet),	"copy(A.bb, A.ee, oi)"			));
		C.push_back(test(1, Q(valid_snippet),	"copy()"				));
		C.push_back(test(1, Q(valid_snippet),	"a.b"					));
		C.push_back(test(1, Q(valid_snippet),	"{}"					));
		C.push_back(test(1, Q(valid_snippet),	"// not-last"				));
		C.push_back(test(1, Q(valid_snippet),	"// not-last\n"				));
		C.push_back(test(1, Q(valid_snippet),	"last; // not-last"			));
		C.push_back(test(1, Q(valid_snippet),	"last; // not-last\n"			));
		C.push_back(test(1, Q(valid_snippet),	"first; // not-last\n last"		));
		C.push_back(test(1, Q(valid_snippet),	"first; // not-last\n non-last /*comm*/"));
		C.push_back(test(1, Q(valid_snippet),	"/*com*/"));

	smatch	what;

	//string fmt("$1 <<== $2 ==>> ");
	string fmt("\n\t&: $&\n\t1: $1 \n\t2: $2");

	for (unsigned i=0;  i<C.size();  i++) {
		//output_nested_results(0,last_expr.regex_id())(what);
		bool match = regex_match(C[i].s, what, C[i].r);
		cout	<< '\n' << (C[i].valid == match ? "OK    " : "ERROR ") << (match ? "  valid" : "invalid") << "   ";
		cout	<< "\n\tN: " << C[i].rname ;
		cout	<< "\n\tS: " << C[i].s ;

		if (match) cout << "\n\tR: " <<  regex_replace(C[i].s, with_last, fmt) << '\n';
	}
}
