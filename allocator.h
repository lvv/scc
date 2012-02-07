#ifndef LVV_ALLOCATOR_H
#define LVV_ALLOCATOR_H

#include <iostream>

		template<typename T>
struct trace_allocator : public std::allocator<T> {
		typename std::allocator<T>::pointer
	allocate(typename std::allocator<T>::size_type n, typename std::allocator<void>::const_pointer = 0) {
	        std::cout << "Allocating: " << n << " itens." << '\n';
	        return reinterpret_cast<typename std::allocator<T>::pointer>(::operator new(n * sizeof (T))); 
	}

	        void
	deallocate(typename std::allocator<T>::pointer p, typename std::allocator<T>::size_type n) {
	    std::cout << "Dealloc: " <<  n << " itens." << '\n';
	    ::operator delete(p); 
	}

	template<typename U> struct rebind { typedef trace_allocator<U> other; };
};

#endif
