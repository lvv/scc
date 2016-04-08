#ifndef  scc_SCC_H
#define  scc_SCC_H

	#include "scc/simple.h"
	//#include "scc/allocator.h"


	// BUF
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <cerrno>

//  CONFIG

	const static bool  is_header =
		#ifdef scc_IS_HEADER
			true;
		#else
			false;
		#endif

	const static bool  is_stream =
		#ifdef scc_IS_STREAM
			true;
		#else
			false;
		#endif

	static bool  __attribute__((unused)) is_print_last = false;

	const static bool  is_p =
		#ifdef scc_P
			true;
		#else
			false;
		#endif

	const static bool  is_n =
		#ifdef scc_N
			true;
		#else
			false;
		#endif

#ifdef 	scc_AWK 
	#include <scc/awk.h>
#endif

#ifdef 	scc_OPENCV 
	#include <opencv2/opencv.hpp>
	using namespace cv;
	#include  "cv.h"
	void		show(Mat I)	{ cv::imshow("",I);  waitKey(); };
#endif



#endif // scc_SCC
