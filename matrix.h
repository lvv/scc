
#ifndef  LVV_MATRIX_H
#define  LVV_MATRIX_H

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
struct	matrix {
	matrix (size_t y_size,  size_t x_size, T val0=0):  M(vector<vector<T>>(y_size,  vector<T>(x_size, val0))) {};
	vector<vector<T> >  M;
	T&	operator()	(pt p)   		{ return M[p.y][p.x]; };
	T&	operator()	(size_t y,  size_t x)   { return M[y][x]; };
	size_t	y_size		()	 		{ return M.size(); };
	size_t	x_size		()	 		{ return M[0].size(); };
	bool	in		(pt p)	 		{ return 0<=p.y  &&  p.y < (T)y_size()  &&   0<=p.x && p.x < (T)x_size() ; };
};

#endif // LVV_MATRIX_H
