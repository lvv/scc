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
		char		*data;
		char		*b;		// free begin
		char		*e;		// end of data buffer;
	 nd_allocator() : std::allocator<T>(),  data(new char[capacity]),  b(data),  e(data + capacity) {};
	 template<typename U>
	 nd_allocator(const nd_allocator<U>& a) : data(a.data), b(a.b), e(a.e) {}
	~nd_allocator()  { delete[]  data; };

		typename std::allocator<T>::pointer
	allocate(typename std::allocator<T>::size_type n, typename std::allocator<void>::const_pointer = 0) {
	        auto ret =  reinterpret_cast <typename std::allocator<T>::pointer> (b);
	        b  +=  n * sizeof (T);
		if (b>e) throw (std::bad_alloc());
	        return  ret;
	}

	        void
	deallocate(typename std::allocator<T>::pointer p, typename std::allocator<T>::size_type n) {
		//::operator delete(p);
		//assert (false);
		cout << "\t de-alloc  " << n << endl;
	}

	template<typename U> struct rebind { typedef nd_allocator<U> other; };
};


#endif
