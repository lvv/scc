
#ifndef  LVV_MATRIX_H
#define  LVV_MATRIX_H

//#include<cstdint>
#include<vector>
	using std::vector;
//#include<algorithm>

//using namespace std;

	template<typename T=int>
struct	pt {
	int x, y;
	pt (){};
	pt (int x, int y) : x(x), y(y) {};
	bool	operator==	(pt rhs)	{ return  x==rhs.x &&  y==rhs.y; };
	bool	operator!=	(pt rhs)	{ return  ! (*this == rhs); };
	pt	operator+	(pt rhs)	{ return  pt(x+rhs.x, y+rhs.y); };
	pt&	operator+=	(pt rhs)	{ x+=rhs.x;  y+=rhs.y;  return  *this; };
	static pt	up		()		{ return pt(0,-1);};
	static pt	right		()		{ return pt(1,0);};
	static pt	down		()		{ return pt(0,1);};
	static pt	left		()		{ return pt(-1,0);};
	
};

	
	template<typename T>
std::ostream&   operator<<      (ostream& os, const pt<T>& P) { os << "(" << P.x << "," << P.y << ")"; return os; };


	template<typename T=int>
struct	matrix {
	vector<vector<T> >  M;
	explicit matrix (size_t x_size, size_t y_size,  T val0=0)
		:  M(y_size,  vector<T>(x_size, val0)) {};
	T&	operator()	(pt<T> p)   		{ return M[p.y][p.x]; };
	T&	operator()	(size_t x,  size_t y)   { return M[y][x]; };
	size_t	y_size		()	 		{ return M.size(); };
	size_t	x_size		()	 		{ return M[0].size(); };
	size_t	h		()	 		{ return M.size(); };
	size_t	w		()	 		{ return M[0].size(); };
	bool	on_cell		(pt<T> p) 		{ return 0<=p.y  &&  p.y <  (T)y_size()  &&   0<=p.x && p.x < (T)x_size() ; };
	bool	on_grid		(pt<T> p) 		{ return 0<=p.y  &&  p.y <= (T)y_size()  &&   0<=p.x && p.x < (T)x_size() ; };
	bool	on_border	(pt<T> p) 		{ return 0==p.y || (T)h()==p.y ||  p.x==0 || (T)p.x==w() ; };
};

	#ifdef 	MODERN_GCC
	//template<typename T, template<typename T, typename Ct=std::allocator<T> > class Ct >
	template<typename T, template<typename T> class Mt >
	std::istream&                                              
operator>>      (istream& is, matrix<T>& M)    {
	for(typename Mt<T>::iterator it=M.begin();  it!=M.end();  it++)
		if(!(is>>*it)) break;
	return is;
}; 
	#endif

	template<typename T>
std::ostream&   operator<<      (ostream& os, const matrix<T>& M) { for (size_t i=0;  i<M.M.size();  i++) os << M.M[i] << std::endl; return os; };

#endif // LVV_MATRIX_H
