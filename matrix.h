
#ifndef  LVV_MATRIX_H
#define  LVV_MATRIX_H

#include<iostream>
	using std::cout;
	using std::endl;
#include<vector>
	using std::vector;
//#include<algorithm>

//using namespace std;

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
std::ostream&   operator<<      (std::ostream& os, const pt& P) { os << "(" << P.x << "," << P.y << ")"; return os; };


	template<typename T, template<typename TT, typename Al=std::allocator<TT> > class Rg=std::vector>
struct	matrix {
			//typedef		typename vector<T>::iterator		iterator ;
			//typedef		typename vector<T>::const_iterator	const_iterator ;
		size_t w_,h_;
		vector<T>  V;
	explicit matrix (size_t h, size_t w,  T val0=0) : w_(w), h_(h), V(h*w,  val0)  {};
	T&	operator()	(pt p)   			{ return V[w_ * p.y + p.x]; };
	T&	operator()	(size_t x,  size_t y)   	{ return V[w_ * y + x]; };
	const T&operator()	(size_t x,  size_t y)  const  	{ return V[w_ * y + x]; };
	size_t	h		() const	 		{ return h_; };
	size_t	w		() const	 		{ return w_; };
	bool	in		(pt p) const		{ return 0<=p.y  &&  p.y <  (T)h()  &&   0<=p.x && p.x < (T)w() ; };
	bool	on_cell		(pt p) const		{ return 0<=p.y  &&  p.y <  (T)h()  &&   0<=p.x && p.x < (T)w() ; };
	bool	on_grid		(pt p) const		{ return 0<=p.y  &&  p.y <= (T)h()  &&   0<=p.x && p.x < (T)w() ; };
	bool	on_border	(pt p) const		{ return 0==p.y || (T)h()==p.y ||  p.x==0 || (T)p.x==w() ; };
	bool	next		(pt& p)		{ pt pn;  pn.x = (p.x+1)%w();   pn.y = p.y+(pn.x<p.x);  p=pn; return p.y<(int)h(); };
};

	template<typename T>
	std::istream&
operator>>      (std::istream& is, matrix<T>& M)    {
	for(size_t j=0; j<M.h(); j++)
		for (size_t i=0;  i<M.w();  i++)
			if (!(is>> M(i,j))) break;
	return is;
};

	template<typename T>
	std::ostream&
operator<<      (std::ostream& os, const matrix<T>& M) {
	for(size_t j=0; j<M.h(); j++)  {
		for (size_t i=0;  i<M.w();  i++)  {
			os << M(i,j) << " ";
		}
		os << "\n";
	}
	return os;
};

#endif // LVV_MATRIX_H
