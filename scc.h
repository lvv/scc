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

#ifndef 	scc_NOAWK 
#include <scc/awk.h>
#endif



#endif // scc_SCC
