#include <scc/simple.h>

// http://infoarena.ro/blog/square-root-trick

static size_t k;

	template <typename St,  typename Vt, typename T>
void update(St& S, Vt& V, size_t i, T x) {
	S[i/k] = S[i/k] - V[i] + x;
	V[i] = x;
}

	template <typename St,  typename Vt, typename T=typename Vt::value_type>
T query(St& S, Vt& V, size_t lo, size_t hi) {

	T s = 0;
	size_t i = lo;

	while (i % k   &&   i < hi) {
		s += V[i];
		i ++;
	}
				__  i, s;	
	while (i + k < hi) {
		s += S[i/k];
		i += k;
				_ S[i/k], " ";
	}
				__  "  ", i, s;	

	while (i < hi ) {
		s += V[i];
		i += 1;
	}
				__  i, s;	
				__ "query v: ", V,  vint(+V+lo, +V+hi), s; 
	return s;
}
	template<typename Vt>
int triv(Vt& V, size_t lo, size_t hi) {
	return std::accumulate(V.begin()+lo, V.begin()+hi, 0);
}

int main() {
	size_t  N=10; 
	vint V(N);

	// mk index, run updates
	k = sqrt(N);
	vint S(N/k+1);
	REP(100) { idx i = rand()%N;  update(S,V,i,rand()%N); }

					__  k, S, V;

	// test
	REP(100) {
		size_t lo = rand()%N;
		size_t hi = lo+rand()%(N-lo);
					__ "lo,hi: ", lo, hi;

		int q = query(S,V,lo, hi);
					//__  q;
		if (q != triv(V,lo,hi)) __ " ---------------------------------------------";
		assert(q ==          triv(V,lo,hi));
					__ " triv v: ", V,  vint(+V+lo, +V+hi),  triv(V,lo,hi); 
	}
					__  k, S, V;
}
