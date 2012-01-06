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
	const char *b, *e;

	// CTOR
	strr()			: b(0), e(0)				{};
	strr(const char*   s)	: b(s)					{  e = b + strlen(s); };
	//strr(const string& s)	: b(s.data()),  e(s.data()+s.size())	{};
	strr(const char* b, const char* e):  b(b),  e(e)		{};
	//strr& operator=(const strr& sr) : b(sr.b), e(sr

	// MEMBERS
	size_t		size()		const { return e-b; };
	size_t		empty()		const { return e-b == 0; };
	bool		operator==(strr sr) const { return equal(b, e, sr.b); };

	typedef		const char*		iterator;
	typedef		const char* const	const_iterator;
	iterator	begin()		const { return b; };
	iterator	end()		const { return e; };
 };

// traits
template<>	struct  is_container <strr>	: std::false_type {};	// we have strr own printer
template<>	struct  is_string    <strr>	: std::true_type  {};	// so that strr acceptable to regex expressions

		ostream&
 operator<<      (ostream& os, const strr f) {
	assert(f.b && f.e);
	const char *p = f.b;
	while (p!=f.e)   os << *p++;
	return os;
 };



	struct  strr_allocator_t {
			const static size_t  size = 10000;
			char *spool_begin;
			char *spool_end;
			char *data_end;
		strr_allocator_t() :  spool_begin(new char[size]),  spool_end(spool_begin+size)  { clear(); };
		~strr_allocator_t() { delete spool_begin;};
		void clear() { data_end = spool_begin; }

		char*  allocate(size_t sz)   {
			char *p = data_end;
			data_end += sz;
			assert(data_end <= spool_end);
			return p;
		}
	};


static strr_allocator_t  strr_allocator;

struct	fld : strr {

	fld()					: strr()	{};
	fld(const char* b, const char* e)	: strr(b, e)	{};
	fld(const char*   s)			: strr(s)	{};


	// CONVERT TO T
	template<typename T> T convert_to()    const { istringstream is;  T i;  is.str(string(this->b, this->e));  is >> i;  return i; }

	template<typename T> explicit	operator  T()      const {  return  convert_to<T>(); }
	/* non-explicit, default */	operator  double() const {  return  convert_to<double>(); }


	// CONVERT TO INTEGRAL
		template<typename T>
	T TO_TEST_to_integral() const {
		T		sign	= 1;
		T		base	= 10;
		const char	*p	= b;

		for (;  p<e-1;  p++) {			// read prefix
			switch(*p) {
				case ' ':;   case '\t': continue;
				case '-':	sign = -1;  p++;  goto end_prefix;
				case '+':	p++;  goto end_prefix;
				default:	goto end_prefix;
			}
		}

		end_prefix:;

		ssize_t  n=0;				// read number
		for (;  p<e && isdigit(*p);  p++)  {
			n = n*base + (*p-'0');
		}
		return sign*n;
	}

	// ASSIGNMENT
		template<typename IT>
		fld&
	assign(IT b_, IT e_)  {
		size_t size = e_-b_;
		b = strr_allocator.allocate(size);
		e = b + size;
		std::copy (b_,  e_,  const_cast<char*>(b));
		return *this;
	}

	// op=
	                        fld&	operator= (const fld& x)	{ assign(x.b, x.e); return *this; }
	template<typename T>	fld&	operator= (const T& x)	{ ostringstream os; os << x;  string s = os.str(); assign(s.begin(), s.end()); return *this; }

