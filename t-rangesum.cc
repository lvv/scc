#include <scc/simple.h>

// http://infoarena.ro/blog/square-root-trick


	template<typename Vt>
struct rangef_t {

		typedef typename Vt::value_type  T;
		Vt S;
		Vt& V;
		size_t k;
		size_t N;


	explicit rangef_t(Vt& V_)  :  V(V_), N(V.size()) { 
		k = sqrt(N);
		S = Vt(N/k+1);
	}


	void update(size_t i, T x) {
		S[i/k] = S[i/k] - V[i] + x;
		V[i] = x;
	}

	T query(size_t lo, size_t hi) {

		T s = 0;
		size_t i = lo;

		while (i % k   &&   i < hi) {
			s += V[i];
			i ++;
		}
					//__  i, s;	
		while (i + k < hi) {
			s += S[i/k];
			i += k;
					//_ S[i/k], " ";
		}
					//__  "  ", i, s;	

		while (i < hi ) {
			s += V[i];
			i += 1;
		}
					//__  i, s;	
					//__ "query v: ", V,  vint(+V+lo, +V+hi), s; 
		return s;
	}

	private: rangef_t() {};
};

int main() {
	REP(100) {
		size_t  N=random()%10000; 
		vint V(N);
		rangef_t<vint>  RF(V);

		// mk index, run updates
		REP(100) { idx i = rand()%N;  RF.update(i,rand()%N); }

						//__  k, S, V;

		// test
		REP(100) {
			size_t lo = rand()%N;
			size_t hi = lo+rand()%(N-lo);
						//__ "lo,hi: ", lo, hi;

			int q = RF.query(lo, hi);
			int t = std::accumulate(+V+lo, +V+hi, 0);
						//__  q;
			assert(q ==  t);
						//__ " triv v: ", V,  vint(+V+lo, +V+hi),  t; 
		}
						//__  k, S, V;
	}	
}
