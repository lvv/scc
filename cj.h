
#ifndef  LVV_CODEJAM_H
#define  LVV_CODEJAM_H

#ifndef LVV_SIMPLE_H
#include <scc/simple.h>
#endif
///////////////////////////////////////////////////////////////////// SHORTCUTS

///// types
#define		vint		std::vector<int>
#define		vuint		std::vector<unsigned int>
#define		vlong		std::vector<long>
#define		vulong		std::vector<unsigned long>
#define		vfloat		std::vector<float>
#define		vdouble		std::vector<double>
#define		dint		std::deque<int>
#define		duint		std::deque<unsigned int>
#define		dfloat		std::deque<float>
#define		ddouble		std::deque<double>
#define         S      		std::string
#define         vS     		std::vector<std::string>
#define         vstr   		std::vector<str>
#define         dS     		std::deque<std::string>
#define         dstr   		std::deque<str>

///// utils 
#define 	GL(x)		std::getline(cin,x)
#define		MT		std::make_tuple
#define		NL     		cin.ignore(numeric_limits<std::streamsize>::max(),'\n');

//// container / iterators
#define 	ISI 		std::istream_iterator
#define 	OSI 		std::ostream_iterator
#define 	bb		begin() 	
#define 	ee		end() 	
#define 	rbb		rbegin() 	
#define 	ree		rend() 	
#define 	sz		size()


///////////////////////////////////////////////////////////////////// CLASSIC CODEJAM


#define		FOR(i,a,b)	for (__typeof__(b) i = (a); i < (b); i++)
#define		FORD(i,a,b)	for (__typeof__(b) i = (b)-1; i >= (a); i--)
#define		REP(N)    	for (__typeof__(N) i_ue923u=0;  i_ue923u<N;  i_ue923u++) 

#define		FORi(N)		FOR(i,0,N)
#define		FORj(N)		FOR(j,0,N)
#define		FORk(N)		FOR(k,0,N)
#define		FORt(N)		FOR(t,0,N)

#define		FORic(I,C)    	for (size_t I=0;  I<C.size();   I++) 
#define		FORc(IT,C)   	for (auto IT=C.begin();  IT != C.end();   IT++) 
#define		FORr(IT,B,E)   	for (auto IT=B;  IT != E;   IT++) 

#endif  // LVV_CODEJAM_H