	// op+=
	template<typename T>	fld&	operator+= (T x)		{  return  *this = T(*this) + x; }
				fld&	operator+= (const fld& s2)	{  return  *this = double(*this) + double(s2); }
	// op-=
	template<typename T>	fld&	operator-= (T x)		{  return  *this = T(*this) - x; }
				fld&	operator-= (const fld& s2)	{  return  *this = double(*this) - double(s2); }
	// op*=
	template<typename T>	fld&	operator*= (T x)		{  return  *this = T(*this) * x; }
				fld&	operator*= (const fld& s2)	{  return  *this = double(*this) * double(s2); }
	// op/=
	template<typename T>	fld&	operator/= (T x)		{  return  *this = T(*this) / x; }
				fld&	operator/= (const fld& s2)	{  return  *this = double(*this) / double(s2); }
};


	// op+
	template<typename T>	T	operator+ (const fld& sr, T x)		{  return  T(sr) + x; }
	template<typename T>	T	operator+ (T x, const fld& sr)		{  return  T(sr) + x; }
	double				operator+ (const fld& s1, const fld& s2){  return  double(s1) + double(s2); }

	// op-
	template<typename T>	T	operator- (const fld& sr, T x)		{  return  T(sr) - x; }
	template<typename T>	T	operator- (T x, const fld& sr)		{  return  T(sr) - x; }
	double				operator- (const fld& s1, const fld& s2){  return  double(s1) - double(s2); }

	// op*
	template<typename T>	T	operator* (const fld& sr, T x)		{  return  T(sr) * x; }
	template<typename T>	T	operator* (T x, const fld& sr)		{  return  T(sr) * x; }
	double				operator* (const fld& s1, const fld& s2){  return  double(s1) * double(s2); }

	// op/
	template<typename T>	T	operator/ (const fld& sr, T x)		{  return  T(sr) / x; }
	template<typename T>	T	operator/ (T x, const fld& sr)		{  return  x / T(sr); }
	double				operator/ (const fld& s1, const fld& s2){  return  double(s1) / double(s2); }

	// op%
	template<typename T>	T	operator% (const fld& sr, T x)		{  return  T(sr) % x; }
	template<typename T>	T	operator% (T x, const fld& sr)		{  return  T(sr) % x; }
	long				operator% (const fld& s1, const fld& s2){  return  long(s1) * long(s2); }
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

		template<typename T>
	struct   R_t : std::deque<T> {
		T&	operator()(size_t I) {
			if (this->size()<I+1) this->resize(I+1);
			return (*this)[I];
		};
		T  a;	// All_of record

	};


///////////////////////////////////////////////////////////////////////////////  AWK's vars

	R_t<fld> F;
		#define		$0	F.a
		#define		$1	F(0)
		#define		$2	F(1)
		#define		$3	F(2)
		#define		$4	F(3)
		#define		$5	F(4)
		#define		$6	F(5)
		#define		$7	F(6)
		#define		$8	F(7)
		#define		$9	F(8)
		#define		$10	F(9)
		#define		$11	F(10)
		#define		$12	F(11)
		#define		$13	F(12)
		#define		$14	F(13)
		#define		$15	F(14)
		#define		$16	F(15)
		#define		$17	F(16)
		#define		$18	F(17)
		#define		$19	F(18)
		#define		$20	F(19)

		#define		$NF	F(NF-1)
		#define		$	F

	long NF = 0;
	long NR = 0;

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
struct buf_t {
	const static	size_t		buf_size=1000000;
			bool		good_file;	// !eof
			const char		*bob, *eob;	// buffer dimentions
			const char		*bod, *eod;	// data in buffer
			const char	*path;
			int		fd;		// file

	explicit	buf_t		(const char* path)
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

	explicit	buf_t		(int fd)
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
		return  true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////  GET_REC
		template <typename sep_T>
	bool		get_rec		(sep_T RS, sep_T FS, R_t<fld>& F)	{

		if (!good_file)   return false;

		const char *p   (bod);
		F.a.b = p;				// record

		strr_allocator.clear();

		while(1) {	//  read until EOR
			size_t	unused_data = eod - p;
			if (!unused_data)  {
				size_t  buf_free_space = eob-eod;

				if (!buf_free_space) {  // relocate data to begining of buffer
					if (F.a.b == bob ) {
						cerr << "warning: Line is too big for buffer. Splitting line.\n";
						goto return_rec;
					}

					ssize_t data_size = size();
					assert(eob-bob > 2*data_size); // FIXME: replace assert with realloc

					memcpy(const_cast<char*>(bob), const_cast<char*>(bod), data_size);
					size_t diff = bod-bob;
					bod = F.a.b = bob;
					eod = p = bob + data_size;
				}

				if ( !(good_file = fill()) )  {
					if ( F.a.b == p )	return false;				// if EOF at BoR --> return EOF
					else			{ F.a.e = p;  goto return_rec; }	// else close current record
				}
			}

			p = F.a.e = search (p, eod, RS.b, RS.e);

			if (p != eod) {
				assert(*p == *RS.b);
				goto  return_rec;
			}
		}

		return_rec:
			parse_rec(F);
			NF  = F.size();
			p  += RS.size();
			bod = p;
			NR++;
			return true;
	}

  private:

	void parse_rec (R_t<fld>& F) {
		F.clear();
		if (F.a.empty())  return;
		const char *sep, *eof;
		const char *bof = F.a.b;

		do {
			while( bof < F.a.e   &&   PAD_tab[*bof]  )  bof++;		// skip padding
			sep = eof = search(bof, F.a.e, FS.b, FS.e);			//
			while( bof < (eof-1)  &&   PAD_tab[*(eof-1)]  )  eof--;		// eat  padding begore FS
			F.push_back(fld(bof,eof));
			bof = sep + FS.size();
		}  while (bof < F.a.e);
	}

 };




#endif // SCC
