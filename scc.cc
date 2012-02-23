#include <simple.h>
#include <scc.h>
#include <cj.h>
#include <matrix.h>

void  print_line() {
	if (!F.empty()) cout  << F[0];
	for(int i=1;   i < (int)F.size();  i++)
		cout  << OFS << F[i];
	cout << ORS;
 }

struct buf_t;
static buf_t	*buf;

static bool  read_line()  { return  buf->get_rec(RS, FS, F); };
static bool  next_file()  { return  buf->next_file(); };
#define		WRL	while( read_line()  ||  (next_file()  &&  read_line()) )


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
	char *p       __attribute__((unused)) = nullptr;

	char	**first_file_argv = argv+2;
	buf = new buf_t(first_file_argv, argv+argc);	// stdio


	////////  READ ENV

	// RS
	p = std::getenv("RS");
	if (p==nullptr)		RS = strr("\n");
	else			RS = strr(p);

	// ORS
	p = std::getenv("ORS");
	if (p==nullptr)		ORS = strr(RS);
	else			ORS = strr(p);

	// FS
	#ifndef  scc_ifs
		p = std::getenv("FS");
		if (p==nullptr)		FS = strr(" ");
		else			FS = strr(p);
	#endif

	// OFS
	#ifndef  scc_OFS
		p = std::getenv("OFS");
		if (p==nullptr)		OFS = strr(FS);
		else			OFS = strr(p);
	#endif

	// PAD
	#ifndef  scc_PAD
		p = std::getenv("PAD");
		if (p==nullptr)		PAD = strr(" \t");
		else			PAD = strr(p);
	#endif

	// PAD_tab
	for (const char *p = PAD.b;  p!=PAD.e;  p++)
		PAD_tab[size_t(*p)] = 1;

	{  ///////////////////////////////////////////////////////////////////////////////////  snippet env

		if (is_header) {
			read_line();
			for (size_t i = 0;  i<F.size();  i++)
				F.header[F[i]] = i;
		}

		if (is_stream)  {
			while (read_line()) {
				#include "/tmp/snippet.h"

				if (is_print_last)  {
					if (is_n) cout << ORS;
					if (is_p) cout << OFS;
				}

				if (is_p)  print_line();
			}
		} else {
			#include "/tmp/snippet.h"
			if (is_print_last)  cout << ORS;
		}
	;}

	delete buf;
}
