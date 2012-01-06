// test if regex.h can be used independantly

#include "scc/regex.h"
#include <iostream>
	using std::cout;
	using std::endl;

int main() {
	cout <<  ("ABC" == "A.."_R) << endl;
	cout <<  ("ABC" == ~std::string("A.."))  << endl;
}
