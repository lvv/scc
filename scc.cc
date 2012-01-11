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

	const char  *FILENAME;
	int FD=0;
	if (argc>2) {
		FILENAME=argv[2];
		FD = open(FILENAME,  O_RDONLY);
		if (FD<0) {
			cerr << "scc error:  can not open file \"" << FILENAME << "\"\n";
			exit(1);
		}
	}


	buf_t	buf(FD);	// stdio

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
		PAD_tab[*p] = 1;

	{  ///////////////////////////////////////////////////////////////////////////////////  snippet env

		std::function<bool()>  read_line;

		//if (RS.size()==1  &&  FS.size()==1)	read_line = [&]() { return  buf.get_rec(*RS.B, *FS.B, F); };
		//else					read_line = [&]() { return  buf.get_rec(RS, FS, F); };
		read_line = [&]() { return  buf.get_rec(RS, FS, F); };
		#define		WRL	while(read_line())


		#ifdef scc_HEADER
			read_line();
			itALL (F)
			for (size_t i = 0;  i<F.size();  i++)
				F.header[F[i]] = i;
		#endif


		#ifdef scc_IS_STREAM

			while (read_line()) {

				#include "/tmp/snippet.h"

				#ifdef scc_P
					#ifdef scc_PRINT_LAST
						cout << OFS;
					#endif

					print_line();
				#endif
			}

		#else
			#include "/tmp/snippet.h"
		#endif
	;}
}
