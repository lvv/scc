
ASCIIDOC_FILTERS ?= /usr/share/asciidoc/filters


ifeq ($(USER),lvv)
	HOMEDIR := /home/lvv/p/volnitsky.com/
	INCLUDE := $(HOMEDIR)/include.mk 
else
	INCLUDE := /dev/null
endif


include $(INCLUDE)

index.txt: 
	head -n-1 README.asciidoc > /tmp/t.ad


#COPY_LIST += $(wildcard *.png)

###########################################################  Precompiled Headers
# http://gcc.gnu.org/onlinedocs/libstdc++/manual/using_headers.html#manual.intro.using.headers.pre 
# TR http://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html
ALL_INC=/usr/lib64/gcc/x86_64-pc-linux-gnu/4.7.0-alpha20120114/include/g++-v4/x86_64-pc-linux-gnu/bits/stdc++.h

stdc++.h.gch:
	g++ -Winvalid-pch -x c++-header -g -O2 -o $@  $(ALL_INC)

###########################################################



CLEAN_LIST += t-print  t-regex t-meta

CXXFLAGS=   -std=gnu++11 -Wall -I/home/lvv/p/ 
t-buf-r: t-buf

########################################################  SCCPP

u-sccpp:	CXXFLAGS=-Wall  -I/home/lvv/p/  -D_GLIBCXX_DEBUG 
sccpp:		CXXFLAGS=-Wall  -I/home/lvv/p/  -O3 
u-sccpp: u-sccpp.cc 
	$(CXX) $(CXXFLAGS) $< -o $@ 
sccpp:	sccpp.cc
	$(CXX) $(CXXFLAGS) $< -o $@ 
u-sccpp sccpp: sccpp.h

########################################################  BENCH
BENCH_FILE=/tmp/bf

bench_lines: $(BENCH_FILE)
	#sh -c "[ -x /tmp/x ] && mv /tmp/x{,.old}"
	scc -O -x /tmp/x -n 'WRl n++; n'
	cat $(BENCH_FILE) > /dev/null
	/usr/bin/time -f'\t%Es (%Us+%Ss) \t%MKB\n'  /tmp/x < $(BENCH_FILE)

bench: $(BENCH_FILE)
	cat $(BENCH_FILE) > /dev/null
	@echo 
	LC_ALL=C time wc -wl $(BENCH_FILE)
	@echo 
	LC_ALL=C time gawk '{n+=NF}; END{print n, NR}'  $(BENCH_FILE)
	@echo 
	LC_ALL=C time mawk '{n+=NF}; END{print n, NR}'  $(BENCH_FILE)
	@echo 
	scc -O -x /tmp/x -n 'WRl n+=NF; __ NR ^ n;'
	LC_ALL=C time  /tmp/x < $(BENCH_FILE)


$(BENCH_FILE):
	scc 'char C[]="123456789"; REP(5*1000*1000) { REP(10) _ C << " "; __ "";}' > $(BENCH_FILE)
