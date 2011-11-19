#ifndef  LVV_SCC_H
#define  LVV_SCC_H

	#include <cassert>

	// BUF
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <cerrno>


//////////////////////////////////////////////////////////////////////////////////////////  STRR
	

struct strr {          
	const char *B, *E;

	// CTOR
	strr()			/*: B(0), E(0)*/  				{};
	strr(const char*   s)	: B(s)           			{  E = B + strlen(s); };
	strr(const string& s)	: B(s.data()),  E(s.data()+s.size())	{};
	strr(const char* B, const char* E):  B(B),  E(E)		{};
	//strr& operator=(const strr& sr) : B(sr.B), E(sr

	// MEMBERS
	size_t	size()		const { return E-B; };
	size_t	empty()		const { return E-B == 0; };
	bool	operator==(strr sr)	const { return equal(B, E, sr.B); };

	// CONVERSION
	operator const string			(void) const { return string(B,E); }

	operator ssize_t		(void) const {
		ssize_t 	sign	= 1;
		const char	*p	= B;   
		ssize_t		base	= 10;

		for (;  p<E-1;  p++) { 			// read prefix
			switch(*p) {
				case ' ':;   case '\t': continue;
				case '-':	sign = -1;  p++;  goto end_prefix;
				case '+':	p++;  goto end_prefix; 
				default: 	goto end_prefix;
			}
		}

		end_prefix:;

		ssize_t  n=0;				// read number
		for (;  p<E && isdigit(*p);  p++)  {
			n = n*base + (*p-'0'); 
		}
		return sign*n;
	}
 };

		inline std::ostream&  
 operator<<      (ostream& os, const strr f) {               
	const char *p = f.B;
	while (p!=f.E)   os << *p++;
	return os;
 };

/*
struct field: string {      ////////////////////////////////////////////////////////////////  OLD FIELD

	// CTOR
	field(const char*   s)	: string(s) {};
	field(const string& s)	: string(s) {};
	field(int           i)	: string()  {*this = (long)i;};
	field(long          i)	: string()  {*this = (long)i;};
	field(double        i)	: string()  {*this = (double)i;};
	field()			: string()  {};

	// op= assign
	field& operator  = (int I) { ostringstream OS;   OS <<              I;   this->string::assign(OS.str());  return *this; }
	field& operator += (int I) { ostringstream OS;   OS << int(*this) + I;   this->string::assign(OS.str());  return *this; }
	field& operator -= (int I) { ostringstream OS;   OS << int(*this) - I;   this->string::assign(OS.str());  return *this; }
	field& operator *= (int I) { ostringstream OS;   OS << int(*this) * I;   this->string::assign(OS.str());  return *this; }
	field& operator /= (int I) { ostringstream OS;   OS << int(*this) / I;   this->string::assign(OS.str());  return *this; }
	field& operator %= (int I) { ostringstream OS;   OS << int(*this) / I;   this->string::assign(OS.str());  return *this; }

	field& operator  = (long I) { ostringstream OS;   OS <<               I;   this->string::assign(OS.str());  return *this; }
	field& operator += (long I) { ostringstream OS;   OS << long(*this) + I;   this->string::assign(OS.str());  return *this; }
	field& operator -= (long I) { ostringstream OS;   OS << long(*this) - I;   this->string::assign(OS.str());  return *this; }
	field& operator *= (long I) { ostringstream OS;   OS << long(*this) * I;   this->string::assign(OS.str());  return *this; }
	field& operator /= (long I) { ostringstream OS;   OS << long(*this) / I;   this->string::assign(OS.str());  return *this; }
	field& operator %= (long I) { ostringstream OS;   OS << long(*this) / I;   this->string::assign(OS.str());  return *this; }

	field& operator  = (double I) { ostringstream OS;   OS <<                 I;   this->string::assign(OS.str());  return *this; }
	field& operator += (double I) { ostringstream OS;   OS << double(*this) + I;   this->string::assign(OS.str());  return *this; }
	field& operator -= (double I) { ostringstream OS;   OS << double(*this) - I;   this->string::assign(OS.str());  return *this; }
	field& operator *= (double I) { ostringstream OS;   OS << double(*this) * I;   this->string::assign(OS.str());  return *this; }
	field& operator /= (double I) { ostringstream OS;   OS << double(*this) / I;   this->string::assign(OS.str());  return *this; }
	field& operator %= (double I) { ostringstream OS;   OS << double(*this) / I;   this->string::assign(OS.str());  return *this; }

		template<class T>
	field& operator << (T t) { ostringstream OS;   OS << *this << t;  *this =  OS.str(); return *this; }

	operator const string&	(void) const 	{ return  *(string*)this; }	// converter to std::string&
	operator string&	(void) 		{ return  *(string*)this; }	// converter to std::string&
	operator bool		(void) const 	{ return   this->size() != 0; }	// converter to bool

	// converter to numerics
		
			operator double		(void) { istringstream IS;  double I;  IS.str(*this);  IS >> I;  return I; }
	#if 	 (  __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6 ) ) ) 
	explicit	operator int		(void) { istringstream IS;  int             I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator long		(void) { istringstream IS;  long            I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator unsigned int	(void) { istringstream IS;  unsigned int    I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator unsigned long	(void) { istringstream IS;  unsigned long   I;  IS.str(*this);  IS >> I;  return I; }
	explicit	operator float		(void) { istringstream IS;  double          I;  IS.str(*this);  IS >> I;  return I; }
	//explicit	operator void*		(void) { return  this->empty())  ? 0 : 1 ;   }
	#endif

	////
	field  operator +  (const char* s) { return  *(std::string*)this +  std::string(s); }	

	// prefix/postfix inc/dec
	long operator++() {                    return  *this = long(*this) + 1; }
	long operator--() {                    return  *this = long(*this) - 1; }
	long operator++(int) { long old = long(*this); *this = long(*this) + 1; return old; }
	long operator--(int) { long old = long(*this); *this = long(*this) - 1; return old; }
	// TODO for double
 };
	template<typename T, template<typename T, typename Ct=std::allocator<T> > class Ct >
Ct<T>&  operator<< (Ct<T>& C, field F)  { C.push_back(T(F));   return C; };


typedef field string_field; 

std::ostream&   operator<<      (ostream& os, const field& s) { os << (std::string)s; return os; };

*/


