#include "scc/cj.h"
#include "lvv/timer.h"
#include "scc/allocator.h"

//#define  ALLOC	trace_allocator
#define  ALLOC	nd_allocator

int main()  {


	const size_t	N	= 20000;
	char		*P[N]	= { nullptr };

	nd_allocator<char> Al;
	__ "*********************  N=", N, "      nd-cap=", Al.capacity;
	lvv::Timer tm;


	/////  ND_ALLOCATOR
	*Al.data = 'a';
	tm.reset();
	pALL(P)  { *p = Al.allocate((p-P)%27);  **p='a'; }
	__ "nd_allocator:    ", tm.interval_ticks(), flush;

	//pALL(P)   delete[] *p;
	//__ "delete:\t", tm.interval_ticks();


	/////  NEW
	tm.reset();
	pALL(P)  { *p = new char[(p-P)%27]; **p='a'; }
	__ "new:             ", tm.interval_ticks(), flush;
	pALL(P)   delete[] *p;
	__ "delete:          ", tm.interval_ticks(), flush;

	atexit( []{ delete[]  nd_allocator<char>::data; });
}
