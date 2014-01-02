// strr, fld type

					#ifndef  SCC_FLD_H
					#define  SCC_FLD_H

struct strr {         ///////////////////////////////////////////////////////  STRR
	const char *b, *e;

	// CTOR
	strr()			: b(0), e(0)				{};
	strr(const char*   s)	: b(s)					{  e = b;  while(*++e); };
	strr(const char* b, const char* e):  b(b),  e(e)		{};

	// MEMBERS
	size_t		size()		const { return e-b; };
	size_t		empty()		const { return e-b == 0; };
	bool		operator==(strr sr) const { return std::equal(b, e, sr.b); };

	typedef		const char*		iterator;
	typedef		const char* const	const_iterator;
	iterator	begin()		const { return b; };
	iterator	end()		const { return e; };
 };


#ifdef scc_RO
	//namespace    {
	namespace ro {
		template<>		struct  is_ioable_t    <strr>:   std::true_type  {};
		template<>		struct  is_range_t <strr>:   std::false_type  {};
	};
	//};
#endif

	std::ostream&
operator<<      (std::ostream& os, const strr& sr) {
	os.write(sr.b, sr.size());
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
	// FIXME -- DTOR


	// CONVERT FROM T
	explicit fld(const char*   s)			: strr(s)	{};
	template<size_t N> fld(const char   (&s)[N])			: strr(s)	{};
	explicit fld(const std::string& s)	{ assign (s.begin(), s.end()); };
	explicit fld(int           i)	{*this = (long)i;};
	explicit fld(long          i)	{*this = (long)i;};
	explicit fld(double        i)	{*this = (double)i;};

	// CONVERT TO T
	template<typename T> T convert_to()    const { std::istringstream is;  T x;  is.str(std::string(this->b, this->e));  is >> x;  return x; }

	template<typename T> explicit	operator  T()      const {  return  convert_to<T>(); }
	/* non-explicit, default */	operator  double() const {  return  convert_to<double>(); }

					operator  std::string() const {  return  string(this->b, this->e); }



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

	template<size_t N>      fld&	operator= (const char (&S)[N])	{ *this = fld(S); return *this; }
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
	//template<typename T>	T	operator* (const fld& sr, T x)		{  return  T(sr) * x; }
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


// traits
#ifdef scc_RO
	//namespace    {
	namespace ro {
		template<>	struct  is_ioable_t <fld>       : std::true_type  {};
		template<>	struct  is_range_t  <fld>	: std::false_type  {};

		template<>	struct  is_string_t <strr>	: std::true_type  {};	// so that strr acceptable to regex expressions
		template<>	struct  is_string_t  <fld>	: std::true_type  {};	// so that strr acceptable to regex expressions
	};
	//};
#endif

					#endif // SCC_AWK
