// TR http://stackoverflow.com/questions/12556638/stl-container-constructors-allocator-parameter-and-scoped-allocators
// TR sample allocator -- http://stackoverflow.com/questions/8089850/how-to-overwrite-the-default-behavor-of-the-construct-method-in-the-allocator-cl/8090161#8090161
// TR http://www2.research.att.com/~bs/rg++0xFAQ.html#scoped-allocator
// TR http://stackoverflow.com/questions/11373796/curom-memory-allocator-for-stl-map
// TR http://www.codeguru.com/cpp/cpp/cpp_mfc/stl/article.php/c4079/Allocators-STL.htm
// TO TRY -- http://stackoverflow.com/questions/17548032/c11-memory-pool-class-workaround-for-static-casting-from-void

/* (from c++ now presentation) - A Minimal Allocator • Much of the rg++03 boilerplate is now defaulted

	template <class T>
	class MyAlloc {
		public:
		typedef T value_type;
		MyAlloc();
		template <class U>
		MyAlloc(const MyAlloc<U>&);
		T* allocate(std::size_t);
		void deallocate(T*, std::size_t);
	};
	template <class T, class U> bool operator==(const MyAlloc<T>&, const MyAlloc<U>&);
	template <class T, class U> bool operator!=(const MyAlloc<T>&, const MyAlloc<U>&);
*/

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


		template<typename T>					//  NO-DELETE ALLOCATOR
struct nd_allocator : std::allocator<T> {
		static const size_t	capacity  = 200*1000*1000;
		static char		*data;
		static char		*b;		// free begin
		static char		*e;		// end of data buffer;
		static int		ref_cnt;
	 nd_allocator() :   std::allocator<T>()  {
		if(!ref_cnt)  {
			data	= new char[capacity];
			b	= data;
			e	= data + capacity;
		};
		++ref_cnt;
	 }

	 template<typename U>
	 nd_allocator(const nd_allocator<U>& other)  { ref_cnt++; };
	 
	~nd_allocator()  { --ref_cnt;  if (!ref_cnt)  delete [] data; };

		typename std::allocator<T>::pointer
	allocate(typename std::allocator<T>::size_type n, typename std::allocator<void>::const_pointer = 0) {
							//__ "\t nd: +" << n << " x " << sizeof(T);
	        auto ret =  reinterpret_cast <typename std::allocator<T>::pointer> (b);
	        b  +=  n * sizeof (T);
		if (b>e) throw (std::bad_alloc());
	        return  ret;
	}

	        void
	deallocate(typename std::allocator<T>::pointer p, typename std::allocator<T>::size_type n) {
		//::operator delete(p);
		//assert (false);
						//__ "\t nd: -" << n;
	}

	template<typename U> struct rebind { typedef nd_allocator<U> other; };
};

template<typename T> char*	nd_allocator<T>::data		= nullptr;
template<typename T> char*	nd_allocator<T>::b		= nullptr;
template<typename T> char*	nd_allocator<T>::e		= nullptr;
template<typename T> int	nd_allocator<T>::ref_cnt	= 0;

#endif
