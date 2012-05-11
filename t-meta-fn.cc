
// http://stackoverflow.com/questions/4170201/c0x-overloading-on-lambda-arity
#include "io.h"
#include "meta.h"

	template<typename F,typename R>
void do_stuff(F& f,R (F::*mf)() const) {
    (f.*mf)();
}

	template<typename F,typename R,typename A1>
void do_stuff(F& f,R (F::*mf)(A1) const) {
    (f.*mf)(99);
}

	template<typename F,typename R,typename A1,typename A2>
void do_stuff(F& f,R (F::*mf)(A1,A2) const) {
    (f.*mf)(42,123);
}

	template<typename F>
void do_stuff(F f) {
    do_stuff(f,&F::operator());
}


int main() {
    do_stuff([]			{__ "no args";});
    do_stuff([](int a1)		{__ "1 args=", a1;});
    do_stuff([](int a1,int a2)	{__ "2 args=", a1, a2;});
}
