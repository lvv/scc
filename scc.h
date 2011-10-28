#ifndef  LVV_SCC_H
#define  LVV_SCC_H

///////////////////////////////////////////////////////////////////// BOOST
#ifndef NO_BOOST

	//#include <regex> 	 // std::regex - 4.6.0  fail with: scc 'RS("abc", R("abc"))'

	#include <boost/regex.hpp>
		using boost::regex;
		using boost::cmatch;
		using boost::regex_match;
		using boost::regex_token_iterator;
		using boost::sregex_token_iterator;
		using boost::cregex_token_iterator;


	#include <boost/format.hpp>
		using boost::format;
	//using namespace boost;

	
	// literals in gcc460  not implemented
	//boost::regex operator""R (const char* p, size_t n)	{ return boost::regex(p); };


 #endif


struct strr {           ///////////////////////////////////////////////////////////////////////////////  STRR
	const char *B, *E;

	// CTOR
	strr()			: B(0), E(0)  				{};
	strr(const char*   s)	: B(s)           			{  E = B + strlen(s); };
	strr(const string& s)	: B(s.data()),  E(s.data()+s.size())	{};
	strr(const char* B, const char* E):  B(B),  E(E)		{};

	// MEMBERS
	size_t	size()		{ return E-B; };
	size_t	empty()		{ return E-B == 0; };
	bool	operator==(strr sr)	{ return equal(B, E, sr.B); };

	// CONVERSION
	operator string			(void) { return string(B,E); }

	operator ssize_t		(void) {
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

typedef		std::vector<std::string>	vstr;
typedef		std::deque<std::string>		dstr;


///////////////////////////////////////////////////////////////////////////////  F

		template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
	struct   F_t : std::vector<_Tp> {
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

	long NF = 0;
	long NR = 0;

	string       __attribute__((unused))	line;

	#ifdef  arg_OFS
	string	     __attribute__((unused))	OFS(arg_OFS);
	#else
	string	     __attribute__((unused))	OFS(" ");
	#endif

	const char*  __attribute__((unused))	CSV="\"((?:(?:\\\\\")|[^\"])*)\"(\\s*,\\s*|$)";

	#ifdef  arg_IFS
	string       __attribute__((unused))	IFS(arg_IFS);
	#else
		#ifdef  arg_ifs
		string       __attribute__((unused))	IFS("([^" arg_ifs "]+)(" arg_ifs "|$)");	// field (data) is 1st group; IFS is second group
		#else
		string       __attribute__((unused))	IFS("(\\S+)(\\s+|$)");	// field (data) is 1st group; IFS is second group
		#endif
	#endif

	strr IRS("\n");

///////////////////////////////////////////////////////////////////////////////  Utils functions

	void	split() {
		#ifdef USE_BOOST
			boost::sregex_token_iterator   ite, it(line.begin(),line.end(), boost::regex(IFS),1);
			//boost::sregex_token_iterator   ite, it(line.begin(),line.end(), boost::regex(":"),1);
			while(it!=ite)   F.push_back(field(*it++));
		#else
			stringstream	ss(line);
			string		f;
			F.clear();
			while(ss >> f)   F.push_back(f);
		#endif

		NF = F.size();
	};

	bool  read_line() {
		F.clear();
		if (getline(cin,line)) {
			split();
			++ NR;
			return true;
		} else {
			return false;
		}
	};

	#ifdef xxxxUSE_BOOST
		// simplified regex_replace (now accept const char* for regex)
			template <class traits, class charT>
			basic_string<charT>
		RR (
			const basic_string<charT>& s,
	               	const basic_regex<charT, traits>& e,
			const basic_string<charT>& fmt,
			boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default
		)  {
			return boost::regex_replace<traits, charT>  (s, e, fmt, flags);
		}

			template <class traits, class charT>
			basic_string<charT>
		RR (
			const basic_string<charT>& s,
	               	//const basic_regex<charT, traits>& e,
	               	const char* r,
			const basic_string<charT>& fmt,
			boost::regex_constants::match_flag_type flags = boost::regex_constants::match_default
		)  {
			return boost::regex_replace<traits, charT>  (s, boost::regex(r), fmt, flags);
		}

	#endif

	#define WRL  while(read_line())

///// boost

#ifdef  USE_BOOST

#define 	R		boost::regex
//R 	operator "" r(const char * s, size_t n) {return R(s);};
#define		FMT 		boost::format

#define 	RM		boost::regex_match
#define 	RS		boost::regex_search
#define 	RR		boost::regex_replace
		// usage: scc 'str s="aa bb"; RR(s, R("(\\w+)"),"*\\1*")'
	
//#define 	M		boost::match
#define 	CM		boost::cmatch
#define 	SM		boost::cmatch

//typedef 	boost::regex_iterator		RI;
typedef 	boost::sregex_iterator          SRI;
typedef 	boost::cregex_iterator          CRI;		
		// usage:  echo 'aa bb' | scc 'WRL {SRI it(line.begin(), line.end(), R("\\w+")), e; while (it!=e) cout << *it++ << endl;}
//typedef 	boost::regex_token_iterator     RTI;		
typedef 	boost::sregex_token_iterator    SRTI;		
typedef 	boost::cregex_token_iterator    CRTI;		
#define 	MRTI		boost::make_regex_token_iterator 

#endif

struct buf_t {		///////////////////////////////////////////////////////////////////////////////  BUF
	const static	size_t		buf_size=100;
			char		*bob, *eob;	// buffer dimentions
			char		*bod, *eod;	// data in buffer
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

	bool		get_rec		(strr IRS, strr IFS, vector<strr>& F)	{

		if (!good_file)   return false; 

		char *bor, *p;	// record
		char *bof; 	// field
		bor = bof = p = bod;
		F.clear();
		F.push_back(strr());	// F[0] - whole line

		while(1) {	//////////////////////////////////////////////////////// read until EOR
			size_t	unchecked = eod - p;
			if ( unchecked == 0 )  {
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

			strr data_tail(p, eod);
			if        (is_separator(data_tail, IFS))	{ F.push_back(strr(bof,p));  p += IFS.size(); bof = p; }
			else  if  (is_separator(data_tail, IRS))	{ goto return_rec; } 
			else                                      p++;
		} 


		return_rec: 
			// P shoud point to true EOR+1
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
		if  (*rec.B != *sep.B)	return false;
		else			return true;
		
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
