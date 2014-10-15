#ifndef  SCC_LOOPS_MACRO_H
#define  SCC_LOOPS_MACRO_H

///////////////////////////////////////////////////////////////////// LOOPS


#define		FOR(i,i0,N)	for (long i = (i0), max_##i=(N);   i < max_##i;   i++)
#define		FOR1(i,N)	FOR(i,1,N+1)
#define		ROF(i,a,b)	for (long i = (b)-1; i >= long(a); i--)
#define		REP(N)		for (long i_REP_ue923u=0, N_REP_2uf23f=(N);   i_REP_ue923u< N_REP_2uf23f;   i_REP_ue923u++)

#define		iFOR(N)		FOR(i,0,N)
#define		jFOR(N)		FOR(j,0,N)
#define		lFOR(N)		FOR(l,0,N)
#define		kFOR(N)		FOR(k,0,N)
#define		tFOR(N)		FOR(t,0,N)
#define		nFOR(N)		FOR(m,0,N)
#define		mFOR(N)		FOR(m,0,N)

#define		iFOR1(N)	FOR(i,1,N+1)
#define		jFOR1(N)	FOR(j,1,N+1)
#define		kFOR1(N)	FOR(k,1,N+1)
#define		tFOR1(N)	FOR(t,1,N+1)
#define		nFOR1(N)	FOR(m,1,N+1)
#define		mFOR1(N)	FOR(m,1,N+1)

#define		ijFOR(I,J)	iFOR(I) jFOR(J)

#define		ITER(IT, C)	for (auto IT=begin(C);  IT != end(C);   IT++)
#define		RETI(IT, C)	for (auto IT=end(C)-1;  IT >= begin(C);   IT--)
#define		itITER(C)	ITER(it,C)
#define		itRETI(C)	RETI(it,C)
#define		pITER(C)	ITER(p,C)
#define		qITER(C)	ITER(q,C)
#define		pRETI(C)	RETI(p,C)

#define		IDX(I,C)	for (long I=0;  I<(long)(end(C)-begin(C));   I++)
#define		iIDX(C)		IDX(i,C)
#define		jIDX(C)		IDX(j,C)
#define		kIDX(C)		IDX(k,C)
#define		lIDX(C)		IDX(l,C)
#define		mIDX(C)		IDX(m,C)
#define		nIDX(C)		IDX(n,C)

#define		ALL(EL,C)	for (auto& EL:C)
#define		cALL(C)		for (auto c:C) if(c == '\0') break;  else
#define		xALL(C)		ALL (x,C)
#define		eALL(C)		ALL (e,C)

#ifdef  RO_H
#define		xRNG(a,b,c)	for (auto x: range(a,b,c))
#endif

#endif  		// SCC_LOOPS_MACRO_H
