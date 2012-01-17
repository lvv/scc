#include <fstream>
#include <iostream>
	using std::cerr;
	using std::cout;
	using std::endl;

//#include <vector>
#include <string>
	using std::string;

#include <boost/xpressive/xpressive.hpp>
	using namespace boost::xpressive;

int main(int argc, char** argv)  {

	if (argc != 3)   { cerr << "\nusage:\n\tsccpp  source-scc-snippet-file  pre-processed-file\n\n";  exit(1); }

	std::ifstream	in  (argv[1]);
	std::ofstream	out (argv[2]);
	std::string	in_str;

	char c;   while(in.get(c))  in_str.push_back(c);

	#include "scc/sccpp.h"

	smatch	what;
	string fmt("$1\n\tstd::cout << ( $2 );  is_print_last=true;" );

	bool valid = regex_match(in_str, what, valid_snippet);
	if (!valid)   cerr << "sccpp warning: can not parse snippet, passing through ...\n";

	if (valid)	out <<  regex_replace(in_str, with_last, fmt);
	else		out <<  in_str;
}
