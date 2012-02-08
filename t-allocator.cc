#include "simple.h"
#include "allocator.h"
/*
#include <iostream>
#include <vector>
#include <map>
#include <utility>
*/


int main()  {

	__ "\nVECTOR";
	std::vector<int,trace_allocator<int>> v;
		v << 1 << 2 << 3;
		v--;
		v.clear();
		v.reserve(10);
	__ v;


	__ "\nMAP";
	std::map<int, float, std::less<int>, trace_allocator<std::pair<const int, float>> > m;
		m[1]=1.1;
		m[2]=2.2;
	__ flush;
	__ m, flush;

	__ "\n AT EXIT", flush;
}
