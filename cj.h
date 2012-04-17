
#ifndef  LVV_CODEJAM_H
#define  LVV_CODEJAM_H

#ifndef LVV_SIMPLE_H
#include <scc/simple.h>
#endif

#ifndef LVV_MATRIX_H
#include <scc/matrix.h>
#endif

///////////////////////////////////////////////////////////////////// UTILS



	template<typename T>
T gcd(T a, T b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (a == 0) return b;
    if (a > b) return gcd(b, a);
    return gcd(b % a, a);
}

#define countof(array) (sizeof (array) / sizeof(array[0]))


#endif  // LVV_CODEJAM_H
