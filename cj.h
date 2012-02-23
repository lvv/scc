
#ifndef  LVV_CODEJAM_H
#define  LVV_CODEJAM_H

#ifndef LVV_SIMPLE_H
#include <scc/simple.h>
#endif

#ifndef LVV_MATRIX_H
#include <scc/matrix.h>
#endif

///////////////////////////////////////////////////////////////////// UTILS


// Greatest Common divisor
int gcd(long a, long b) {
	if (b==0)	return a;
	else		return gcd(b,a%b);
}

#define countof(array) (sizeof (array) / sizeof(array[0]))


#endif  // LVV_CODEJAM_H
