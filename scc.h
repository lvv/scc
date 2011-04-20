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

	string	 __attribute__((unused))	line;
	char 	 __attribute__((unused))	IFS=' ';
	string	 __attribute__((unused))	OFS(" ");


	void	split() {
		stringstream	ss(line);
		string		f;

		F.clear();
		while(ss >> f) {
			F.push_back(f);
		}
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
