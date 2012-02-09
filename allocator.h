#ifndef LVV_ALLOCATOR_H
#define LVV_ALLOCATOR_H

#include <assert.h>
#include <iostream>
	using std::cout;
	using std::endl;
	using std::flush;

		template<typename T>					//  TRACE ALLOCATOR
struct trace_allocator : std::allocator<T> {

		typename std::allocator<T>::pointer
	allocate(typename std::allocator<T>::size_type n, typename std::allocator<void>::const_pointer = 0) {
		cout << "\tAllocating: " << n << " itens." << endl << flush;
		return reinterpret_cast<typename std::allocator<T>::pointer>(::operator new(n * sizeof (T))); 
	}

	trace_allocator() {};
	template<class Other> trace_allocator( const trace_allocator<Other>& _Right ) {};   // conversion CTOR needed for gg++

	        void
	deallocate(typename std::allocator<T>::pointer p, typename std::allocator<T>::size_type n) {
		cout << "\tDealloc: " <<  n << " itens." << endl << flush;
		::operator delete(p); 
	}

	template<typename U> struct rebind { typedef trace_allocator<U> other; };


};


		template<typename T>					//  NO DELETE ALLOCATOR
struct nd_allocator : std::allocator<T> {
		static const size_t	capacity  = 100*1000*1000;
		static char		*data;
		static char		*b;		// free begin
		static char		*e;		// end of data buffer;
	 //nd_allocator() : std::allocator<T>(),  data(new char[capacity]),  b(data),  e(data + capacity) {};
	 //nd_allocator() :   std::allocator<T>() {if (!data)  data = new char[capacity];  b=data;  e=data + capacity; };
	 nd_allocator() :   std::allocator<T>() {};
	 template<typename U>
	 nd_allocator(const nd_allocator<U>& other)  {}
	~nd_allocator()  {};					//  TODO: atexit() - delete[]  data; ;

		typename std::allocator<T>::pointer
	allocate(typename std::allocator<T>::size_type n, typename std::allocator<void>::const_pointer = 0) {
							__ "\t nd: +" << n << " x " << sizeof(T);
	        auto ret =  reinterpret_cast <typename std::allocator<T>::pointer> (b);
	        b  +=  n * sizeof (T);
		if (b>e) throw (std::bad_alloc());
	        return  ret;
	}

	        void
	deallocate(typename std::allocator<T>::pointer p, typename std::allocator<T>::size_type n) {
		//::operator delete(p);
		//assert (false);
							__ "\t nd: -" << n;
	}

	template<typename U> struct rebind { typedef nd_allocator<U> other; };
};

template<typename T> char* nd_allocator<T>::data = new char[capacity];
template<typename T> char* nd_allocator<T>::b = nd_allocator<char>::data;
template<typename T> char* nd_allocator<T>::e = nd_allocator<char>::data + capacity;


#endif