///////////////////////////////////////////////////////////////////////////////  F

		template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
	struct   F_t : std::deque<_Tp> {
		_Tp& 	operator()(size_t I) {
			if (this->size()<I+1) this->resize(I+1);
			return (*this)[I];
		};
	};


///////////////////////////////////////////////////////////////////////////////  AWK's vars

	F_t<strr> F;
		#define 	F0	F(0)
		#define 	F1	F(1)
		#define 	F2	F(2)
		#define 	F3	F(3)
		#define 	F4	F(4)
		#define 	F5	F(5)
		#define 	F6	F(6)
		#define 	F7	F(7)
		#define 	F8	F(8)
		#define 	F9	F(9)
		#define 	F10	F(10)
		#define 	F11	F(11)
		#define 	F12	F(12)
		#define 	F13	F(13)
		#define 	F14	F(14)
		#define 	F15	F(15)
		#define 	F16	F(16)
		#define 	F17	F(17)
		#define 	F18	F(18)
		#define 	F19	F(19)

	long NF = 0;
	long NR = 0;

	//string       __attribute__((unused))	line;

	#ifdef  arg_OFS
	string	     __attribute__((unused))	OFS(arg_OFS);
	#else
	string	     __attribute__((unused))	OFS(" ");
	#endif

	const char*  __attribute__((unused))	CSV="\"((?:(?:\\\\\")|[^\"])*)\"(\\s*,\\s*|$)";

	/*
	#ifdef  arg_IFS
	string       __attribute__((unused))	IFS(arg_IFS);
	#else
		#ifdef  arg_ifs
		string       __attribute__((unused))	IFS("([^" arg_ifs "]+)(" arg_ifs "|$)");	// field (data) is 1st group; IFS is second group
		#else
		string       __attribute__((unused))	IFS("(\\S+)(\\s+|$)");	// field (data) is 1st group; IFS is second group
		#endif
	#endif
	*/

	#ifdef  arg_ifs
	strr       __attribute__((unused))	IFS(arg_ifs);
	#else
	strr       __attribute__((unused))	IFS(" ");
	#endif

	strr IRS("\n");

///////////////////////////////////////////////////////////////////////////////  Utils functions

	#define 	WRL 	while(buf.get_rec(IRS, IFS, F))


///////////////////////////////////////////////////////////////////////////////  STRR HEAP


struct strr_heap_t {
		strr_heap_t	(const size_t size=1000000) :  _size(size),  B(new char[size])  {};
		~strr_heap_t	() { delete []B; };

