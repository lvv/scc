
############################################################################################### make + install
make:
	@echo "SCC is headers only code, no preliminary compilation is needed."
	@echo "After checking out from repo, it's in read-to-use state."

PREFIX=/usr/local
install:
	@echo "not implemented - just use this (scc/) directory."
#	mkdir -p  ${PREFIX}/bin/
#	cp -v scc ${PREFIX}/bin/
#	mkdir -p  ${PREFIX}/include/scc/
#	cp -v *.h ${PREFIX}/include/scc/


############################################################################################### asciidoc gen
ASCIIDOC_FILTERS ?= /usr/share/asciidoc/filters


ifeq ($(USER),lvv)
	HOMEDIR := /home/lvv/p/volnitsky.com/
	INCLUDE := $(HOMEDIR)/include.mk 
else
	INCLUDE := /dev/null
endif


include $(INCLUDE)

##index.txt: 
#	head -n-1 README.asciidoc > /tmp/t.ad

index.html:  /tmp/t.ad

/tmp/t.ad:  README.asciidoc
	head -n-1 README.asciidoc > /tmp/t.ad


u-meta.cc: *.h

#COPY_LIST += $(wildcard *.png)

###########################################################  Precompiled Headers
# http://gcc.gnu.org/onlinedocs/libstdc++/manual/using_headers.html#manual.intro.using.headers.pre 
# TR http://gcc.gnu.org/onlinedocs/gcc/Precompiled-Headers.html
ALL_INC=$(wildcard /usr/lib64/gcc/x86_64-pc-linux-gnu/4.7.0-*/include/g++-v4/x86_64-pc-linux-gnu/bits/stdc++.h)


#H =  $(wildcard *.h)
#GCH = $(H:.h=.h.gch) stdc++.h.gch
GCH =   scc.h.gch 



stdc++.h.gch:
	g++  -Winvalid-pch -std=gnu++11 -x c++-header -o $@  $(ALL_INC)

%.h.gch:  %.h
	g++  -Winvalid-pch -std=gnu++11 -I . -I .. -x c++-header -o $@  $<
	
gch: ${GCH}
echo:
	: H:  ${H}
	: GCH:  ${GCH}

###########################################################



CLEAN_LIST += t-print  t-regex t-meta

#CXXFLAGS +=   -std=gnu++11 -Wall -I/home/lvv/p/ 
CXXFLAGS +=   -Wall -I/home/lvv/p/ -I .. 

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

######################################################  Unit Tests
CXXFLAGS+= -std=gnu++11 -Wall -O0 -ggdb3 -D_GLIBCXX_DEBUG  -fno-inline -I/home/lvv/p/  

