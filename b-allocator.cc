#include "scc/cj.h"
#include "lvv/timer.h"
#include "scc/allocator.h"

//#define  ALLOC	trace_allocator
#define  ALLOC	nd_allocator

int main()  {

	#ifdef NDEBUG
	const size_t	N	= 500000;
	#else
	const size_t	N	= 100;
	#endif
	char		*P[N]	= { nullptr };

	nd_allocator<char> Al;
	__ "*********************  N=", N, "      nd-cap=", Al.capacity;
	lvv::Timer tm;


	/////  ND_ALLOCATOR
	*Al.data = 'a';
	tm.reset();
	pALL(P)  { *p = Al.allocate((p-P)%27+1);  **p='a'; }
	__ "nd_allocator:    ", tm.interval_ticks(), flush;

	//pALL(P)   delete[] *p;
	//__ "delete:\t", tm.interval_ticks();


	/////  BUILDINT NEW  sequential
	tm.reset();
	pALL(P)  { *p = new char[(p-P)%27+1]; **p='a'; }
	__ "seq new:         ", tm.interval_ticks(), flush;
	pALL(P)   { delete[] *p;   *p = nullptr; }
	__ "seq delete:      ", tm.interval_ticks(), flush;

	/////  BUILDINT NEW  random

	//  GENERATE LOG
	// log of allocation/deallocation
	//   x=0:  uninitilized
	//   x>0:  index of subsequent delete (where pointer will be stored)
	//   x<0:  negative of index of predeceasing allocate (for assert) + 1

		int	L[2*N]{};
		int	l=0, ll;	// log index to allocate and de-allocate
	iFOR(N) {
		while(ll = l + rand()%(2*N-1-l) + 1,  L[ll]);		// find free log entry for de-allocate
		while(L[l]) ++l;					// find free log entry for allocation
									 assert(!L[l] && !L[ll]);  //__ i,l,ll;
		L[l++] = i;	// rec alloc
		L[ll]=-i-1;	// rec de-alloc
	};
									//__ L;



	/////  PLAY LOG

	tm.reset();
	lALL(L) {
		int i=L[l];
		if (i>=0) {						assert(!P[i]);
			P[i] =  new char[rand()%27 + 1];
			*P[i] = 'a';
		} else {
			int j= -i-1;					assert(*P[j]=='a');
			delete[]  P[j];
			P[j] = nullptr;
		}
	}

									pALL(P) assert(p==nullptr);

	__ "random new+del:  ", tm.interval_ticks(), flush;


	///// ND cleanup
	atexit( []{ delete[]  nd_allocator<char>::data; });
}
