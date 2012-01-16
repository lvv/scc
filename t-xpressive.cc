// run as  g++ -I.. t.cc -o t && ./t a +a -+a aa + a+ ==a b= a==b  a+b a+b+c a++b  +a+b*c a=b+c
#include <iostream>
#include <boost/xpressive/xpressive.hpp>
	using namespace boost::xpressive;

int main(int argc, char** argv) {

	cregex	expr;
	cregex	var	=	_w;
	cregex	op	=	(set = '+', '-', '/', '*', '=') | "==";
	cregex	prefix	=	(set = '+', '-');
	cregex	group	= 	var | ('(' >> by_ref(expr) >> ')');
		expr	=	group
					| (+(prefix) >> group)
					| (group >> + (op >> group))
					;
	while (*++argv)   std::cout << *argv << (regex_match(*argv,  expr)? "\t   match\n" : "\t NO-match\n");
}
