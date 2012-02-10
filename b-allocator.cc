#include "scc/cj.h"
#include "lvv/timer.h"
#include "scc/allocator.h"

//#define  ALLOC	trace_allocator
#define  ALLOC	nd_allocator

int main()  {


	const size_t	N	= 100000;
	char		*P[N]	= { nullptr };

	lvv::Timer tm;

	iALL(P)  P[i] = new char[i%27];
	__ "N=", N;
	__ "new:\t", tm.interval_ticks();
	pALL(P)   delete[] *p;
	__ "delete:\t", tm.interval_ticks();




	atexit( []{ delete[]  nd_allocator<char>::data; });
}
