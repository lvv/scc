#include <boost/xpressive/xpressive.hpp>

using namespace boost::xpressive;

int main() {

	#include "scc/sccpp.h"

	smatch	what;
	string fmt("$1 << $2 >> ;");


	//output_nested_results(0,last_expr.regex_id())(what);
	bool match = regex_match(C[i].s, what, valid_snippet);
	cout	<< (C[i].valid == match ? "OK     " : "ERROR  ") << (match ? "  valid" : "invalid") << "   ";
	cout	<< ">" << C[i].s << "<";

	if (match) cout << "   --->   " <<  ">" << regex_replace(C[i].s, with_last_snippet, fmt) << "<";
	cout << '\n';

}
