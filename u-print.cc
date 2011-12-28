// test if u-print.h can be used independantly

#include"print.h"
#include<iostream>

using std::array;
using std::vector;
using std::pair;
using std::tuple;
using std::make_tuple;
using std::string;
using std::map;
using std::set;
using std::multiset;
using std::multimap;

int main() {
	#include "u-print.h"
	int A[3]{1,2,3};   cout << A << endl;  __ A;
}
