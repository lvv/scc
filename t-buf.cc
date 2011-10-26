#include <errno.h>
#include <unistd.h>
#include <scc/simple.h>
#include <scc/scc.h>


struct buf_t {
			char		*bob, *eob;	// buffer dimentions
			char		*bod, *eod;	// unused data in buffer
	const static	size_t		buf_size=100;
			int		fd;		// file
			bool		good_file;	// !eof

	explicit	buf_t 		(int fd) : fd(fd), good_file(true) {
		bob = bod = eod =  new char[buf_size];  
		eob = bob + buf_size;
	}


	size_t		capacity	()	{ return buf_size; }
	size_t		size		()	{ return eod-bod; }


	bool		fill		()	{
		size_t buf_free_space = eob-eod;
		ssize_t got;
		if (buf_free_space > 0) { 
			retry:
			got = read (fd, eod,  buf_free_space);
			if (got == -1  &&  errno == EINTR)	goto  retry;
			if (got <=  0)				return  false;

			eod += got;
		}
		return  true;  				// TODO
	}


	bool		get_rec		(char RS, char FS, strr& sr, vector<strr>& F)	{

		if (!good_file)   return false; 

		char *bor, *eor; // record
		bor = eor = bod;
		F.clear()

		do {
			size_t	unchecked = eod - eor;
			if ( unchecked == 0 )  {
				size_t  buf_free_space = eob-eod;

				if (buf_free_space == 0) {  // relocate data to begining of buffer
					if (bor == bob ) {
						cerr << "warning: Line is too big for buffer. Splitting line.\n";
						goto return_strr; 
					} 

					ssize_t data_size = size();
					assert(eob-bob > 2*data_size); // FIXME: replace assert with realloc

					memcpy(bob, bod, data_size);
					bod = bor = bob;
					eod = eor = bob + data_size;
				}

				if ( !(good_file = fill()) )  {
					if ( bor == eor ) 	return false;
					else 			goto return_strr;
				}
			}
								//assert((unchecked = eod - eor,  unchecked >= 0));
		} while ( *eor++ != RS);


		return_strr:
			bod = eor;
			sr.B = bor;
			sr.E = eor-1;
			return true;
	}

};


int main() {
	buf_t buf(0);
	strr sr;

	size_t cnt=0;
	size_t sz = 0;
	size_t f_sz = 0;
	size_t f_cnt = 0;

	vector<strr> F;
	while(buf.get_rec('\n', ' ', sr, F)) {
		sz += sr.size();
		f_cnt += F.size();
		for(size_t i=0;  i<F.size();  i++)  f_sz +=  F[i].size();
		__ cnt++ ^  sr;
	}
	__ "total count: \t", cnt;
	__ "total size: \t", sz;
	__ "total field size: \t", f_sz;
	__ "total field count: \t", f_cnt;

}

