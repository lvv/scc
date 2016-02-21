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


	#ifdef	scc_I_path
	cv::Mat		I		(cv::imread(scc_I_path));
	cv::Mat		BW		(cv::imread(scc_I_path, CV_LOAD_IMAGE_GRAYSCALE));
	#else
	cv::Mat		I		(cv::imread("/home/lvv/p/cv/lena.png"));
	cv::Mat		BW		(cv::imread("/home/lvv/p/cv/lena.png", CV_LOAD_IMAGE_GRAYSCALE));
	#endif
	if(I.empty()) {CV_Error(CV_StsBadArg, "error: Cann't read input image. Try to adjust image path")};

	#undef		I

	void		show(Mat I)	{ cv::imshow("",I);  waitKey(); };
	#define		asI(M)		cv::Mat  M(I.size(), I.type(), cv::Scalar::all(0));
	#define		Isz		I.size()
	#define		Itp		I.type()
#endif



#endif // scc_SCC
