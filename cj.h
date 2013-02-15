
#ifndef  LVV_CODEJAM_H
#define  LVV_CODEJAM_H


//#ifndef LVV_MATRIX_H
//#include "scc/matrix.h"
//#endif

///////////////////////////////////////////////////////////////////// UTILS



/*
	template<typename T>
T gcd(T a, T b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a == 0) return b;
    if (a > b) return gcd(b, a);
    return gcd(b % a, a);
}
*/
	// to check http://stackoverflow.com/questions/110344/algorithm-to-calculate-the-number-of-divisors-of-a-given-number
	//

constexpr long gcd(long x, long y) {
	    return (x % y) == 0 ? y :  gcd(y,x % y);
}

constexpr long factorial(long n) {
	    return n == 0  ?  1  :  n*factorial(n-1);
};


constexpr long permutation(long n, long k) {
	    return k == 1  ?  n  :  (n-(k-1))*permutation(n,k-1);
};

constexpr long combination(long n, long k) {
	    return permutation(n,k)/factorial(k);
};


#define countof(array) (sizeof (array) / sizeof(array[0]))


#define scc_RO	1
#include <ro/ro.h>		// http://github.com/lvv/ro
#include <scc/simple.h>		// http://github.com/lvv/scc

#endif  // LVV_CODEJAM_H
