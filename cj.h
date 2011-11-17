
#ifndef  LVV_CODEJAM_H
#define  LVV_CODEJAM_H

#ifndef LVV_SIMPLE_H
#include <scc/simple.h>
#endif

#ifndef LVV_MATRIX_H
#include <scc/matrix.h>
#endif
///////////////////////////////////////////////////////////////////// SHORTCUTS

///// types
typedef		std::vector<int>          	vint;
typedef		std::vector<unsigned int> 	vuint;
typedef		std::vector<long>         	vlong;
typedef		std::vector<unsigned long>	vulong;
typedef		std::vector<char>         	vchar;
typedef		std::vector<float>        	vfloat;
typedef		std::vector<double>       	vdouble;
typedef		std::deque<int>           	dint;
typedef		std::deque<int>           	dlong;
typedef		std::deque<unsigned int>  	duint;
typedef		std::deque<float>         	dfloat;
typedef		std::deque<double>        	ddouble;
typedef		std::deque<char>          	dchar;

typedef		std::string			str;
typedef		std::vector<std::string>	vstr;
typedef		std::deque<std::string>		dstr;
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


#define		FOR(i,i0,N)	for (long i = (i0), N_FOR_d8s7d8s9=(N);   i < N_FOR_d8s7d8s9;   i++)
#define		FORD(i,a,b)	for (long i = (b)-1; i >= long(a); i--)
#define		REP(N)    	for (long i_REP_ue923u=0, N_REP_2uf23f=(N);   i_REP_ue923u< N_REP_2uf23f;   i_REP_ue923u++) 

#define		FORi(N)		FOR(i,0,N)
#define		FORj(N)		FOR(j,0,N)
#define		FORk(N)		FOR(k,0,N)
#define		FORt(N)		FOR(t,0,N)
#define		FORm(N)		FOR(m,0,N)

#define		FORic(I,C)    	for (long I=0;  I<(long)C.size();   I++) 
#define		FORitc(IT,C)   	for (auto IT=C.begin();  IT != C.end();   IT++) 
#define		FORr(IT,B,E)   	for (auto IT=B;  IT != E;   IT++) 

#endif  // LVV_CODEJAM_H
