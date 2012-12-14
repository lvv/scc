// Record, AWK vars, buf_t

					#ifndef  SCC_AWK_H
					#define  SCC_AWK_H

					#include<scc/fld.h>

///////////////////////////////////////////////////////////////////////////////  R_t

		template<typename T>
	struct   R_t : std::vector<T> {

		T&	operator()(size_t I) {
			if (I==0)  return a;
			if (this->size()<I) this->resize(I);	// reference to non existant field
			return (*this)[I-1];
		};

		T&	operator()(const char* s) {
			auto it = header.find(s);
			if (it ==  header.end()) {
				cerr << "scc error:  header \"" <<  s << "\"  not found\n";
				return (*this)[0];
			} else {
				return (*this)[it->second];
			}
		};

		T  a;	// All_of record
		map<std::string,size_t>  header;

	};

	R_t<fld> F;

///////////////////////////////////////////////////////////////////////////////  AWK's vars 

		#define		$0	F.a
		#define		$1	F(1)
		#define		$2	F(2)
		#define		$3	F(3)
		#define		$4	F(4)
		#define		$5	F(5)
		#define		$6	F(6)
		#define		$7	F(7)
		#define		$8	F(8)
		#define		$9	F(9)
		#define		$10	F(10)
		#define		$11	F(11)
		#define		$12	F(12)
		#define		$13	F(13)
		#define		$14	F(14)
		#define		$15	F(15)
		#define		$16	F(16)
		#define		$17	F(17)
		#define		$18	F(18)
		#define		$19	F(19)
		#define		$20	F(20)

		#define		$NF	F(NF)
		#define		$	F

	long NF  = 0;
	long FNR = 0;
	long NR  = 0;

	//string       __attribute__((unused))	line;


	const char*  __attribute__((unused))	CSV="\"((?:(?:\\\\\")|[^\"])*)\"(\\s*,\\s*|$)";

	/*
	#ifdef  scc_IFS
	string       __attribute__((unused))	FS(scc_IFS);
	#else
		#ifdef  scc_ifs
		string       __attribute__((unused))	FS("([^" scc_ifs "]+)(" scc_ifs "|$)");	// field (data) is 1st group; FS is second group
		#else
		string       __attribute__((unused))	FS("(\\S+)(\\s+|$)");	// field (data) is 1st group; FS is second group
		#endif
	#endif
	*/

	strr	ORS;
	strr	RS;

	strr	OFS
		#ifdef  scc_OFS
			(scc_OFS);
		#else
			(" ");
		#endif

	strr	FS
		#ifdef  scc_ifs
			(scc_ifs);
		#else
			(" ");
		#endif

	strr	PAD
		#ifdef  scc_PAD
			(scc_PAD);
		#else
			(" \t");
		#endif

	char PAD_tab[256] = {0};

///////////////////////////////////////////////////////////////////////////////  Utils functions



///////////////////////////////////////////////////////////////////////////////  INPUT BUF

static const char	 * FILENAME = 0;

struct buf_t {
	const static	size_t		buf_size=1000000;
			bool		good_file;	// !eof
			char		bob[buf_size+1];// buffer dimentions
			const char	*eob;		// end of buffer
			const char	*bod, *eod;	// data in buffer
			const char	*path;
			int		fd;		// file
			char		**&argv;
			char		**argv_e;


	bool  next_file()   {
		if (fd==0 || argv==argv_e) {
			good_file = false;
			return  false;
		}

		FILENAME = *argv++;
		if (fd > 0)  close(fd);
		fd = open(FILENAME, O_RDONLY);
		if (fd < 0)  { cerr << "scc error:  can not open file \"" << FILENAME << "\"\n";   exit(1); }
		posix_fadvise (fd, 0, 0, POSIX_FADV_SEQUENTIAL);
		FNR = 0;
		good_file = true;
		return  true;
	}


	buf_t		(char**&argv, char**argv_e)
		: good_file(true), fd(-1),  argv(argv),  argv_e(argv_e)
	{
		if (argv <  argv_e)  {
			next_file();
		} else {
			FILENAME = "stdin";
			fd = 0;
		}
		bod = eod = bob;
		eob = bob+buf_size;
	}

	size_t		capacity	() const{ return buf_size; }
	ssize_t		size		() const{ return eod-bod; }
	bool		empty		() const{ return size() <= 0; }
	void		clear		()	{ eod  = bod = bob; }


	bool		fill		()	{
		size_t	buf_free_space = eob-eod;
		ssize_t	got;
		if  (buf_free_space > 0) {
			retry:
			got = read (fd, const_cast<char*>(eod),  buf_free_space);
			if (got == -1  &&  errno == EINTR)	goto  retry;
			if (got <=  0)				return  false;
			eod += got;
		}
		return  true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////  GET_REC
		template <typename sep_T>
	bool		get_rec		(sep_T RS, sep_T FS, R_t<fld>& F)	{

		try_next_file:
		if (!good_file  &&   is_stream && !next_file() )	return false;
		if (!good_file  &&  !is_stream )			return false;

		const char *p   (bod);
		F.a.b = p;				// record

		strr_allocator.clear();
		#define   FINISH_RECORD   { parse_rec(F);   NF = F.size();   bod = p;   FNR++; NR++; }

		while(1) {	//  read until EOR
			size_t	unused_data = eod - p;
			if (!unused_data)  {
				size_t  buf_free_space = eob-eod;

				if (!buf_free_space) {  // relocate data to begining of buffer
					if (F.a.b == bob ) {
						cerr << "warning: Line is too big for buffer. Splitting line.\n";
						FINISH_RECORD;
						return true;
					}

					ssize_t data_size = size();
					assert(eob-bob > 2*data_size); // FIXME: replace assert with realloc

					memcpy(const_cast<char*>(bob), const_cast<char*>(bod), data_size);
					bod = F.a.b = bob;
					eod = p = bob + data_size;
				}

				if ( !(good_file = fill()) )  {		// EOF
					if ( F.a.b == p  )    goto try_next_file;		// if EOF at BoR --> try next file
					F.a.e = p;
					FINISH_RECORD;
					return  true;
				}
			}

			p = F.a.e = search (p, eod, RS.b, RS.e);
			if (p != eod) {
				p += RS.size();
				FINISH_RECORD;
				return  true;
			}
		}

		FINISH_RECORD;
		return true;
	}

  private:

	void parse_rec (R_t<fld>& F) {
		F.clear();
		if (F.a.empty())  return;
		const char *sep, *eof;
		const char *bof = F.a.b;

		// TODO: gawk: In the special case that FS is a single space, fields are separated by runs of spaces
		//   and/or tabs and/or newlines.  (But see the section POSIX COMPATIBILITY, below).

		do {
			while( bof < F.a.e   &&   PAD_tab[size_t(*bof)]  )  bof++;		// skip padding
			sep = eof = search(bof, F.a.e, FS.b, FS.e);			//
			while( bof < (eof-1)  &&   PAD_tab[size_t(*(eof-1))]  )  eof--;		// eat  padding begore FS
			F.push_back(fld(bof,eof));
			bof = sep + FS.size();
		}  while (bof < F.a.e);
	}

 };

					#endif // SCC_AWK
