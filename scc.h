#ifndef  LVV_SCC_H
#define  LVV_SCC_H

	//using namespace std;

	struct   F_t : std::deque<str> {
		str& 	operator()(size_t I) {
			this->resize(I+1);
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
	string	     __attribute__((unused))	OFS(" ");
	string       __attribute__((unused))	IFS("(\\S+)(\\s+|$)");
	const char*  __attribute__((unused))	CSV="\"((?:(?:\\\\\")|[^\"])*)\"(\\s*,\\s*|$)";

	void	split() {
		#ifdef USE_BOOST
			SRTI ite, it(line.begin(),line.end(),R(IFS),1);
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

	#define WRL  while(read_line())

#endif // SCC
