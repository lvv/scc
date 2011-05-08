#ifndef  LVV_SCC_H
#define  LVV_SCC_H

	//using namespace std;

	struct   F_t : std::deque<str> {
		str& 	operator()(size_t I) {
			if (this->size()<I+1) this->resize(I+1);
			return (*this)[I];
		};
	};

	std::ostream&   operator<<      (ostream& os, const deque<str, std::allocator<str> >& C) {              
		os << "{";
		auto it=C.begin();
		for (int i=0;   i < int(C.size())-1;   i++, it++)	os  << *it <<  ", ";
		if (!C.empty())  					os  << *it;
		os << "}";
		return os;
	};

	F_t F;
	int NF = 0;
	int NR = -1;

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
	string       __attribute__((unused))	IFS("(\\S+)(\\s+|$)");	// IFS is second group (\2)
	#endif


	void	split() {
		#ifdef USE_BOOST
			boost::sregex_token_iterator   ite, it(line.begin(),line.end(), boost::regex(IFS),1);
			while(it!=ite)   F.push_back(str(*it++));
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

	#ifdef xxxUSE_BOOST
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

#endif // SCC
