#include <errno.h>
#include <unistd.h>
#include <scc/simple.h>
#include <scc/scc.h>




int main() {
	buf_t buf(0); // stdin

	size_t cnt=0;
	size_t sz = 0;
	size_t f_sz = 0;
	size_t f_cnt = 0;

	F_t<strr> F;
	while(buf.get_rec('\n', '.', F)) {
		f_cnt += F.size();
		for(size_t i=0;  i<F.size();  i++)  { f_sz +=  F[i].size();  _ " \"", F[i], "\" "; }
		__ "\t" ^ cnt++; 
	}
	__ "total count: \t", cnt;
	__ "total field size: \t", f_sz;
	__ "total field count: \t", f_cnt;

}

