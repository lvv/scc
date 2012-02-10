#include "simple.h"
#include "allocator.h"

//#define  ALLOC	trace_allocator
#define  ALLOC	nd_allocator

int main()  {
	

	__ "\nVECTOR";
	std::vector<int,ALLOC<int>> v;
		v << 1 << 2 << 3;
		v--;
		v.clear();
		v.reserve(10);
	__ v;


	__ "\nMAP";
	std::map<int, float, std::less<int>, ALLOC<std::pair<const int, float>> > m;
		m[1]=1.1;
		m[2]=2.2;
	__ flush;
	__ m, flush;

	__ "\n AT EXIT", flush;

	atexit( []{ delete[]  nd_allocator<char>::data; });
}
