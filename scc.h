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

		#define 	$0	F(0)
		#define 	$1	F(1)
		#define 	$2	F(2)
		#define 	$3	F(3)
		#define 	$4	F(4)
		#define 	$5	F(5)
		#define 	$6	F(6)
		#define 	$7	F(7)
		#define 	$8	F(8)
		#define 	$9	F(9)
		#define 	$10	F(10)
		#define 	$11	F(11)
		#define 	$12	F(12)
		#define 	$13	F(13)
		#define 	$14	F(14)
		#define 	$15	F(15)
		#define 	$16	F(16)
		#define 	$17	F(17)
		#define 	$18	F(18)
		#define 	$19	F(19)

		#define 	$NF	F(NF)
		#define 	$	F

	long NF = 0;
	long NR = 0;

	//string       __attribute__((unused))	line;


	const char*  __attribute__((unused))	CSV="\"((?:(?:\\\\\")|[^\"])*)\"(\\s*,\\s*|$)";

	/*
	#ifdef  scc_IFS
	string       __attribute__((unused))	IFS(scc_IFS);
	#else
		#ifdef  scc_ifs
		string       __attribute__((unused))	IFS("([^" scc_ifs "]+)(" scc_ifs "|$)");	// field (data) is 1st group; IFS is second group
		#else
		string       __attribute__((unused))	IFS("(\\S+)(\\s+|$)");	// field (data) is 1st group; IFS is second group
		#endif
	#endif
	*/

	strr	ORS;
	strr	IRS;

	strr	OFS
		#ifdef  scc_OFS
			(scc_OFS);
		#else
			(" ");
		#endif

	strr	IFS 
		#ifdef  scc_ifs
			(scc_ifs);
		#else
			(" ");
		#endif



///////////////////////////////////////////////////////////////////////////////  Utils functions

	#define 	WRL 	while(read_line())


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
			bool		good_file;	// !eof
			const char		*bob, *eob;	// buffer dimentions
			const char		*bod, *eod;	// data in buffer
			const char 	*path;	
			int		fd;		// file

	explicit	buf_t 		(const char* path)
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
		: good_file(true), bob(new char[buf_size+1]), eob(bob+buf_size), bod(bob), eod(bob), path(0), fd(fd) {
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
			got = read (fd, const_cast<char*>(eod),  buf_free_space);
			if (got == -1  &&  errno == EINTR)	goto  retry;
			if (got <=  0)				return  false;
			eod += got;
		}
		return  true;  				// TODO
	}


		template <typename sep_T>
	bool		get_rec		(sep_T IRS, sep_T IFS, F_t<strr>& F)	{

		if (!good_file)   return false; 

		const char *p   (bod);	
		const char *bor (bod);	// record
		const char *bof (bod);; 	// field

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
					memcpy(const_cast<char*>(bob), const_cast<char*>(bod), data_size);
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

			if        (is_separator(p, eod, IFS))	{ F.push_back(strr(bof,p));  p += sep_size(IFS);  bof = p; }
			else  if  (is_separator(p, eod, IRS))	{ goto return_rec; } 
			else                                      p++;
		} 


		return_rec: 
			F.push_back(strr(bof,p));  
			NF = F.size()-1;
			F[0].B = bor;
			F[0].E = p;
			//p += IRS.size();
			p += sep_size(IRS);
			bod = p;
							assert(F[0].B == F[1].B);
							assert(F[0].E == F[NF].E);
			return true;
	}

  private: 

	static bool is_separator(const char* recB, const char* recE,  const strr sep) {  // Is begining of Rec a seperator?
		assert(!sep.empty()  &&  recE-recB > 0);
		return	*recB == *sep.B    		
			&&  size_t(recE-recB)  >=  sep.size() 
			&&  std::equal(sep.B+1, sep.E, recB+1);
	}

	static bool is_separator(const char* recB, const char* recE,  char sep) { 
		assert(recE-recB > 0);
		return	*recB == sep;
	}

	constexpr static size_t		sep_size(char c)	{return sizeof(c);}
	static size_t			sep_size(const strr s)	{return s.size();}

 };



#endif // SCC
