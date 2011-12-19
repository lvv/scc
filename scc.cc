#include <simple.h>
#include <scc.h>
#include <cj.h>
#include <matrix.h>

int main(int argc, char** argv) {
	long i __attribute__((unused)) = 0;
	long j __attribute__((unused)) = 0;
	long k __attribute__((unused)) = 0;
	long n __attribute__((unused)) = 0;
	long m __attribute__((unused)) = 0;
	long l __attribute__((unused)) = 0;

	double x __attribute__((unused)) = 0.0;
	double y __attribute__((unused)) = 0.0;
	double z __attribute__((unused)) = 0.0;
	double f __attribute__((unused)) = 0.0;

	std::string s __attribute__((unused));
	std::string w __attribute__((unused));

	buf_t	buf(0);	// stdio

	{

	#ifdef scc_IS_STREAM

		// while ( read_line()) {
		while ( buf.get_rec(strr(IRS), strr(IFS), F) ) {

			#include "/tmp/snippet.h"

			#ifdef scc_P
				#ifdef scc_PRINT_LAST
					cout << OFS;
				#endif

				for(int i=1;   i < int(F.size())-1;  i++)
					cout  << F[i] << OFS;

				if (F.size() > 1)  cout << F.back();
					cout << endl;
			#endif
		}

	#else
		#include "/tmp/snippet.h"
	#endif
		;
	}
}


