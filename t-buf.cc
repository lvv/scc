#include <errno.h>
#include <unistd.h>
#include <scc/simple.h>
#include <scc/scc.h>


struct buf_t {
			char		*bob, *eob;	// buffer dimentions
			char		*bod, *eod;	// unused data in buffer
	const static	size_t		buf_size=1000;
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


	bool		get_rec		(strr& sr)	{

		if (!good_file)   return false; 

		char *bor, *eor; // record
		bor = eor = bod;

		do {
			size_t	unchecked = eod - eor;
			
			if ( unchecked == 0 )  {
				if ( !(good_file = fill()) )  {
					if ( bor == eor ) 	return false;
					else 			goto return_strr;
				}
			}
								assert((unchecked = eod - eor,  unchecked > 0));
		} while ( *eor++ != '\n');


		return_strr:
			sr.B = bor;
			sr.E = eor-1;
			bod = eor;
			return true;
	}

};


int main() {
	buf_t buf(0);
	strr sr;
	int i=0;
	while(buf.get_rec(sr))
		__ i++ ^  sr;
	__ "total: ", i;

}

