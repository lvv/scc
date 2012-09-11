template<class T>   void  f(T&  t)  {};
template<class T>   void  f(T&& t)  {};

int main() {
        int lv{11};
        f(lv);  // error: ambigues overload
}