	size_t	size	() { return _size; };
	void	clear	() { E = B; };

	size_t	_size;
	char 	*B, *E;
}; 

///////////////////////////////////////////////////////////////////////////////  INPUT BUF
struct buf_t {	
	const static	size_t		buf_size=1000000;
			char		*bod, *eod;	// data in buffer
			bool		good_file;	// !eof
			char		*bob, *eob;	// buffer dimentions
			const char 	*path;	
			int		fd;		// file

	explicit	buf_t 		(const char* path)
	        /*       : fd(open(path, O_RDONLY)),  good_file(true),  
	                 bob(new char[buf_size+1]),  bod(bob), eod(bob),  eob(bob+buf_size),  path(path)  {}
		*/

		: good_file(true),   path(path) 
	{	
		fd = open(path, O_RDONLY); 
		assert(fd>0);
		if (fd < 0)  throw  std::ios::failure (path);
		posix_fadvise (fd, 0, 0, POSIX_FADV_SEQUENTIAL);
		bob = new char[buf_size+1];  
		bod = eod = bob;
		eob = bob+buf_size;
	}

	explicit	buf_t 		(int fd)
		: fd(fd), good_file(true), bob(new char[buf_size+1]), bod(bob), eod(bob), eob(bob+buf_size), path(0)  {
		assert(fd>=0);
	}
			~buf_t		()	{ delete [] bob; }



	size_t		capacity	() const{ return buf_size; }
	ssize_t		size		() const{ return eod-bod; }
	bool		empty		() const{ return size() <= 0; }
	void		clear		()	{ eod  = bod = bob; }


	bool		fill		()	{
		size_t	buf_free_space = eob-eod;
		ssize_t	got;
		if  (buf_free_space > 0) { 
			retry:
			got = read (fd, eod,  buf_free_space);
			if (got == -1  &&  errno == EINTR)	goto  retry;
			if (got <=  0)				return  false;
			eod += got;
		}
		return  true;  				// TODO
	}


	bool		get_rec		(const strr IRS, const strr IFS, F_t<strr>& F)	{

		if (!good_file)   return false; 

		char *p   (bod);	
		char *bor (bod);	// record
		char *bof (bod);; 	// field

		F.clear();
		F.push_back(strr());	// F[0] - whole line

		while(1) {	//////////////////////////////////////////////////////// read until EOR
			size_t	unused_data = eod - p;
			if ( unused_data == 0 )  {
				size_t  buf_free_space = eob-eod;

				if (buf_free_space == 0) {  // relocate data to begining of buffer
					if (bor == bob ) {
						cerr << "warning: Line is too big for buffer. Splitting line.\n";
						goto return_rec; 
					} 

					ssize_t data_size = size();
					assert(eob-bob > 2*data_size); // FIXME: replace assert with realloc

					// rellocate everything to BOB
					memcpy(bob, bod, data_size);
					size_t diff = bod-bob;
					bod = bor = bob;
					eod = p = bob + data_size;
					bof -= diff;	
					for (size_t i=1;  i<F.size();  i++)  { F[i].B -= diff; F[i].E -= diff;}
				}

				if ( !(good_file = fill()) )  {
					if ( bor == p ) 	return false;
					else 			goto return_rec;
				}
			}

			if        ( *p == *(IFS.B))	{ F.push_back(strr(bof,p));  p += IFS.size();  bof = p; }
			else  if  ( *p == *(IRS.B))	{ goto return_rec; } 
			//strr data_tail(p, eod);
			//if        (is_separator(data_tail, IFS))	{ F.push_back(strr(bof,p));  p += IFS.size();  bof = p; }
			//else  if  (is_separator(data_tail, IRS))	{ goto return_rec; } 
			else                                      p++;
		} 


		return_rec: 
			// P should point to true EOR+1
			F.push_back(strr(bof,p));  
			NF = F.size()-1;
			F[0].B = bor;
			F[0].E = p;
			p += IRS.size();
			bod = p;
							assert(F[0].B == F[1].B);
							assert(F[0].E == F[NF].E);
			return true;
	}

		private: 
	bool is_separator(strr rec, strr sep) {
								assert(!sep.empty()  &&  !rec.empty());
		return   *rec.B == *sep.B;
		
		/*  TO ADD:  multibyte
		for ( size_t i=1;  i<sep.size() && i<rec.size();  i++) {
			if  (rec[i] == sep[i])  continue;
			else			return false;
		}
		return true;
		*/
	}


 };



#endif // SCC
