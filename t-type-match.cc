//#include <scc/simple.h>
#include <iostream>
#include <string>
	using namespace std;

template<typename T> 	void  print(T v)		{ cout << "    unknoun:  "	<< v << endl;}
template<> 		void  print(int v)		{ cout << "        int:  "	<< v << endl;}
template<> 		void  print(double v)		{ cout << "     double:  "	<< v << endl;}
template<typename T> 	void  print(T v[])		{ cout << "        T[]:  "	;  for(int i=0; i<3; i++) cout << v[i] << " ";  cout << " ..." << endl;}
template<> 		void  print(int v[])		{ cout << "      int[]:  "	;  for(int i=0; i<3; i++) cout << v[i] << " ";  cout << " ..." << endl;}
template<> 		void  print(const char* v)	{ cout << "const char*:  "	<< v << endl;}
template<typename T> 	void  print(basic_string<T> v)	{ cout << "     string:  "	<< v << endl;}


int main() {

	print(1);
	print(1.1);
	print("c-string");
	print((int[]){1,2,3});
	print((float[]){1.1,2.2,3.3});
	print(string("c++ string"));
}
