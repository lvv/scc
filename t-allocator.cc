#include "simple.h"
#include "allocator.h"

//#define  ALLOC	trace_allocator
#define  ALLOC	nd_allocator

int main()  {
	

	//nd_allocator<int> nd;
	__ "\nVECTOR";
	std::vector<int,ALLOC<int>> v;
		v << 1 << 2 << 3;
		v--;
		v.clear();
		v.reserve(10);
	__ v;


	__ "\nMAP";
	//nd_allocator<std::pair<const int, float>> ndm;
	std::map<int, float, std::less<int>, ALLOC<std::pair<const int, float>> > m;
		m[1]=1.1;
		m[2]=2.2;
	__ flush;
	__ m, flush;


	__ "\nSTRING";
	typedef 	std::basic_string<char, std::char_traits<char>, ALLOC<char> > nd_str;
	nd_str  s="abc", ss="xyz"; 
	std::string  S="ABC";
	__ flush;
	cout <<  S << endl;
	cout <<  s << endl;

	__ "\n AT EXIT", flush;

	//atexit( []{ delete[]  nd_allocator<char>::data; });
}
