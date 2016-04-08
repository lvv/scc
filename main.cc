
// do not define ctype funcs as macros (gcc specific)
# define __NO_CTYPE 1

#include "scc/cj.h"

#ifdef scc_RO
	#include <ro/ro.h>
	using namespace ro;
#endif
	
#include <scc/simple.h>

#include <scc/scc.h>


//#include "scc/matrix.h"
#ifdef  scc_BENCHMARK
	#include "lvv/timer.h"
#endif

#ifdef scc_AWK
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
#endif


struct	tracking_buf_t : std::streambuf {

		char last_char;
		std::streambuf* buf;
		long count;

	tracking_buf_t (std::streambuf* buf) :  last_char(0), buf(buf), count(0) {
	    setp(0, 0); 	// no buffering, overflow on every char
	}

	bool terminated_line() const { return last_char=='\n' || count==0; }	// TOFIX? compare with ORS (=="\n")
	
	virtual int_type overflow(int_type c) {
		buf->sputc(c);
		last_char = c;
		++count;
		return c;
	}
};

#include "snippet.h"

int main(int argc, char** argv) {


	// tracking streambuf 
	std::cout.flush();
	std::streambuf* org_cout_buf = std::cout.rdbuf();
	tracking_buf_t tracking_buf(org_cout_buf);
	std::cout.rdbuf(&tracking_buf);

	// pre-declared vars
	int i __attribute__((unused)) = 0;
	int j __attribute__((unused)) = 0;
	int k __attribute__((unused)) = 0;
	int n __attribute__((unused)) = 0;
	int m __attribute__((unused)) = 0;
	int l __attribute__((unused)) = 0;
	int t __attribute__((unused)) = 0;

	double x __attribute__((unused)) = 0.0;
	double y __attribute__((unused)) = 0.0;
	double z __attribute__((unused)) = 0.0;

	std::string s	__attribute__((unused));
	std::string w	__attribute__((unused));
	char  c      	__attribute__((unused));
	char *p		__attribute__((unused)) = 0;
	char *q		__attribute__((unused)) = 0;

	// facet / locale
	// to figure out
       	std::locale::global(std::locale(""));
       	std::wcout.imbue(std::locale());
	auto& facet __attribute__((unused)) = std::use_facet<std::ctype<wchar_t>>(std::locale());


	#ifdef scc_AWK
		char	**first_file_argv = argv+1;

		buf = new buf_t(first_file_argv, argv+argc);	// stdio
		// cin.sync_with_stdio(false);

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

	#else // ^NOAWK 
		#define ORS "\n"
	#endif // ^NOAWK 
 
	// BENCHMARK
	#ifdef  scc_BENCHMARK
		lvv::timer_t timer  __attribute__((unused)) (true);
	#endif

	#ifdef 	scc_OPENCV 

		cv::Mat	F;  
		cv::Mat	Fbw; 
		cv::Mat	M,O;

		#ifdef	scc_I_path
		cv::Mat		I		(cv::imread(scc_I_path));
		cv::Mat		Ibw		(cv::imread(scc_I_path, CV_LOAD_IMAGE_GRAYSCALE));
		#else
		cv::Mat		I		(cv::imread("/home/lvv/p/cv/lena.png"));
		cv::Mat		Ibw		(cv::imread("/home/lvv/p/cv/lena.png", CV_LOAD_IMAGE_GRAYSCALE));
		#endif

		if (I.empty())
			CV_Error(CV_StsBadArg, "error: Cann't read input image. Try to adjust image path");

		I  .convertTo (F,   CV_32FC3, 1.f/255);
		Ibw.convertTo (Fbw, CV_32FC1, 1.f/255);


		#define		asI(M)		cv::Mat  M(I.size(), I.type(), cv::Scalar::all(0));
		#define		Isz		I.size()
		#define		Fsz		I.size()
	#endif

	{  ///////////////////////////////////////////////////////////////////////////////////  snippet env

		#ifdef scc_IS_STREAM
		#ifdef scc_AWK
		if (is_header) {
			read_line();
			for (size_t i = 0;  i<F.size();  i++)
				F.header[F[i]] = i;
		}

		if (is_stream)  {
			while (read_line()) {
				#include "snippet.cc"

				if (is_print_last)  {
					if (is_n) cout << ORS;
					if (is_p) cout << OFS;
				}

				if (is_p)  print_line();
			}
		}
		else
		#endif
		#else
		{
			#include "snippet.cc"
			//if (is_print_last)  cout << ORS;
		}
		#endif
		; // this semicolon terminates possible empty else
	}

	// last output should have terminated '\n'
	if ( ! tracking_buf.terminated_line()) 	 cout << ORS;
	std::cout.rdbuf(org_cout_buf);

	#ifdef scc_AWK
	delete buf;
	#endif
}
