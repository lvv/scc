#include <simple.h>
#include <scc.h>
#include <cj.h>
#include <matrix.h>

void  print_line() {
	for(int i=1;   i < int(F.size())-1;  i++)
		cout  << F[i] << OFS;

	if (F.size() > 1)  cout << F.back();
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

	buf_t	buf(0);	// stdio

	////////  READ ENV

	// RS
	p = std::getenv("RS");
	if (p==nullptr)		RS = strr("\n");
	else			RS = strr(p);

	// ORS
	p = std::getenv("ORS");
	if (p==nullptr)		ORS = strr("\n");
	else			ORS = strr(p);

	// OFS
	#ifndef  scc_OFS
	p = std::getenv("OFS");
	if (p==nullptr)		OFS = strr(" ");
	else			OFS = strr(p);
	#endif

	// FS
	#ifndef  scc_ifs
	p = std::getenv("FS");
	if (p==nullptr)		FS = strr(" ");
	else			FS = strr(p);
	#endif

	{  /////////////////////////////////////////////////////////////////////////////////////////////

		std::function<bool()>  read_line;

		if (RS.size()==1  &&  FS.size()==1)	read_line = [&]() { return  buf.get_rec(*RS.B, *FS.B, F); };
		else					read_line = [&]() { return  buf.get_rec(RS, FS, F); };
		#define		WRL	while(read_line())

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
						// cout <<  endl;
						// cout <<  "RS=" << hex <<  int(*RS.B) <<  " " << RS.size() << endl;
						// cout <<  "FS=" << hex <<  int(*FS.B) <<  " " << FS.size() << endl;
						// cout <<  "ORS=" << hex <<  int(*ORS.B) <<  " " << ORS.size() << endl;
						// cout <<  "OFS=" << hex <<  int(*OFS.B) <<  " " << OFS.size() << endl;
	;}
}
